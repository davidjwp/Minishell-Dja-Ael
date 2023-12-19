/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_B.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:29:05 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/14 19:14:43 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_alnum(char c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) \
	|| c == '_')
		return (true);
	return (false);
}

bool	varischar(char *str)
{
	if (!is_alnum(str[1]) && str[1] != '?')
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

//searches 
t_env	*exp_findenv(char *name, int *err, t_env *sh_env)
{
	t_env	*tmp;
	char	*trim;
	int		len;

	len = 0;
	while (is_alnum(name[len]) && name[len])
		len++;
	if (*name >= 48 && *name <= 57)
		len = 1;
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

//iterates through the content and looks for a valid variable or an exst
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
