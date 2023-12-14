/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerutils_D.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:26:11 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/14 15:30:40 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*	lexerutils_D contains the following functions :
*	get_node_type(), free_tree(), free_node(), it_sep()
*/

//gets the node type for redirections
int	get_node_type(const char *input, size_t *g_ind)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (input[i] && (type(input, i) == 0 || type(input, i) % 4 != 0))
		i++;
	check_spec(&input[i], &n);
	*g_ind += n;
	return (type(input, i));
}

//free tree from root to bottom
void	free_tree(t_astn *node)
{
	if (node->left != NULL)
		free_tree(node->left);
	if (node->right != NULL)
		free_tree(node->right);
	if (node->type == COMD)
		free_cmd_node(node, true);
	else
		free(node);
}

//free the redirection node
void	free_node(t_astn *red)
{
	free_cmd_node(red->left, true);
	free_cmd_node(red->right, true);
	free(red);
}

//iterates over separarators
bool	it_sep(const char *input, size_t *l_ind)
{
	while (type(input, *l_ind) == SEPR && input[*l_ind])
		*l_ind += 1;
	return (true);
}
