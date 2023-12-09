/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_A.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/09 16:57:12 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//checks for syntax error near a pipe
bool	pipe_rules(t_astn *node, int *err, t_cleanup *cl)
{
	if (node->right == NULL || node->left == NULL)
		return (*err += 1, syntax_error(PIPE, cl), false);
	if (!parser_rules(node->left, err, cl))
		return (false);
	if (!parser_rules(node->right, err, cl))
		return (false);
	return (true);
}

//checks for syntax error near an append redirection
bool	apr_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->right == NULL)
		return (*error += 1, syntax_error(0, cl), false);
	if (!(node->right->type % 4) && node->right->left == NULL)
		return (*error += 1, syntax_error(node->right->type, cl), false);
	return (true);
}

//> ......
//checks for syntax error near a right redirection
bool	redr_rules(t_astn *node, int *error, t_cleanup *cl)
{
	struct stat	folder;

	if (node->right == NULL)
		return (*error += 1, syntax_error(0, cl), false);
	if (!(node->right->type % 4) && node->right->left == NULL)
		return (*error += 1, syntax_error(node->right->type, cl), false);
	if (!(node->right->type % 4))
		if (!stat(node->right->left->token[0]->content, &folder))
			if (S_ISDIR(folder.st_mode))
				return (*error += 1, \
					is_a_dir(node->right->left->token[0]->content, cl), false);
	if (node->right->type == COMD)
		if (!stat(node->right->token[0]->content, &folder))
			if (S_ISDIR(folder.st_mode))
				return (*error += 1, \
				is_a_dir(node->right->token[0]->content, cl), false);
	return (true);
}

//checks for syntax error near a left redirection
bool	redl_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->right == NULL)
		return (*error += 1, syntax_error(0, cl), false);
	if (node->right && !(node->right->type % 4) && \
	node->right->left == NULL)
		return (*error += 1, syntax_error(node->right->type, cl), false);
	if (!(node->right->type % 4) && node->right->left->type == COMD && \
	node->right->left->token[0]->type == HERD)
		return (*error += 1, syntax_error(HERD, cl), false);
	if (node->right->type == COMD && node->right->token[0]->type == HERD)
		return (*error += 1, syntax_error(HERD, cl), false);
	if (access(node->right->token[0]->content, F_OK))
		return (*error += 1, \
	printf("minishell: %s: No such file or directory\n", \
		node->right->token[0]->content), false);
	return (true);
}
