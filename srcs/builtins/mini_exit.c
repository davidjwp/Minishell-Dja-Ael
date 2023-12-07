/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:40:51 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:33:16 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

static int	check_is_nb(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' && ft_isdigit(str[1]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	mini_exit(char **split_command)
{
	int	n;
	int	is_num;

	n = 0;
	if (split_command[1] && split_command[2])
		return (ft_putendl_fd("Minishell: exit: too many arguments", 2));
	if (split_command[1])
	{
		is_num = check_is_nb(split_command[1]);
		if (is_num)
		{
			n = ft_atoi(split_command[1]);
			if (n >= 0 && n <= 255)
				g_exit_status = n;
			else
				g_exit_status = n % 256;
		}
		else
		{
			ft_putstr_fd("minishell: exit: numeric argument required: ", 2);
			ft_putendl_fd(split_command[1], 2);
			g_exit_status = 2;
		}
	}
	return (exit(g_exit_status), 1);
}
