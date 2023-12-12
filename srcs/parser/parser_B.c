/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_B.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/12 20:24:55 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	n_quolen(char *cont, int *len, int i, int t)
{
	bool	open;

	*len = 0;
	open = false;
	while (cont[i])
	{
		if (type(cont, i) && !(type(cont, i) % 5) && !open)
		{
			t = type(cont, i++);
			open = true;	
		}
		if (type(cont, i) == t && open)
			open = false;
		if (!t || type(cont, i) != t)
			*len += 1;
		i++;
	}
	return (*len);
}

char	*rem_quotes(char *cont, int *tp, int *err, t_p p)
{
	char	*new;
	int		t;

	t = 0;
	if (n_quolen(cont, &p.len, 0, 0) <= 0)
		return (free(cont), cont = ft_strdup(""));
	new = ft_calloc((p.len + 1), sizeof(char));
	if (new == NULL)
		return (*err = 1, NULL);
	while (cont[p.i])
	{
		if (type(cont, p.i) && !(type(cont, p.i) % 5) && !p.o)
		{
			t = type(cont, p.i++);
			p.o = 1;
		}	
		if (type(cont, p.i) == t && p.o)
			p.o = 0;
		if (!t || type(cont, p.i) != t)
			new[p.y++] = cont[p.i];
		p.i++;
	}
	if ((get_token_type(new) && !(get_token_type(new) % 11)))
		return (free(cont), *tp = get_token_type(new), new);
	return (free(cont), new);
}
