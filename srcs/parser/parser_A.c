/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_A.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/08 20:42:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//checks for syntax error near a pipe
bool	pipe_rules(t_astn *node, int *err, t_cleanup *cl)
{
	if (node->right == NULL || node->left == NULL)
		return (*err += 1, syntax_error("|", cl), false);
	if (!parser_rules(node->left, err, cl))
		return (false);
	if (!parser_rules(node->right, err, cl))
		return (false);
	return (true);
}
//< << << << << << <<< <
//checks for syntax error near an append redirection
bool	apr_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->right == NULL)
		return (*error += 1, syntax_error("newline", cl), false);
	if ((node->right->type == APRD || node->right->type == REDR) \
	&& node->right->left == NULL)
		return (*error += 1, syntax_error(">>", cl), false);
	return (true);
}

//checks for syntax error near a right redirection
bool	redr_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->left == NULL)
		return (*error += 1, syntax_error("newline", cl), false);
	if (node->right->type == REDR && node->right->left == NULL)
		return (*error += 1, syntax_error(">", cl), false);
	return (true);
}

//< << << << << << <<< <
//checks for syntax error near a left redirection
bool	redl_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->right && node->right->type == HERD && node->right->left == NULL)
		return (*error += 1, syntax_error("<<", cl), false);
	if (node->right == NULL || (!(node->right->type % 4) && \
	node->right->left == NULL))
		return (*error += 1, syntax_error("newline", cl), false);
	if (access(node->right->token[0]->content, F_OK))
		return (*error += 1, \
		printf("minishell: %s: No such file or directory\n", \
		node->right->token[0]->content), false);
	return (true);
}

//bool	comd_rules(t_token **tokens, int *error, t_cleanup *cl)
//{
//	char	*pathname;

//	if (get_herd(tokens, &(int){0}))
//		return (true);
//	pathname = cr_pathname(tokens[0]->content, cl->env, &cl->status, 0);
//	if (pathname == NULL)
//		return (*error += 1, false);
//	else if (ft_strncmp(pathname, "ok", ft_strlen("ok")))
//		free(pathname);
//	return (true);
//}
