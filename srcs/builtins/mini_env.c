/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:25:49 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 20:25:48 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		mini_env(t_env	*env)
{
	t_env *tmp;

	tmp = env;
	while (env)
	{
		printf("%s=%s\n",env->name,env->value);
		env = env->next;
		if (env == tmp)
			break ;
	}
	return (0);
}
