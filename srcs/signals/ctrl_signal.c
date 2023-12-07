/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:56:34 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/07 17:40:09 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		putchar('\n');
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// void	ctrl_d(char *str, char *prompt)
// {
// 	g_signal = 0;
// 	ft_putendl_fd("", STDOUT_FILENO);
// 	ft_putendl_fd(str, STDOUT_FILENO);
// 	rl_clear_history();
// 	free(prompt);
// 	exit(EXIT_SUCCESS);
// }
