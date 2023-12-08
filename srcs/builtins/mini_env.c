/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:25:49 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/08 20:08:36 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		printf("%s=%s\n",env->name,env->value);
		env = env->next;
	}
	return (0);
}
