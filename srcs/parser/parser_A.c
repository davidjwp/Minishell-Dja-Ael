/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_A.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/10 20:17:23 by djacobs          ###   ########.fr       */
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

bool	redr_rules(t_token *tok, int *error, t_cleanup *cl)
{
	struct stat	folder;

	if (tok == NULL)
		return (*error += 1, syntax_error(0, cl), false);
	if (tok->type && !(tok->type % 4))
		return (*error += 1, syntax_error(tok->type, cl), false);
	if (!stat(tok->content, &folder))
		if (S_ISDIR(folder.st_mode))
			return (*error += 1, is_a_dir(tok->content, cl), false);
	if (access(tok->content, F_OK))
		if (!access(tok->content, W_OK))
			return (*error += 1, perm_denied(tok->content, cl), false);
	return (true);
}

bool	redl_rules(t_token *tok, int *error, t_cleanup *cl)
{
	struct stat	dir;

	if (tok == NULL)
		return (*error += 1, syntax_error(0, cl), false);
	if (tok->type == HERD || (tok->type && !(tok->type % 4)))
		return (*error += 1, syntax_error(tok->type, cl), false);
	if (!stat(tok->content, &dir))
		if (S_ISDIR(dir.st_mode))
			return (*error = 1, is_a_dir(tok->content, cl), false);
	if (access(tok->content, F_OK))
		return (*error += 1, no_such_file(tok->content, cl), false);
	if (access(tok->content, F_OK | R_OK))
		return (*error += 1, perm_denied(tok->content, cl), false);
	return (true);
}

bool	herd_rules(t_token *tok, int *err, t_cleanup *cl)
{
	if (tok == NULL)
		return (*err += 1, syntax_error(0, cl), false);
	if (tok->type)
		return (*err += 1, syntax_error(tok->type, cl), false);
	return (true);
}

bool	comd_rules(t_token **tok, int *err, t_cleanup *cl)
{
	struct stat	dir;
	int	i;

	i = 0;
	while (tok[i] != NULL)
	{
		if (tok[i]->type == REDL)
			redl_rules(tok[i + 1], err, cl);
		else if (tok[i]->type == REDR || tok[i]->type == APRD)
			redr_rules(tok[i + 1], err, cl);
		else if (tok[i]->type == HERD)
			herd_rules(tok[i + 1], err, cl);
		else if (!tok[i]->type)
		{
			if (!stat(tok[i]->content, &dir))
				if (S_ISDIR(dir.st_mode))
					return (*err += 1, is_a_dir(tok[i]->content, cl), false);
		}
		if (*err)
			return (false);
		i++;
	}
	return (true);
}