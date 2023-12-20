/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:40:51 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/20 19:54:06 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cvrt_atoi(char *str)
{
	int	n;

	n = 0;
	n = ft_atoi(str);
	if (n >= 0 && n <= 255)
		return (n);
	else
		return (n % 256);
}

static int	check_exit_case(t_cleanup *cl, t_token **token, int status)
{
	if (get_token_len(token) == 1)
		return (clean_up(cl, CL_ALL), exit(0), 0);
	else if (get_token_len(token) == 2 && token[1]->content)
	{
		if (check_is_all_nb(token))
		{
			status = cvrt_atoi(token[1]->content);
			return (clean_up(cl, CL_ALL), exit(status), status);
		}
		else
			return (ft_putstr_fd("minishell: exit: numeric argument required: ",
					2), clean_up(cl, CL_ALL), exit(2), 2);
	}
	else if (get_token_len(token) > 2)
	{
		if (check_is_all_nb(token) || check_is_first_digit(token))
			return (ft_putendl_fd("Minishell: exit: too many arguments", 2), 1);
		else if (check_is_all_alpha(token) || check_is_first_alpha(token))
			return (ft_putstr_fd("minishell: exit: numeric argument required: ",
					2), ft_putendl_fd(token[1]->content, 2),
				clean_up(cl, CL_ALL), exit(2), 2);
	}
	return (0);
}

int	mini_exit(t_cleanup *cl, t_token **token)
{
	int	status;

	status = 0;
	status = check_exit_case(cl, token, status);
	return (status);
}
