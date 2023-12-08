/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/08 14:46:05 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*	exe contains the following functions :
*	open_file(), sh_red(), sh_pipe(), clean_up(), execute()
*/
//checks for access permissions and viability of files then opens
int	open_file(t_astn *tree, t_red *_red, int flag)
{
	if (flag == O_APPEND)
	{
		if (access(tree->right->token[0]->content, W_OK) == -1)
			_red->out = open(tree->right->token[0]->content, O_RDWR | \
			__O_CLOEXEC | O_CREAT | O_APPEND, 0644);
		else
			_red->out = open(tree->right->token[0]->content, O_RDWR | \
			__O_CLOEXEC | O_APPEND, 0644);
	}
	else if (!flag)
	{
		if (access(tree->right->token[0]->content, W_OK) == -1)
			_red->out = open(tree->right->token[0]->content, O_RDWR | \
			__O_CLOEXEC | O_CREAT, 0644);
		else
			_red->out = open(tree->right->token[0]->content, O_RDWR | \
			__O_CLOEXEC, 0644);
	}
	if (_red->out == -1)
		return (0);
	return (1);
}

//there could be case where it is a folder or something else be careful

/*
*	this is the shell redirection, it's a little scary looking because i
*	either had too many lines or too little to make the code readable.
*
*	as the name suggests it redirects output or input depending on the type of
*	redirection so first it'll get the fd for the file by using open_file(), then
*	i use res_fd() to put the fd corresponding to the fd which will be duplicated
*	to the file fd at the top of the list of fd(lots of fds lol) then i duplicate
*	the file fd with stdin or stdout, close the file fd and enter shell loop to
*	execute the command, then i make sure to restore the old fd
*/
int	sh_red(t_astn *tree, t_env *sh_env, t_cleanup *cl)
{
	t_red	_red;

	if (tree->type == REDL)
	{
		_red.in = open(tree->right->token[0]->content, O_RDONLY | __O_CLOEXEC);
		if (_red.in == -1)
			return (0);
		restore_fd(STDIN_FILENO, STDI, cl);
		dup2(_red.in, STDIN_FILENO);
		close(_red.in);
		shell_loop(tree->left, sh_env, cl);
		return (restore_fd(STDIN_FILENO, STDI, cl), 1);
	}
	else if (tree->type == REDR)
		if (!open_file(tree, &_red, 0))
			return (err_msg("open file fail"), 0);
	if (tree->type == APRD)
		if (!open_file(tree, &_red, O_APPEND))
			return (err_msg("open file fail"), 0);
	fd_redirection(&_red, RED_RED);
	shell_loop(tree->left, sh_env, cl);
	return (restore_fd(STDOUT_FILENO, STDO, cl), 1);
}

//cleans up file descriptors the abstract synthax tree and the shell envs
void	clean_up(t_cleanup *cl, int flag)
{
	if (cl->fds != NULL && (flag & CL_FDS))
		close_fds(cl->fds);
	if (cl->tree != NULL && (flag & CL_TRE))
		free_tree(cl->tree);
	if (cl->env != NULL && (flag & CL_ENV))
		free_env(cl->env);
	if ((flag & CL_INP))
	{
		free(cl->input);
		cl->input = NULL;
	}
	if ((flag & CL_HIS))
		rl_clear_history();
	if ((flag & CL_PRO))
		free(cl->prompt);
	if ((flag & CL_CL))
		free(cl);
}

//executes the command node, might not need that last freeing
int	execute(t_astn *tree, t_env *sh_env, t_cleanup *cl)
{
	pid_t	pid;
	t_exe	exe;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (err_msg("execute fork fail"), 0);
	if (pid)
		return (wait(&cl->status), 1);
	exe._path = cr_pathname(tree->token[0]->content, find_env("PATH", sh_env), \
	&status, 0);
	if (!exe._path)
		return (clean_up(cl, CL_ALL), exit(status), 0);
	exe._envp = cr_envp(sh_env);
	if (!exe._envp)
		return (free(exe._path), clean_up(cl, CL_ALL), exit(EXIT_FAILURE), 0);
	exe.argv = cr_args(tree->token, exe._path);
	if (!exe.argv)
		return (free_split(exe._envp), free(exe._path), clean_up(cl, CL_ALL), \
		exit(EXIT_FAILURE), 0);
	return (execve(exe._path, exe.argv, exe._envp), exit(EXIT_FAILURE), 0);
}
