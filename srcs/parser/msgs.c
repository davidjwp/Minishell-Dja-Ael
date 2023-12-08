/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/08 13:37:31 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//no standard fds on these outputs 

void	not_found(char *cmd, int *status)
{
	char	*err;

	err = ft_calloc((ft_strlen(": command not found\n") + ft_strlen(cmd) + \
	ft_strlen("minishell: ") + 1), sizeof(char));
	ft_strcat(err, "minishell: ");
	ft_strcat(err, cmd);
	ft_strcat(err, ": command not found\n");
	write (2, err, ft_strlen(err));
	free(err);
	*status = 127;
}

void	syntax_error(const char *str, t_cleanup *cl)
{
	write (2, "minishell: syntax error near unexpected token \'", \
	ft_strlen("minishell: syntax error near unexpected token \'"));
	write (2, str, ft_strlen(str));
	write (2, "\'\n", ft_strlen("\'\n"));
	cl->status = 2;
}

void	err_msg(char *msg)
{
	write(2, "minishell: ", 12);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	print_out(char *msg, t_cleanup *cl)
{
	write(get_fd(STDO, cl->fds), msg, ft_strlen(msg));
}

void	no_such_file(const char *file)
{
	printf("minishell: %s: No such file or directory\n", file);
}
