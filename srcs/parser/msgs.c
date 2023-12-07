/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/07 18:51:44 by djacobs          ###   ########.fr       */
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

void	syntax_error(const char *str, t_cleanup *cl)//check that 
{
	char	*err;

	err = ft_calloc((ft_strlen \
	("minishell: syntax error near unexpected token \'") + ft_strlen \
	(str) + ft_strlen("\'\n") + 1), sizeof(char));
	ft_strcat(err, "minishell: syntax error near unexpected token \'");
	ft_strcat(err, str);
	ft_strcat(err, "\'\n");
	perror(err);//don't know that i should put it on stderror, probably doesn't matter
	free(err);
	cl->status = 2;
}

void	err_msg(char *msg)
{
	printf ("minishell: %s\n", msg);
}

void	print_out(char *msg, t_cleanup *cl)
{
	write(get_fd(STDO, cl->fds), msg, ft_strlen(msg));
}

void	no_such_file(const char *file)
{
	printf("minishell: %s: No such file or directory\n", file);
}
