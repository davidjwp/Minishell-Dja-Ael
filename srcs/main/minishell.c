/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 10:37:38 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/20 19:54:48 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile int	g_signal = 0;

/*
*	cleans up file descriptors, the abstract syntax tree, the shell envs
*	the input, the prompt and the cl
*	you can choose which one you want to free by using the flags and bitwise
*	ops like | or ^
*/
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

/*
* sh_init will initialize the global data structure for the shell
* the fds in order to always keep the original stdios in case of pipes or redir
* the tree is created and parsed here and the status set to 0 on the first pass
* the data structure contains the input, envs, tree, status and fds 
*/
bool	sh_init(t_cleanup *cl)
{
	static int	passes;

	//signals();
	cl->fds = init_fds();
	if (!passes && g_signal != 130)
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
* the main function creates the shell env consisting of the env being passed
* to the main function
* then the main loop where the global data structure is created and the
* shell_loop
*/
int	main(int ac, char **av, char **env)
{
	t_cleanup	*cl;

	cl = malloc(sizeof(t_cleanup));
	if (cl == NULL)
		return (err_msg("cl malloc fail"), 0);
	cl->env = cr_env(env);
	if (cl->env == NULL)
		return (free(cl), 0);
	signals();
	while (42)
	{
		g_signal = 1;
		cl->input = readline(cr_prompt(cl));
		if (g_signal == 130)
			cl->status = g_signal;
		if (cl->input == NULL || cl->prompt == NULL)
			return (clean_up(cl, CL_CL | CL_PRO | CL_ENV), 0);
		if (sh_init(cl))
			shell_loop(cl->tree, cl);
	}
	return ((void)ac, (void)av, 1);
}

/*
* the main shell loop which redirects or pipes the output in order of the tree
* being recursively called
*/
int	shell_loop(t_astn *tree, t_cleanup *cl)
{
	if (tree == NULL)
		return (0);
	if (tree->type == PIPE)
		sh_pipe(tree, cl);
	else
		exec_comd(tree, cl);
	if (tree == cl->tree)
		return (reset_fds(cl), clean_up(cl, CL_FDS | CL_TRE | \
		CL_INP | CL_PRO), 1);
	return (1);
}
