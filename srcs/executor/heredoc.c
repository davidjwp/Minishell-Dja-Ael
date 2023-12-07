/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:03:33 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/07 19:04:55 by djacobs          ###   ########.fr       */
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

//this is the part that reads input 
int	here_doc(char *delimiter, int out, int *err, t_cleanup *cl)
{
	char	*line;
	char	*new;

	signals();
	line = NULL;
	restore_fd(STDOUT_FILENO, STDO, cl);
	while ("heredoc")
	{
		new = readline("> ");
		if (*new && !ft_strncmp(delimiter, new, ft_strlen(new)))
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

int	exe_herd(t_astn *node, int pos, t_env *sh_env, t_cleanup *cl)
{
	t_pipe	p;
	int		err;

	err = 0; 
	if (pipe(p.pipe) == -1)
		return (err_msg("exe_herd pipe fail"), 0);
	here_doc(get_herd(node->token, &(int){0})->content, p.pipe[1], &err, cl);
	if ((node->token[0]->type == HERD && node->token[pos + 1] == NULL) || err)
		return (close_pipe(p.pipe), restore_fd(STDOUT_FILENO, STDO, cl), 1);



	p.l_pid = fork();
	if (p.l_pid == -1)
		return (err_msg("exe_herd fork fail"), 0);
	if (!p.l_pid)
	{
		if (!fd_redirection(&p, RED_PIP))
			return (clean_up(cl, CL_ALL), exit(EXIT_FAILURE), 0);
		//if (!(node->token[0]->type % 11))
		//	return (exec_builtin(node, cl), dup2(STDOUT_FILENO, cl->fds->fd),
		//	clean_up(cl, CL_ALL), exit(EXIT_SUCCESS), 0);
		execute(node, sh_env, cl);
		exit(EXIT_SUCCESS);
	}
	return (wait(&cl->status), restore_fd(STDOUT_FILENO, STDO, cl), 1);
}