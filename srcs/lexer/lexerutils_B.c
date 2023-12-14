/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerutils_B.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:54:51 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/14 15:31:01 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*   lexerutils_B contains the following functions :
*   built_in(), get_token_type(), it_token(), get_content(), free_tok()
*/
//compares the token with all builtin and returns it's builtin type if found
int	built_in(const char *input)
{
	char	*builtin[7];
	int		type[7];
	int		i;

	i = -1;
	while (++i < 8)
	{
		builtin[i] = (char *[8]){"echo", "cd", "pwd", "export", "unset", \
		"env", "exit", NULL}[i];
		type[i] = (int [7]){22, 33, 44, 55, 66, 77, 88}[i];
	}
	i = 0;
	while (builtin[i] != NULL)
	{
		if (cmp(builtin[i], input))
			return (type[i]);
		i++;
	}
	return (WORD);
}

//finds the type for the token, if not special character or builtin then word
int	get_token_type(char *token)
{
	int	builtin;

	if (type(token, 0))
		return (type(token, 0));
	else
	{
		builtin = built_in(token);
		if (builtin)
			return (builtin);
	}
	return (WORD);
}

/*
*	iterates the token while giving length of token, also 
*	iterates over SEPARATORS and checks unclosed quotes 
*/
bool	it_token(const char *input, size_t *l_ind)
{
	if (type(input, *l_ind) == HERD || type(input, *l_ind) == APRD)
		return (*l_ind += 2, true);
	if (type(input, *l_ind) && !(type(input, *l_ind) % 4))
		return (*l_ind += 1, true);
	while (type(input, *l_ind) != SEPR && type(input, *l_ind) != HERD && \
	!(type(input, *l_ind) && !(type(input, *l_ind) % 4)))
	{
		if (type(input, *l_ind) != 0 && !(type(input, *l_ind) % 5))
		{
			if (!check_quote(input, l_ind))
				return (false);
			else
				return (true);
		}
		else
			*l_ind += 1;
		if (!input[*l_ind])
			break ;
	}
	return (true);
}

//returns an allocated string from input for token and gets length of token
char	*get_content(const char *input, size_t *l_ind, t_token *token, int *err)
{
	char	*content;
	int		i;

	i = 0;
	if (!it_token(&input[*l_ind], &token->len))
		return (NULL);
	content = malloc(sizeof(char) * (token->len + 1));
	if (content == NULL)
		return (err_msg("get_content malloc fail"), *err = 1, NULL);
	content[token->len] = 0;
	while (i < (int)token->len)
	{
		content[i] = input[*l_ind];
		*l_ind += 1;
		i++;
	}
	return (content);
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
