/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_B.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidjwp <davidjwp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/11 23:39:28 by davidjwp         ###   ########.fr       */
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

void	set_qr(char *cont, int *qr)//
{
	int	i;
	

}

char	*rem_quotes(t_token *t, int *err, int i, int y)
{
	char	*new;
	int		qr;

	set_qr(t->content, &qr);
	n_quolen(t->content, &i, &y);
	if (!(y - i))
		return (free(t->content), t->content = ft_strdup(""));
	new = ft_calloc(((y - i) + 1), sizeof(char));
	if (new == NULL)
		return (*err = 1, NULL);
	i = 0;
	y = 0;
	while (t->content[i])
	{
		while (type(t->content, i) && !(type(t->content, i) % 5))
			i++;
		if (t->content[i])
			new[y] = t->content[i++];
		y++;
	}
	return (free(t->content), new);
}
