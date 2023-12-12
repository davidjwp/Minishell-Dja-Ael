/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_B.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/12 15:13:04 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	n_quolen(char *cont, int *i, int *y)
{
	while (cont[*y])
	{
		if (type(cont, *y) && !(type(cont, *y) % 5))
			*i += 1;
		*y += 1;
	}
}

char	*rem_quotes(char *cont, int *t, int *err)
{
	char	*new;
	int		i;
	int		y;	

	y = 0;
	i = 0;
	n_quolen(cont, &i, &y);
	if (!(y - i))
		return (free(cont), cont = ft_strdup(""));
	new = ft_calloc(((y - i) + 1), sizeof(char));
	if (new == NULL)
		return (*err = 1, NULL);
	i = 0;
	y = 0;
	while (cont[i])
	{
		while (type(cont, i) && !(type(cont, i) % 5))
			i++;
		if (cont[i])
			new[y] = cont[i++];
		y++;
	}
	if ((get_token_type(new) && !(get_token_type(new) % 11)))
		return (free(cont), *t = get_token_type(new), new);
	return (free(cont), new);
}
