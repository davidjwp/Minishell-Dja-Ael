/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:40:51 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/20 18:39:14 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	mini_exit(t_cleanup *cl, t_token **token)
{
	int	n;
	int	status;

	status = 0;
	n = 0;
	if (get_token_len(token) > 2)
		return (ft_putendl_fd("Minishell: exit: too many arguments", 2), 2);
	else if (token[1] && token[1]->content)
	{
		if (check_is_nb(token[1]->content))
		{
			n = ft_atoi(token[1]->content);
			if (n >= 0 && n <= 255)
				status = n;
			else
				status = n % 256;
		}
		else
		{
			ft_putstr_fd("minishell: exit: numeric argument required: ", 2);
			ft_putendl_fd(token[1]->content, 2);
			status = 2;
		}
	}
	return (clean_up(cl, CL_ALL), exit(status), 1);
}
//have to free CL_CL else cl is "leak" so might have to CL_ALL everytime
