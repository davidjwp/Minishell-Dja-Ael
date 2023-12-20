/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:01:05 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/20 20:01:21 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*get_herd(t_token **tokens, int *pos)
{
	while (tokens[*pos] != NULL && tokens[*pos]->type != HERD)
		*pos += 1;
	if (tokens[*pos] == NULL)
		return (NULL);
	return (tokens[*pos + 1]);
}
