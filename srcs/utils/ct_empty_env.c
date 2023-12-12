/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ct_empty_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:05:13 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/12 16:33:00 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*cr_empty_env(void)
{
	t_env	*sh_env;
	t_env	*tmp_env;
	char	*cwd;
	char	*tmp;

	cwd = NULL;
	tmp = NULL;
	cwd = getcwd(cwd, 0);
	if(cwd)
	{
		tmp = ft_strdup("PWD=");
		tmp = ft_strjoin (tmp, cwd);
		sh_env = env_node(tmp);
		free(tmp);
		sh_env->next = env_node("SHLVL=1");
	}
	else
		sh_env = env_node("SHLVL=1");
	tmp_env = sh_env;
	sh_env = sh_env->next;
	sh_env->next = env_node("_=/usr/bin/env");
	sh_env = sh_env->next;
	sh_env->next = tmp_env;
	return(free(cwd), sh_env);
}
