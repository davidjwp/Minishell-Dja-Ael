/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:25:49 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/18 16:23:39 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	insert_new_env_entry(t_cleanup *cl, char *content, t_env *tmp_env)
{
	t_env	*new_env_entry;

	new_env_entry = env_node(content);
	cl->env->next = new_env_entry;
	new_env_entry->next = tmp_env;
	return (1);
}

int	get_token_len(t_token **token)
{
	int	i;

	i = 0;
	while (token[i] && token[i]->content)
		i++;
	return (i);
}

int	get_env_len(t_env *env)
{
	t_env	*tmp;
	int		len;

	tmp = env;
	len = 0;
	while (env->next != tmp)
	{
		len++;
		env = env->next;
	}
	return (len);
}

static void	show_env(t_cleanup	*cl)
{
	int		len;

	len = get_env_len(cl->env) + 1;
	while (len--)
	{
		printf("%s=%s\n", cl->env->name, cl->env->value);
		cl->env = cl->env->next;
	}
}

int	mini_env(t_cleanup	*cl)
{
	t_env	*first_env;

	first_env = cl->env;
	if (!cl->env)
	{
		cl->env = env_node("_=/usr/bin/env");
		cl->env->next = cl->env;
	}
	else if (cl->env)
	{
		while (cl->env)
		{
			if (export_cmp_token_to_env(cl->env, "_=/usr/bin/env"))
				break ;
			if (cl->env->next == first_env)
			{
				insert_new_env_entry(cl, "_=/usr/bin/env", first_env);
				cl->env = cl->env->next;
				break ;
			}
			cl->env = cl->env->next;
		}
		cl->env = cl->env->next;
	}
	return (show_env(cl), 0);
}
