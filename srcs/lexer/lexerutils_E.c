/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerutils_E.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:32:25 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/07 13:09:06 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*	lexerutils_E contains the following functions :
*	free_node(), it_sep()
*/
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
