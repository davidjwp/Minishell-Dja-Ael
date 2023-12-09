/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:03:33 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/09 15:32:59 by djacobs          ###   ########.fr       */
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
	while (new[i])
	{
		if ((!del[i] && new[i]) || (new[i] != del[i]))
			return (false);
		i++;
	}
	return (true);
}

//this is the part that reads input 
int	here_doc(char *delimiter, int out, int *err, t_cleanup *cl)
{
	char	*line;
	char	*new;

	signals();
	line = NULL;
	restore_fd(STDOUT_FILENO, STDO, cl);
	restore_fd(STDIN_FILENO, STDI, cl);
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

void	free_herd(t_astn *node, int pos)
{
	free(node->token[pos]->content);
	free((t_token *)node->token[pos]);
	free(node->token[pos + 1]->content);
	free((t_token *)node->token[pos + 1]);
}

int	rem_herd(t_astn *node, int pos)
{
	t_token	**new;
	int		len;
	int		i;
	int		y;

	i = 0;
	y = 0;
	len = 0;
	while (node->token[len] != NULL)
		len++;
	len -= 2;
	new = (t_token **)malloc(sizeof(t_token) * (len + 1));
	if (new == NULL)
		return (err_msg("rem_herd malloc fail"), 0);
	new[len] = NULL;
	free_herd(node, pos);
	while (node->token[i] != NULL)
	{
		if (i == pos)
			y += 2;
		new[i] = node->token[y];
		i++;
		y++;
	}
	return (free(node->token), node->token = new, 1);
}

int	exe_herd(t_astn *node, t_env *sh_env, t_cleanup *cl)
{
	int		pos;
	int		err;
	t_pipe	p;

	err = 0;
	pos = 0;
	if (pipe(p.pipe) == -1)
		return (err_msg("exe_herd pipe fail"), 0);
	here_doc(get_herd(node->token, &pos)->content, p.pipe[1], &err, cl);
	if ((node->token[0]->type == HERD && node->token[2] == NULL) || err)
		return (close_pipe(p.pipe), restore_fd(STDOUT_FILENO, STDO, cl), 1);
	if (!rem_herd(node, pos))
		return (close_pipe(p.pipe), restore_fd(STDOUT_FILENO, STDO, cl), 1);
	fd_redirection(&p, RED_HERD);
	execute(node, sh_env, cl);
	restore_fd(STDOUT_FILENO, STDO, cl);
	restore_fd(STDIN_FILENO, STDI, cl);
	return (1);
}