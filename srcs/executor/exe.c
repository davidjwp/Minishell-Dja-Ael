/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/13 17:46:25 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*	exe contains the following functions :
*	exec_comd(), sh_red(), sh_pipe(), execute()
*/
/*
*	this function will look through the tokens for a redirection or a heredoc 
*	as long as one is found it'll loop through it, then the first symbol found
*	is applied, a redirection, redirects, a heredoc ... heredocs ?
*	then the two tokens refering to a heredoc or a redirection are removed from
*	the node and whatever is left is executed.
*/
int	exec_comd(t_astn *tree, t_env *sh_env, t_cleanup *cl)
{
	int	pos;

	while (red_herd(tree->token))
	{
		pos = 0;
		get_pos(tree->token, &pos);
		if (tree->token[pos]->type == HERD)
			exe_herd(tree, pos, cl);
		else if (tree->token[pos]->type && !(tree->token[pos]->type % 4))
			sh_red(tree->token, pos, cl);
		if (!rem_tokens(tree, pos))
			return (0);
	}
	if (tree->token[0] && (tree->token[0]->type && \
	!(tree->token[0]->type % 11)))
		builtin(tree, cl, tree->token[0]->type);
	else if (tree->token[0] != NULL)
		execute(tree, sh_env, cl);
	return (1);
}

int	sh_red(t_token **tok, int pos, t_cleanup *cl)
{
	int	fd;

	if (tok[pos]->type == REDL)
		fd = open(tok[pos + 1]->content, 524288, 0644);
	else if (tok[pos]->type == REDR)
		fd = open(tok[pos + 1]->content, 524354, 0644);
	else
		fd = open(tok[pos + 1]->content, 525378, 0644);
	if (fd == -1)
		return (0);
	if (tok[pos]->type == REDL)
		return (res_fd(STDIN_FILENO, STDI, cl), fd_red(&fd, RED_IN), 1);
	return (res_fd(STDOUT_FILENO, STDO, cl), fd_red(&fd, RED_RED), 1);
}

void	ex_exit(int sig)
{
	if (sig == SIGINT)
	{
		write (2, "in sig handler\n", 16);
		exit(EXIT_FAILURE);
	}
}

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
	p.pid = fork();
	if (p.pid == -1)
		return (err_msg("sh_pipe fork error"), 0);
	if (!p.pid)
	{
		fd_red(&p, RED_PIP);
		exec_comd(tree->left, sh_env, cl);
		return (clean_up(cl, CL_ALL), exit(EXIT_SUCCESS), 0);
	}
	g_signal = 0;
	dup2(p.pipe[0], STDIN_FILENO);
	close_pipe(p.pipe);
	shell_loop(tree->right, sh_env, cl);
	return (wait(&cl->status), 0);
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
	//signal(SIGINT, ex_exit);
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

void	reset_fds(t_cleanup *cl)
{
	res_fd(STDIN_FILENO, STDI, cl);
	res_fd(STDOUT_FILENO, STDO, cl);
}

//echo $? | echo $? | echo $?