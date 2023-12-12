/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerutils_A.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:31:16 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/10 20:26:32 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*	lexerutils_A contains the following functions :
*	type(), _pipe(), cmp(), check_spec(), check_quote()
*/
//returns type for first pointed chars in *s
inline int	type(const char *s, size_t i)
{
	if (!s[i])
		return (0);
	if (s[i] < 33 && s[i] > 0)
		return (SEPR);
	if (s[i] == '\"')
		return (DQUO);
	if (s[i] == '\'')
		return (SQUO);
	if (s[i] == '|')
		return (PIPE);
	if (s[i] == '>' && s[i + 1] == '>')
		return (APRD);
	if (s[i] == '<' && s[i + 1] == '<')
		return (HERD);
	if (s[i] == '$' && s[i + 1] == '?')
		return (EXST);
	if (s[i] == '$')
		return (VARE);
	if ((s[i] == '>' && s[i + 1] != '>'))
		return (REDR);
	if ((s[i] == '<' && s[i + 1] != '<'))
		return (REDL);
	return (WORD);
}

//finds first pipe in input
bool	_pipe(const char *input)
{
	bool	open;
	int		index;
	int		t;

	t = 0;
	index = 0;
	open = false;
	while (input[index] != 0)
	{
		if (type(input, index) && !(type(input, index) % 5) && !open)
		{
			open = true;
			t = type(input, index);
		}
		else if (type(input, index) == t && open)
			open = false;
		if (type(input, index) == PIPE && !open)
			return (true);
		else
			index += 1;
	}
	return (false);
}

//cmp two strings returns bool if same string or not 
bool	cmp(const char *content, const char *input)
{
	size_t	i;

	i = 0;
	while (content[i] == input[i] && (content[i] && input[i]) && \
	type(input, i) != SEPR)
		i++;
	if ((!content[i] && !input[i]) || (type(input, i) == SEPR && !content[i]))
		return (true);
	return (false);
}

/*
*	iterates size_t *i depending on the special character type
*/
bool	check_spec(const char *input, size_t *i)
{
	int	t;

	t = type(input, *i);
	if (t == VARE)
	{
		while (t != SEPR && input[*i])
		{
			if (t == REDR || t == REDL || t == APRD || t == HERD || t == EXST)
				*i += 2;
			else
				*i += 1;
			t = type(input, *i);
		}
	}
	else if (t == EXST || t == HERD || t == APRD)
		*i += 2;
	else
		*i += 1;
	return (true);
}

/*
*   will check for unclosed quotes and iterate index *i which corresponds to 
*   length in it_token's higher scope, this also gets the length of the token
*	- this is possibly deprecated because my expand will expand correctly even
*		when unclosed, so there is no need to send an error msg 
*/
bool	check_quote(const char *input, size_t *i)
{
	bool	open;
	int		t;

	open = false;
	while (input[*i])
	{
		if (type(input, *i) == SEPR && !open)
			break ;
		if (type(input, *i) && !(type(input, *i) % 5) && !open)
			t = type(input, *i);
		if (type(input, *i) == t && !open)
			open = true;
		else if (type(input, *i) == t && open)
			open = false;
		*i += 1;
	}
	if (!input[*i] && open)
		return (err_msg("unclosed quote"), false);
	return (true);
}