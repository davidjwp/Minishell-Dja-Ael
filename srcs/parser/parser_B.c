/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_B.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/07 15:35:14 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*rem_quotes(char *content, int *err, int i, int y)
{
	char	*new;

	while (content[y])
	{
		if (type(content, y) && !(type(content, y) % 5))
			i++;
		y++;
	}
	if (!(y - i))
		return (free(content), content = ft_strdup(""));
	new = ft_calloc(((y - i) + 1), sizeof(char));
	if (new == NULL)
		return (*err = 1, NULL);
	i = 0;
	y = 0;
	while (content[i])
	{
		while (type(content, i) && !(type(content, i) % 5))
			i++;
		if (content[i])
			new[y] = content[i++];
		y++;
	}
	return (free(content), new);
}
