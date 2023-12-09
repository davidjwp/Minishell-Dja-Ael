/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 10:37:38 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/09 15:58:05 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile int	g_signal = 0;

//valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./minitest

/*
* sh_init will initialize the global data structure for the shell
* the fds in order to always keep the original stdios in case of pipes or redir
* the tree is created and parsed here and the status set to 0 on the first pass
* the data structure contains the input, envs, tree, status and fds 
*/
bool	sh_init(t_env *sh_env, t_cleanup *cl)
{
	static int	passes;

	signals();
	cl->fds = init_fds();
	cl->env = sh_env;
	if (!passes)
		cl->status = 0;
	cl->tree = parser(cl->input, cl);
	passes += 1;
	if (cl->input && *cl->input)
		add_history(cl->input);
	if (cl->tree == NULL)
		return (clean_up(cl, CL_FDS | CL_INP | CL_FDS | CL_PRO), false);
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
		cl->input = readline(cr_prompt(cl, sh_env));
		if (cl->input == NULL || cl->prompt == NULL)
			return (clean_up(cl, CL_CL | CL_PRO), free_env(sh_env), 1);
		if (sh_init(sh_env, cl))
			shell_loop(cl->tree, sh_env, cl);
		//printf("exit:%d\n", cl->status > 255 ? WEXITSTATUS(cl->status) : cl->status);
	}
	return ((void)ac, (void)av, 1);
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
	else if (tree->token[0]->type && !(tree->token[0]->type % 11))
		builtin(tree, cl, tree->token[0]->type);
	else
		execute(tree, sh_env, cl);
	if (tree == cl->tree)
		clean_up(cl, CL_FDS | CL_TRE | CL_INP | CL_PRO);
	return (1);
}
