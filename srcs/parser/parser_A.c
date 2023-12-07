/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_A.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/07 15:29:43 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	pipe_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->right == NULL || node->left == NULL)
		return (*error += 1, syntax_error("|", cl), false);
	return (true);
}

bool	apr_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->right == NULL)
		return (*error += 1, syntax_error("newline", cl), false);
	if (node->right->type == APRD)
		return (*error += 1, syntax_error(">>", cl), false);
	return (true);
}

bool	redr_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->left == NULL)
		return (*error += 1, syntax_error("newline", cl), false);
	return (true);
}

bool	redl_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->left != NULL)
		return (comd_rules(node->left->token, error, cl));
	if (node->right != NULL)
		return (comd_rules(node->right->token, error, cl));
	if (node->left == NULL || node->right == NULL)
		return (*error += 1, syntax_error("newline", cl), false);
	return (true);
}

bool	comd_rules(t_token **tokens, int *error, t_cleanup *cl)
{
	char	*pathname;

	if (get_herd(tokens, &(int){0}))
		return (true);
	pathname = cr_pathname(tokens[0]->content, cl->env, &cl->status, 0);
	if (pathname == NULL)
		return (*error += 1, false);
	else if (ft_strncmp(pathname, "ok", ft_strlen("ok")))
		free(pathname);
	return (true);
}
