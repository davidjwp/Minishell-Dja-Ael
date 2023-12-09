/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:01:49 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/09 16:04:17 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*srch_env(t_env *env, char *str)
{
	t_env *tmp_env;

	tmp_env = env;
	while (env->next != tmp_env)
	{
		if(!ft_strcmp(str, env->name))
			return(env);
		env = env->next;
	}
	return (NULL);
}
