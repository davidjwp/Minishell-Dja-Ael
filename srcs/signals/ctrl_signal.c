/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:56:34 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/18 16:45:00 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (sig == SIGINT && g_signal)
		rl_redisplay();
	if (sig == SIGINT)
		g_signal = 130;
}

void	signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
}
