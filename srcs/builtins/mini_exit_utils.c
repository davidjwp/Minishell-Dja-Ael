/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:52:08 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/19 18:56:14 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_is_all_nb(t_token **token)
{
	int	i;
	int	j;

	i = 1;
	while (token && token[i] && token[i]->content)
	{
		j = 0;
		if (token[i]->content[0] == '-' && ft_isdigit(token[i]->content[1]))
			j++;
		while (token[i]->content[j])
		{
			if (!ft_isdigit(token[i]->content[j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_is_all_alpha(t_token **token)
{
	int	i;
	int	j;

	i = 1;
	while (token && token[i] && token[i]->content)
	{
		j = 0;
		if (token[i]->content[0] == '-' && ft_isalpha(token[i]->content[1]))
			j++;
		while (token[i]->content[j])
		{
			if (!ft_isalpha(token[i]->content[j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_is_first_alpha(t_token **token)
{
	int	i;

	i = 0;
	while (token[1]->content[i])
	{
		if (!ft_isalpha(token[1]->content[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_is_first_digit(t_token **token)
{
	int	i;

	i = 0;
	while (token[1]->content[i])
	{
		if (!ft_isdigit(token[1]->content[i]))
			return (0);
		i++;
	}
	return (1);
}
