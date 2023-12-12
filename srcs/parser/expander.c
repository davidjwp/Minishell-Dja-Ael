/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidjwp <davidjwp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:10:39 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/11 18:17:54 by davidjwp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	varischar(char *str)
{
	if (str[1] <= 33 || str[1] == 34 || str[1] == 39)
		return (true);
	return (false);
}

//check on that idk
bool	qisclose(char *str, bool open)
{
	int	t;
	int	i;

	i = 1;
	t = type(str, 0);
	if (open)
		return (true);
	while (str[i])
	{
		if (type(str, i) == t && !open)
			return (true);
		i++;
	}
	return (false);
}

t_env	*exp_findenv(char *name, int *err, t_env *sh_env)
{
	t_env	*tmp;
	char	*trim;
	int		len;

	len = 0;
	while (type(name, len) != SEPR && !(type(name, len) && \
	!(type(name, len) % 5)) && name[len] != '$' && name[len])
		len++;
	trim = ft_calloc((len + 1), sizeof(char));
	if (trim == NULL)
		return (err_msg("find_env malloc fail"), *err = 1, NULL);
	while (len--)
		trim[len] = name[len];
	tmp = sh_env;
	while (ft_strcmp(trim, tmp->name))
	{
		tmp = tmp->next;
		if (tmp == sh_env)
			break ;
	}
	if (!ft_strcmp(trim, tmp->name))
		return (free(trim), tmp);
	return (free(trim), NULL);
}

//iterates through the content and looks for a variable or an exst
bool	find_var(char *cont, size_t *pos)
{
	bool	dq;
	bool	sq;

	dq = false;
	sq = false;
	while (cont[*pos])
	{
		if (type(cont, *pos) == DQUO && !dq && !sq && qisclose(&cont[*pos], dq))
			dq = true;
		else if (type(cont, *pos) == DQUO && dq)
			dq = false;
		if (type(cont, *pos) == SQUO && !sq && !dq && qisclose(&cont[*pos], sq))
			sq = true;
		else if (type(cont, *pos) == SQUO && sq)
			sq = false;
		if ((cont[*pos] == '$' && !varischar(&cont[*pos])) \
		&& (dq || (!sq && !dq)))
			return (true);
		*pos += 1;
	}
	return (false);
}

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
		return (len += ft_strlen (&content[len]));
	while (!(type(content, i) && !(type(content, i) % 5)) && \
	type(content, i) != SEPR && content[i] != '$' && content[i])
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
		while (type(cont, va.i) != SEPR && cont[va.i] &&\
		!(type(cont, va.i) && !(type(cont, va.i) % 5)))
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
	// content = rem_quotes(content, error, 0, 0);
	// if (*error)
	// 	return (free(content), NULL);
	return (content);
}
