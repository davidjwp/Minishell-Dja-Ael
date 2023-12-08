/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:24:48 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/08 18:17:41 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 

extern int	g_exit_status;

static void	parent_builtin(t_astn *tree, t_cleanup *cl, int type)
{
	if (type == PWD)
		cl->status = mini_pwd();
	else if (type == ENV)
		cl->status = mini_env(cl->env);
	else if (type == ECHO)
		cl->status = mini_echo(tree);
	else if (type == EXIT)
		cl->status = mini_exit(cl, tree->token);
	
}

void	child_builtin(t_astn *tree, t_cleanup *cl, int type)
{
	if (type == PWD)
		cl->status = mini_pwd();
	else if (type == ENV)
		cl->status = mini_env(cl->env);
	else if (type == ECHO)
		cl->status = mini_echo(tree);
	else if (type == EXIT)
		cl->status = mini_exit(cl, tree->token);
	
	if (type != EXIT)
		exit(EXIT_SUCCESS);
}

void		builtin(t_astn *tree, t_cleanup *cl, int type)
{
	pid_t pid;
	// cl->status;
	// fprintf(stderr, "ici\n");
	if (tree->parent && tree->parent->type == PIPE)
	{
		pid = fork();

		if (pid == 0)
			child_builtin(tree, cl, type);
		else
			wait(&cl->status);
	}
	else
		parent_builtin(tree, cl, tree->token[0]->type);
	// else if (!ft_strcmp(tree->token[0]->content, "export"))
	// 	cl->status = mini_export(cl, tree->token);
	// else if (!ft_strcmp(tree->token[0]->content, "unset"))
	// 	cl->status = mini_unset(cl, tree->token);
	// else if (!ft_strcmp(tree->token[0]->content, "cd"))
	// 	cl->status = mini_cd(cl, tree->token);
	// else
	// {
	// 	signal(SIGINT, SIG_IGN);
	// 	signal(SIGQUIT, SIG_IGN);
	// }
}

// int	is_builtin(t_astn *tree)
// {
// 	if (!lst->command || !lst->split_command)	
// 		return (0);
// 	if (!ft_strcmp(lst->split_command[0], "pwd"))
// 		return (1);
// 	else if (!ft_strcmp(lst->split_command[0], "env"))
// 		return (1);
// 	else if (!ft_strcmp(lst->split_command[0], "export"))
// 		return (1);
// 	else if (!ft_strcmp(lst->split_command[0], "unset"))
// 		return (1);
// 	else if (!ft_strcmp(lst->split_command[0], "echo"))
// 		return (1);
// 	else if (!ft_strcmp(lst->split_command[0], "exit"))
// 		return (1);
// 	else if (!ft_strcmp(lst->split_command[0], "cd"))
// 		return (1);
// 	return (0);
// }
