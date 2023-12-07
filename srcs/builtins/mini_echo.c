/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:40:59 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:33:56 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_echo(char **str, int i)
{
	while (str && str[i])
	{
		ft_printf("%s", str[i]);
		if (str[i + 1])
			ft_printf(" ");
		i++;
	}
}

int	mini_echo(t_astn *tree)
{
	int	i;
	int	n;
	int	j;

	i = 1;
	n = 0;
	while (lst->split_command[i] && !ft_strncmp(lst->split_command[i], "-n", 2))
	{
		j = 1;
		while (lst->split_command[i][j] == 'n')
			j++;
		if (lst->split_command[i][j - 1] && lst->split_command[i][j] == '\0')
		{
			n = 1;
			i++;
		}
		else
			break ;
	}
	print_echo(lst->split_command, i);
	if (!n)
		ft_printf("\n");
	return (0);
}
