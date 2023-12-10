/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerutils_C.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:47:16 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/10 20:28:39 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*	lexerutils_C contains the following functions :
*	free_cmd_node(), cut_len(), init_node(), cut_r(), cut_l()
*/
//frees the whole command node
void	free_cmd_node(t_astn *cmd, bool cmdbool)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return ;
	while (cmd->token[i] != NULL)
	{
		free(cmd->token[i]->content);
		free((t_token *)cmd->token[i]);
		i++;
	}
	free(cmd->token);
	if (cmdbool)
		free(cmd);
}

//gets the length of the cut input
int	cut_len(const char *input, int flag)
{
	int	len;
	int	t;

	len = 0;
	t = type(input, len);
	if (flag == C_PIPE)
	{
		while (input[len] && type(input, len) != PIPE)
			len++;
	}
	else if (flag == C_RED)
	{
		while (input[len] && (!t || t % 4 != 0))
		{
			if (t == HERD)
				len += 2;
			else
				len += 1;
			t = type(input, len);
		}
	}
	return (len);
}

//initializes node members
int	init_node(t_astn *node, int nbr, t_astn *p, int *error)
{
	if (!nbr)
		return (0);
	node->type = COMD;
	node->token = (t_token **)malloc(sizeof(t_token) * (nbr + 1));
	if (node->token == NULL)
		return (free(node), *error = 1, err_msg("init alloc fail"), 0);
	node->left = NULL;
	node->right = NULL;
	node->parent = p;
	node->token[nbr] = NULL;
	return (1);
}

//cuts the right side of the input depending on which type
const char	*cut_r(const char *input, int flag)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = cut_len(input, flag);
	if (type(input, len) == 4)
		len++;
	while (input[++len])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	str[i] = 0;
	len -= i;
	i = -1;
	while (input[len] != 0)
		str[++i] = input[len++];
	return (str);
}

//cuts the left side of the input depending on which type
const char	*cut_l(const char *input, int flag)
{
	char	*str;
	int		len;
	int		i;

	i = -1;
	len = cut_len(input, flag);
	str = malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	while (++i < len)
		str[i] = input[i];
	return (str);
}
