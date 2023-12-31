/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeutils_C.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/14 15:35:14 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*path_cmd(const char *cmd)
{
	char	*path;
	int		len;

	len = ft_strlen(cmd);
	path = malloc(sizeof(char) * (len + 1));
	path[len] = 0;
	while (len--)
		path[len] = cmd[len];
	return (path);
}

void	free_tokens(t_astn *node, int pos)
{
	free(node->token[pos]->content);
	free((t_token *)node->token[pos]);
	free(node->token[pos + 1]->content);
	free((t_token *)node->token[pos + 1]);
}

bool	red_herd(t_token **tok)
{
	int	i;

	i = 0;
	while (tok[i] != NULL)
	{
		if (tok[i]->type == HERD || tok[i]->type == REDR || tok[i]->type == \
		REDL || tok[i]->type == APRD)
			return (true);
		i++;
	}
	return (false);
}

void	get_pos(t_token **tokens, int *pos)
{
	while (tokens[*pos] != NULL)
	{
		if (tokens[*pos]->type == HERD || ((tokens[*pos]->type && \
		!(tokens[*pos]->type % 4))))
			return ;
		*pos += 1;
	}
}

void	reset_fds(t_cleanup *cl)
{
	res_fd(STDIN_FILENO, STDI, cl);
	res_fd(STDOUT_FILENO, STDO, cl);
}
