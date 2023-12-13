/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:56:34 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/13 13:58:32 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//static void	out(void)
//{
//	char	*i = ft_itoa(g_signal);

//	write (2, "the signal is : ", ft_strlen("the signal is : "));
//	write (2, i, ft_strlen(i));
//	write (2, "\n", 1);
//}


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
