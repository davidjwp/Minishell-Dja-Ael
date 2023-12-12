/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:03:33 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/12 20:28:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*get_herd(t_token **tokens, int *pos)
{
	while (tokens[*pos] != NULL && tokens[*pos]->type != HERD)
		*pos += 1;
	if (tokens[*pos] == NULL)
		return (NULL);
	return (tokens[*pos + 1]);
}

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

bool	cmp_del(char *del, char *new)
{
	int	i;

	i = 0;
	if (!new[i])
		return (false);
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

	signals();
	line = NULL;
	while ("heredoc")
	{
		new = readline("> ");
		if (new == NULL || cmp_del(delimiter, new))
			break ;
		new = expand_cont(new, err, cl);
		if (*err)
			return (err_msg("heredoc expand error"), 0);
		line = str_realloc(line, ft_strlen(line) + ft_strlen(new) + 2, \
		sizeof(char));
		ft_strcat(line, new);
		line[ft_strlen(line)] = '\n';
		free(new);
	}
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