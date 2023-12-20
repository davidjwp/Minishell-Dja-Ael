/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:03:33 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/20 20:01:18 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str_realloc(char *ptr, int nmember, int size)
{
	char	*new;
	int		newsize;
	int		psize;

	psize = ft_strlen(ptr);
	if ((nmember * size) <= psize)
		return (ptr);
	newsize = nmember * size;
	new = malloc(newsize);
	if (new == NULL)
		return (NULL);
	while (newsize--)
		new[newsize] = 0;
	if (ptr == NULL)
		return (new);
	return (ft_strcat(new, ptr), free(ptr), new);
}

bool	cmp_quo(char *del, char *new, int t)
{
	char	*quo;
	int		i;

	i = 0;
	quo = rem_quotes(new, &(int){t}, &(int){0}, (t_p){0, 0, 0, 0});
	while (del[i])
	{
		if ((!del[i] && quo[i]) || (del[i] != quo[i]))
			return (free(quo), false);
		i++;
	}
	return (free(quo), true);
}

bool	cmp_del(char *del, char *new)
{
	int		i;

	i = 0;
	if (!new[i])
		return (false);
	if (*new == '\'' || *new == '\"')
	{
		if (*new == '\'' && cmp_quo(del, ft_strdup((const char *)new), SQUO))
			return (true);
		if (*new == '\"' && cmp_quo(del, ft_strdup((const char *)new), DQUO))
			return (true);
		return (false);
	}
	while (del[i])
	{
		if ((!del[i] && new[i]) || (new[i] != del[i]))
			return (false);
		i++;
	}
	return (true);
}

int	here_doc(char *delimiter, int out, int *err, t_cleanup *cl)
{
	char	*line;
	char	*new;

	line = NULL;
	while ("heredoc")
	{
		new = readline("> ");
		if (new)
			new = expand_cont(new, err, cl);
		else
			ft_putendl_fd("minishell: warning:\
here-document delimited by end-of-file", 2);
		if (new == NULL || cmp_del(delimiter, new))
			break ;
		if (*err)
			return (err_msg("heredoc expand error"), 0);
		line = str_realloc(line, ft_strlen(line) + ft_strlen(new) + 2, \
		sizeof(char));
		ft_strcat(line, new);
		line[ft_strlen(line)] = '\n';
		free(new);
	}
	g_signal = 0;
	write (out, line, ft_strlen(line));
	return (free(line), free(new), 0);
}

/*
*	if there is another stdo red then i shouldn't restore stdo, or keep the file
*	fd, restore stdo then redup2 stdo with the file fd, this only applies to 
*	stdout
*/
int	exe_herd(t_astn *node, int pos, t_cleanup *cl)
{
	int		err;
	int		out;
	t_pipe	p;

	out = -1;
	if (!isatty(STDOUT_FILENO))
		out = dup(STDOUT_FILENO);
	err = 0;
	if (pipe(p.pipe) == -1)
		return (err_msg("exe_herd pipe fail"), 0);
	res_fd(STDOUT_FILENO, STDO, cl);
	res_fd(STDIN_FILENO, STDI, cl);
	here_doc(node->token[pos + 1]->content, p.pipe[1], &err, cl);
	if (err)
		return (close_pipe(p.pipe), res_fd(STDOUT_FILENO, STDO, cl), 1);
	if (out != -1)
		return (dup2(out, STDOUT_FILENO), fd_red(&p, RED_HERD), close(out), 1);
	fd_red(&p, RED_HERD);
	return (1);
}
