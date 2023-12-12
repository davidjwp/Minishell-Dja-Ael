/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:25:49 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/10 18:32:51 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	insert_new_env_entry(t_cleanup *cl, char *content, t_env *tmp_env)
{
	t_env	*new_env_entry;

	new_env_entry = env_node(content);
	cl->env->next = new_env_entry;
	new_env_entry->next = tmp_env;
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

int	mini_env(t_env	*env)
{
	int	len;

	len = get_env_len(env) + 1;
	while (len--)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
