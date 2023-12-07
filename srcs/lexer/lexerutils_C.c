/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerutils_C.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:47:16 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/07 13:07:27 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*	lexerutils_C contains the following functions :
*	nbr_token(), free_tok(), free_cmd_node(), cut_len()
*/
/*
*	counts the number of tokens until a pipe or redirection is found
*		-there is no need to actually stop until a pipe or redirection is found
*			because at this point the input is isolated from them
*/
int	nbr_token(const char *input, size_t l_ind, int tokcnt)
{
	int		t;

	if (!*input)
		return (0);
	t = type(input, l_ind);
	while (t != REDL && t != REDR && t != APRD && t != PIPE && input[l_ind])
	{
		it_sep(input, &l_ind);
		t = type(input, l_ind);
		if (!input[l_ind])
			break ;
		else if (t != REDL && t != REDR && t != APRD && t != PIPE)
			tokcnt += 1;
		if (!it_token(input, &l_ind))
			return (tokcnt = 0, 0);
	}
	return (tokcnt);
}

/*
*	free the tokens up to last, only used while assigning allocated token
*	structures to the token struct array so that it only frees what has been
*	allocated 
*/
void	free_tok(t_token **tokens, int last)
{
	int	i;

	i = 0;
	while (i < last)
	{
		free(tokens[i]->content);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

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
