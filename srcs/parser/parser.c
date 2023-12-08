/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/08 20:05:23 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	parser_rules(t_astn *node, int *error, t_cleanup *cl)
{
	int	pos;

	pos = 0;
	if (*error)
		return (false);
	if (node->type == PIPE && !*error)
		return (pipe_rules(node, error, cl));
	else if (node->type == APRD && !*error)
		return (apr_rules(node, error, cl));
	else if (node->type == REDR && !*error)
		return (redr_rules(node, error, cl));
	else if (node->type == REDL && !*error)
		return (redl_rules(node, error, cl));
	get_herd(node->token, &pos);
	if (node->token[pos] && node->token[pos + 1] == NULL)
		return (*error += 1, syntax_error("newline", cl), false);
	if (node->token[pos] && !ft_strcmp(node->token[pos + 1]->content, "<<"))
		return (*error += 1, syntax_error("<<", cl), false);
	if (node->type == COMD && node->token[])
	return (true);
}

int	expand_node(t_astn *node, int *error, t_cleanup *cl)
{
	int	i;

	i = 0;
	if (node->left != NULL)
		return (expand_node(node->left, error, cl));
	if (node->right != NULL)
		return (expand_node(node->right, error, cl));
	if (node->type == COMD)
	{
		while (node->token[i] != NULL)
		{
			node->token[i]->content = expand_cont(node->token[i]->content, \
			error, cl);
			if (*error)
				return (0);
			i++;
		}
	}
	return (1);
}

/*
*	first i create the tree then i use parser_rules to check for 	
*/
t_astn	*parser(const char *input, t_cleanup *cl)
{
	t_astn		*tree;
	int			error;
	size_t		g_ind;

	error = 0;
	g_ind = 0;
	if (!*input)
		return (NULL);
	if (ft_strlen(input) == 1)
	{
		if (*input == '!')
			return (cl->status = 1, NULL);
		if (*input == ':' || *input == '#')
			return (cl->status = 0, NULL);
	}
	tree = create_ast(input, &g_ind, &error, NULL);
	//if (tree != NULL)
	//	return (print_tree(tree), tree); 
	if (error || tree == NULL)
		return (NULL);
	if (!expand_node(tree, &error, cl))
		return (free_tree(tree), NULL);
	if (!parser_rules(tree, &error, cl))
		return (free_tree(tree), NULL);
	return (tree);
}

/*parsing rules here*/
//no > > so tree->right->left->token[0] == NULL or tree->right->left == 
// NULL if tree->right->type == REDR
//no < < 
//you can have multiple files in those redirections but only the 
// first one will be redirected
//check file permissions for redirections, so 