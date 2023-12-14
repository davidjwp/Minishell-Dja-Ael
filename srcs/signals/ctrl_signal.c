/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:56:34 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/14 13:38:16 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ctrl_c(int sig)
{
	char	*i = ft_itoa(g_signal);

	// write (2, i, ft_strlen(i));
	if (sig == SIGINT)
	{
		putchar('\n');
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (sig == SIGINT && g_signal)
		rl_redisplay();
	if (sig == SIGINT)
		g_signal = 130;
	free(i);
}

void	signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
}
