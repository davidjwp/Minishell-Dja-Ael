/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidjwp <davidjwp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/09 23:20:04 by davidjwp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//no standard fds on these outputs 

void	not_found(char *cmd, int *status)
{
	write (2, "minishell: ", ft_strlen("minishell: "));
	write (2, cmd, ft_strlen(cmd));
	write (2, ": command not found\n", ft_strlen (": command not found\n"));
	*status = 127;
}

void	syntax_error(int type, t_cleanup *cl)
{
	write (2, "minishell: syntax error near unexpected token \'", \
	ft_strlen("minishell: syntax error near unexpected token \'"));
	if (type == REDL)
		write (2, "<", 1);
	else if (type == REDR)
		write (2, ">", 1);
	else if (type == HERD)
		write (2, "<<", 2);
	else if (type == APRD)
		write (2, ">>", 2);
	else if (type == PIPE)
		write (2, "|", 1);
	else
		write (2, "newline", 8);
	write (2, "\'\n", ft_strlen("\'\n"));
	cl->status = 2;
}

void	err_msg(char *msg)
{
	write (2, "minishell: ", 12);
	write (2, msg, ft_strlen(msg));
	write (2, "\n", 1);
}

void	no_such_file(const char *file, t_cleanup *cl)
{
	write(2, "minishell: ", 12);
	write(2, file, ft_strlen(file));
	write(2, ": No such file or directory\n", 29);
	cl->status = 1;
}

void	is_a_dir(char *dir, t_cleanup *cl)
{
	write(2, "minishell: ", 12);
	write(2, dir, ft_strlen(dir));
	write(2,": Is a directory\n", 18);
	cl->status = 126;
}
