/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/12 15:16:10 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//also make sure that the file in a redirection is NOT A DIR
bool	parser_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (*error)
		return (false);
	if (node->type == PIPE && !*error)
		return (pipe_rules(node, error, cl));
	if (node->type == COMD && !*error)
		return (comd_rules(node->token, error, cl));
	return (true);
}

int	expand_node(t_astn *n, int *err, t_cleanup *cl)
{
	int	i;

	i = 0;
	if (n->left != NULL)
		return (expand_node(n->left, err, cl));
	if (n->right != NULL)
		return (expand_node(n->right, err, cl));
	if (n->type == COMD)
	{
		while (n->token[i] != NULL)
		{
			n->token[i]->content = expand_cont(n->token[i]->content, \
			err, cl);
			if (*err)
				return (0);
			n->token[i]->content = rem_quotes(n->token[i]->content, \
			&n->token[i]->type, err);
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
