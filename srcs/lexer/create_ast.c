/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/10 20:23:08 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*	create_ast.c contains the following functions :
*	nbr_token(), get_token(), ast_cmd(), ast_pipe(), create_ast()
*/
//counts the number of tokens until a pipe or redirection is found
int	nbr_token(const char *input, size_t l_ind, int tokcnt)
{
	int		t;

	if (!*input)
		return (0);
	t = type(input, l_ind);
	while (t != PIPE && input[l_ind])
	{
		it_sep(input, &l_ind);
		t = type(input, l_ind);
		if (!input[l_ind])
			break ;
		else if (t != PIPE)
			tokcnt += 1;
		if (!it_token(input, &l_ind))
			return (tokcnt = 0, 0);
	}
	return (tokcnt);
}

//returns the token struct with allocated content and type + length
t_token	*get_token(const char *input, size_t *l_ind, t_token *token, int *err)
{
	token->len = 0;
	if (!it_sep(input, l_ind))
		return (NULL);
	token->type = get_token_type((char *)&input[*l_ind]);
	token->content = get_content(input, l_ind, token, err);
	if (*err || token->content == NULL)
		return (NULL);
	return (token);
}

//creates a command node, the node contains the tokens and links to other nodes 
t_astn	*ast_cmd(const char *input, size_t *g_ind, t_cms c, int *err)
{
	size_t	l_ind;
	int		nbr;
	int		i;

	i = 0;
	l_ind = 0;
	nbr = nbr_token(input, 0, 0);
	if (!init_node(c.node, nbr, c.parent, err) || !nbr)
		return (free(c.node), NULL);
	while (nbr != 0)
	{
		c.node->token[i] = (t_token *)malloc(sizeof(t_token));
		if (c.node->token[i] == NULL)
			return (free_tok(c.node->token, i), free(c.node), *err = 1, NULL);
		c.node->token[i] = get_token(input, &l_ind, c.node->token[i], err);
		if (*err)
			return (free_tok(c.node->token, i), free(c.node), NULL);
		nbr -= 1;
		i++;
	}
	*g_ind += l_ind;
	return (c.node);
}

/*
*	creates a pipe node while cutting the left and right side of 
*	the input from the pipe
*/
bool	ast_pipe(const char *in, size_t *g_ind, t_astn *pipe, t_astn *p)
{
	int	error;

	error = 0;
	pipe->left = create_ast(cut_l(in, C_PIPE), g_ind, &error, pipe);
	if (error)
		return (false);
	pipe->token = NULL;
	pipe->type = PIPE;
	pipe->parent = p;
	*g_ind += 1;
	pipe->right = create_ast(cut_r(in, C_PIPE), g_ind, &error, pipe);
	if (error)
		return (false);
	return (true);
}

//creates the abstract syntax tree via descending recursion
t_astn	*create_ast(const char *input, size_t *g_ind, int *error, t_astn *par)
{
	t_astn	*node;

	node = malloc(sizeof(t_astn));
	if (node == NULL)
		return (*error = 1, err_msg("create ast malloc failed"), NULL);
	if (_pipe(input))
	{
		if (!ast_pipe(input, g_ind, node, par))
			return (*error = 1, free(node), NULL);
	}
	else
		node = ast_cmd(input, g_ind, (t_cms){par, node}, error);
	if (*error && par != NULL)
		return (free((char *)input), NULL);
	if (par == NULL)
		return (node);
	return (free((char *)input), node);
}
