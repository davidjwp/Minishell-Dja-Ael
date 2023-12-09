/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidjwp <davidjwp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/10 00:32:21 by davidjwp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*	exe contains the following functions :
*	open_file(), sh_red(), sh_pipe(), clean_up(), execute()
*/
//checks for access permissions and viability of files then opens
// int	open_file(t_astn *tree, t_red *_red, int flag)
// {
// 	if (flag == O_APPEND)
// 	{
// 		if (access(tree->right->token[0]->content, W_OK) == -1)
// 			_red->out = open(tree->right->token[0]->content, O_RDWR | 
// 			__O_CLOEXEC | O_CREAT | O_APPEND, 0644);
// 		else
// 			_red->out = open(tree->right->token[0]->content, O_RDWR | 
// 			__O_CLOEXEC | O_APPEND, 0644);
// 	}
// 	else if (!flag)
// 	{
// 		if (access(tree->right->token[0]->content, W_OK) == -1)
// 			_red->out = open(tree->right->token[0]->content, O_RDWR | 
// 			__O_CLOEXEC | O_CREAT, 0644);
// 		else
// 			_red->out = open(tree->right->token[0]->content, O_RDWR | 
// 			__O_CLOEXEC, 0644);
// 	}
// 	if (_red->out == -1)
// 		return (0);
// 	return (1);
// }

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
// int	sh_red(t_astn *tree, t_env *sh_env, t_cleanup *cl)
// {
// 	t_red	_red;

// 	if (tree->type == REDL)
// 	{
// 		_red.in = open(tree->right->token[0]->content, O_RDONLY | __O_CLOEXEC);
// 		if (_red.in == -1)
// 			return (0);
// 		restore_fd(STDIN_FILENO, STDI, cl);
// 		dup2(_red.in, STDIN_FILENO);
// 		close(_red.in);
// 		shell_loop(tree->left, sh_env, cl);
// 		return (restore_fd(STDIN_FILENO, STDI, cl), 1);
// 	}
// 	else if (tree->type == REDR)
// 		if (!open_file(tree, &_red, 0))
// 			return (err_msg("open file fail"), 0);
// 	if (tree->type == APRD)
// 		if (!open_file(tree, &_red, O_APPEND))
// 			return (err_msg("open file fail"), 0);
// 	restore_fd(STDOUT_FILENO, STDO, cl);
// 	fd_redirection(&_red, RED_RED);
//  	shell_loop(tree->left, sh_env, cl);
// 	return (restore_fd(STDOUT_FILENO, STDO, cl), 1);
// }

void	perm_denied(char *file, t_cleanup *cl)
{
	write (2, "-Minishell: ", 13);
	write (2, file, ft_strlen(file));
	write (2, ": Permission denied\n", 21);
	cl->status = 1;
}

// int	open_file(t_astn *node, t_red *_red, int fl, t_cleanup *cl)
// {
// 	if (!(node->right->type % 4))
// 	{
// 		if (node->type == REDL && access(node->right->left->token[0]->content, 
// 		R_OK))
// 			return (open(node->right->left->token[0]->content, fl));
// 		else if (node->type == REDL && 
// 		access(node->right->left->token[0]->content, R_OK) == -1)
// 			return (perm_denied(node->right->left->token[0]->content, cl), -1);
// 		if (access(node->right->left->token[0]->content, W_OK) == -1)
// 			return (open(node->right->left->token[0]->content, fl | O_CREAT));
// 		else
// 			return (open(node->right->left->token[0]->content, fl));
// 	}
// 	else
// }

bool	file_perm(char *name, int type, int *cr, t_cleanup *cl)
{
	if (type == REDL)
	{
		if (!access(name, F_OK))
		{
			if (!access(name, R_OK))
				return (true);
			return (perm_denied(name, cl), false);
		}
		return (no_such_file(name, cl), false);
	}
	if (!access(name, F_OK))
	{
		if (!access(name, W_OK))
			return (true);
		return (perm_denied(name, cl), false);
	}
	return (*cr = O_CREAT, true);
}

bool	open_file(t_astn *node, int *fd, int fl, t_cleanup *cl)
{
	int	cr;

	cr = 0;
	if (!(node->type % 4))
	{
		if (!file_perm(node->left->token[0]->content, node->type, &cr, cl))
			return (*fd = -1, false);
		return (*fd = open(node->left->token[0]->content, fl | cr), true);
	}
	if (!file_perm(node->token[0]->content, node->parent->type, &cr, cl))
		return (*fd = -1, false);
	return (*fd = open(node->token[0]->content, fl | cr), true);
}

int	fd_type(int type)
{
	if (type == REDL)
		return (RED_IN);
	return (RED_RED);
}

//flags are fucked but it seems to work ok
	// O_RDWR | __O_CLOEXEC | O_CREAT | O_APPEND;
int	sh_red(t_astn *tree, t_env *sh_env, t_cleanup *cl)
{
	int	fd;

	if (tree->type == REDL)
		open_file(tree->right, &fd, O_RDONLY | __O_CLOEXEC, cl);
	else if (tree->type == REDR)
		open_file(tree->right, &fd, O_RDWR | __O_CLOEXEC, cl);
	else
		open_file(tree->right, &fd, O_RDWR | __O_CLOEXEC | O_APPEND, cl);
	if (fd == -1)
		return (0);
	fd_redirection(&fd, fd_type(tree->type));
	shell_loop(tree->left, sh_env, cl);
	shell_loop(tree->right, sh_env, cl);
	if (tree->parent == NULL || tree->parent->type == PIPE)
	{
		restore_fd(STDOUT_FILENO, STDO, cl);
		restore_fd(STDIN_FILENO, STDI, cl);
	}
	return (1);
}
//>> asjdas

/*
*	this is the shell pipes, they open a pipe and fork, in the child process
*	the output is redirected to the pipe and the command is executed.
*
*	Then the stdin is replaced with the read end of the pipe and shell_loop
*	is reinitialized thus executing whatever is right of the pipe. 
*/
int	sh_pipe(t_astn *tree, t_env *sh_env, t_cleanup *cl)
{
	t_pipe	p;

	if (pipe(p.pipe) == -1)
		return (err_msg("sh_pipe pipe error"), 0);
	p.l_pid = fork();
	if (p.l_pid == -1)
		return (err_msg("sh_pipe fork error"), 0);
	if (!p.l_pid)
	{
		fd_redirection(&p, RED_PIP);
		if (!(tree->left->token[0]->type % 11) && tree->left->token[0]->type)
			child_builtin(tree->left, cl, tree->left->token[0]->type);
		else
			execute(tree->left, sh_env, cl);
		return (clean_up(cl, CL_ALL), exit(EXIT_SUCCESS), 0);
	}
	wait(&cl->status);
	dup2(p.pipe[0], STDIN_FILENO);
	close_pipe(p.pipe);
	shell_loop(tree->right, sh_env, cl);
	return (restore_fd(STDIN_FILENO, STDO, cl), 0);
}

/*
*	cleans up file descriptors, the abstract syntax tree, the shell envs
*	the input, the prompt and the cl
*	you can choose which one you want to free by using the flags and bitwise
*	ops like | or ^
*/
//cleans up file descriptors the abstract synthax tree and the shell envs
void	clean_up(t_cleanup *cl, int flag)
{
	if ((flag & CL_FDS) && cl->fds != NULL)
		close_fds(cl->fds);
	if ((flag & CL_TRE) && cl->tree != NULL)
		free_tree(cl->tree);
	if ((flag & CL_ENV) && cl->env != NULL)
		free_env(cl->env);
	if ((flag & CL_INP))
	{
		free(cl->input);
		cl->input = NULL;
	}
	if ((flag & CL_HIS))
		rl_clear_history();
	if ((flag & CL_PRO) && cl->prompt != NULL)
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
	clean_up(cl, CL_FDS);
	return (execve(exe._path, exe.argv, exe._envp), exit(EXIT_FAILURE), 0);
}
