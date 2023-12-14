/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:56:34 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/14 14:21:35 by djacobs          ###   ########.fr       */
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

void	sig_quit(int sig)
{
	if (sig == SIGQUIT && !g_signal)
	{
		write(2, "HERE\n", 6);
		exit(EXIT_FAILURE);
	}
}

// static void	sig_hook(int sig)
// {
// 	struct termios	term;

// 	if (sig == SIGQUIT)
// 		if (tcgetattr(STDIN_FILENO, &term) == 0)
// 			if (term.c_lflag & ECHOE)
// 				g_signal = 1;
// }

//void	mysig(int sig)
//{
//	struct termios	term;

//	if (sig == SIGQUIT)
//	{
//		tcgetattr(STDIN_FILENO, &term);
//		term.c_cc[VEOF] = _POSIX_VDISABLE;
//		tcsetattr(STDIN_FILENO, TCSANOW, &term);
//		ft_putchar('\n');
//		rl_on_new_line();
//		rl_replace_line("", 0);
//	}
//	if (g_signal)
//		rl_redisplay();
//}

void	signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
}
