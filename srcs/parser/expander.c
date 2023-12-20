/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:10:39 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/20 12:22:01 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_exst(int status, int *len)
{
	int		tmp;
	char	*exst;
	int		l_len;

	*len = 0;
	tmp = status;
	if (!tmp)
		++*len;
	while (tmp)
	{
		tmp /= 10;
		++*len;
	}
	l_len = *len;
	exst = ft_calloc((l_len + 1), sizeof(char));
	if (exst == NULL)
		return (NULL);
	while (--l_len)
	{
		exst[l_len] = (status % 10) + 48;
		status /= 10;
	}
	exst[l_len] = (status % 10) + 48;
	return (exst);
}

char	*exst_token(char *content, int *error, size_t pos, t_cleanup *cl)
{
	char		*exst;
	char		*new;
	int			len;
	size_t		in;

	in = -1;
	if (cl->status > 255)
		exst = expand_exst(WEXITSTATUS(cl->status), &len);
	else
		exst = expand_exst(cl->status, &len);
	if (exst == NULL)
		return (*error = 1, NULL);
	new = ft_calloc(((ft_strlen(content) - 2) + len) + 1, sizeof(char));
	if (new == NULL)
		return (free(exst), *error = 1, NULL);
	while (++in < pos)
		new[in] = content[in];
	ft_strcat(new, exst);
	ft_strcat(new, &content[in + 2]);
	return (free(content), free(exst), new);
}

int	exp_newlen(char *content, size_t len, t_env *var)
{
	int	i;

	i = len + 1;
	if (varischar(&content[len]))
		return (len += ft_strlen(&content[len]));
	while (is_alnum(content[i]) && content[i] && !(content[i] >= 48 && \
	content[i] <= 57))
		i++;
	if (content[i] >= 48 && content[i] <= 57)
		i++;
	if (var != NULL)
		len += ft_strlen(var->value);
	return (len += (ft_strlen(&content[i]) + 1));
}

char	*var_token(char *cont, char *new, t_env *var, t_exp va)
{
	if (*va.err || new == NULL)
		return (*va.err = 1, NULL);
	while (va.i < va.pos)
		new[va.y++] = cont[va.i++];
	if (varischar(&cont[va.pos]))
		new[va.y++] = cont[va.i++];
	else if (var == NULL)
	{
		va.i++;
		while (cont[va.i] && is_alnum(cont[va.i]) && \
		!(cont[va.pos + 1] >= 48 && cont[va.pos + 1] <= 57))
			va.i++;
		if (cont[va.pos + 1] >= 48 && cont[va.pos + 1] <= 57)
			va.i++;
	}
	else
	{
		ft_strcat(new, var->value);
		va.y += ft_strlen(var->value);
		va.i += ft_strlen(var->name) + 1;
	}
	while (cont[va.i])
		new[va.y++] = cont[va.i++];
	return (free(cont), new);
}

//this the main expand function, i reuse this for heredocs
char	*expand_cont(char *content, int *error, t_cleanup *cl)
{
	size_t	pos;
	t_env	*var;

	pos = 0;
	if (content == NULL)
		return (NULL);
	while (find_var(content, &pos))
	{
		if (type(content, pos) == VARE)
		{
			var = exp_findenv(&content[pos + 1], error, cl->env);
			content = var_token(content, ft_calloc(exp_newlen(content, \
			pos, var), sizeof(char)), var, (t_exp){0, 0, pos, error});
		}
		else
			content = exst_token(content, error, pos, cl);
		if (*error)
			return (content);
		pos = 0;
	}
	return (content);
}
