/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:54:21 by lazanett          #+#    #+#             */
/*   Updated: 2023/12/18 15:41:46 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*get_prev_env(t_env *env)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (env->next != tmp_env)
		env = env->next;
	return (env);
}

static int	unset_cmp_token_to_env(t_cleanup *cl, char *content)
{
	t_env	*prev_env;
	int		i;

	i = 0;
	if (!cl->env)
		return (0);
	if (cl->env->next == cl->env)
	{
		while (cl->env->cl && cl->env->cl[i])
			free(cl->env->cl[i++]);
		return (free(cl->env->cl), free(cl->env), cl->env = NULL, 1);
	}
	prev_env = get_prev_env(cl->env);
	if (!ft_strcmp(cl->env->name, content))
	{
		while (cl->env->cl && cl->env->cl[i])
			free(cl->env->cl[i++]);
		free(cl->env->cl);
		prev_env->next = cl->env->next;
		free(cl->env);
		cl->env = prev_env->next;
		return (1);
	}
	return (0);
}

int	mini_unset(t_cleanup *cl, t_token **token)
{
	t_env	*first_env;
	int		i;

	first_env = cl->env;
	i = 1;
	if (get_token_len(token) > 1)
	{
		while (token && token[i] && token[i]->content)
		{
			first_env = cl->env;
			while (cl->env)
			{
				if (unset_cmp_token_to_env(cl, token[i]->content))
					break ;
				else if (cl->env->next == first_env)
					break ;
				cl->env = cl->env->next;
			}
			i++;
		}
	}
	return (0);
}

int	unset_vintab(char *av, char **tab)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(av);
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], av, len) && (tab[i][ft_strlen(av)] == '='))
			return (i);
		i++;
	}
	return (-1);
}
