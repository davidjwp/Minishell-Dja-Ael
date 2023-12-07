/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidjwp <davidjwp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 10:37:38 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/08 00:32:39 by davidjwp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile int	g_signal = 0;// i have to init here;

//valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./minitest

//this is just to exit the program easier
int	exit_emul(char *input)
{
	char	exit[] = "exit";

	if (!*input)
		return (0);
	for (int i = 0; exit[i] != 0; i++)
		if (input[i] != exit[i])
			return (0);
	return (1);
}

/*
* sh_init will initialize the global data structure for the shell
* the fds in order to always keep the original stdios in case of pipes or redir
* the tree is created and parsed here and the status set to 0 on the first pass
* the data structure contains the input, envs, tree, status and fds 
*/
bool	sh_init(char *input, t_env *sh_env, t_cleanup *cl)
{
	static int	passes;

	signals();
	cl->fds = init_fds();
	cl->env = sh_env;
	cl->input = input;
	if (!passes)
		cl->status = 0;
	cl->tree = parser(input, cl);
	passes += 1;
	if (cl->input && *cl->input)
		add_history(cl->input);
	if (cl->tree == NULL)
		return (clean_up(cl, CL_FDS | CL_INP | CL_FDS), false);
	return (true);
}

/*
* the main function which checks for the availability of the stdio fds
* then the shell env consisting of the env being passed to the main function
* then the main loop where the global data structure is created and the
* shell_loop
*/
int	main(int ac, char **av, char **env)
{
	char		*input;
	t_env		*sh_env;
	t_cleanup	*cl;

	sh_env = cr_env(env);
	if (sh_env == NULL)
		return (0);
	cl = malloc(sizeof(t_cleanup));
	if (cl == NULL)
		return (err_msg("cl malloc fail"), 0);
	signals();
	while (42)
	{
		input = readline(PROMPT);
		if (input == NULL)
			return (free(cl), free_env(sh_env), 1);
		if (sh_init(input, sh_env, cl))
		{
			//if (!input || exit_emul(input))
				//return (clean_up(cl, CL_ALL), exit(EXIT_SUCCESS), 1);
			shell_loop(cl->tree, sh_env, cl);
		}
		//printf("exit:%d\n", cl->status > 255 ? WEXITSTATUS(cl->status) : cl->status);
	}
	return ((void)ac, (void)av, 1);
}

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
		//if (!(tree->left->token[0]->type % 11) && tree->left->token[0]->type)
		//	exe_builtin(tree->left, sh_env, cl);
		//else
		execute(tree->left, sh_env, cl);
		return (clean_up(cl, CL_FDS), exit(EXIT_SUCCESS), 0);
	}
	wait(&cl->status);
	dup2(p.pipe[0], STDIN_FILENO);
	close_pipe(p.pipe);
	shell_loop(tree->right, sh_env, cl);
	return (restore_fd(STDIN_FILENO, STDO, cl), 0);
}

/*
* the main shell loop which redirects or pipes the output in order of the tree
* being recursively called
*/
int	shell_loop(t_astn *tree, t_env *sh_env, t_cleanup *cl)
{
	if (tree == NULL)
		return (input_enter(), clean_up(cl, CL_FDS | CL_INP), 0);
	if (tree->type == PIPE)
		sh_pipe(tree, sh_env, cl);
	else if (!(tree->type % 4))
		sh_red(tree, sh_env, cl);
	else if (get_herd(tree->token, &(int){0}))
		exe_herd(tree, sh_env, cl);
	else
		execute(tree, sh_env, cl);
	if (tree == cl->tree)
		clean_up(cl, CL_FDS | CL_TRE | CL_INP);
	return (1);
}

	//if (tree->token[0]->type && !(tree->token[0]->type % 11))
	//	exe_builtin(tree, sh_env, cl);

//pipes or redirections in quotes "|" '|' '>'
//""""""'''dughwi ugwieg riweg ioggroi weg'"
//"'''''''''''''' ' ' ' '" "dsaidghasioudhasd ads asadas dgher htr \\\\ das$$"
//""""'dasho"asdhasho  sahodo h'