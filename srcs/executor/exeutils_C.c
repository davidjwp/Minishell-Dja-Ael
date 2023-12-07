/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeutils_C.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/04 14:11:58 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//find the shell environment variable by name
//t_env	*find_env(const char *name, t_env *sh_env)
//{
//	t_env	*tmp;

//	tmp = sh_env;
//	if (sh_env == NULL)
//		return (NULL);
//	if (cmp(name, sh_env->name) == true)
//		return (sh_env);
//	sh_env = sh_env->next;
//	while (cmp(name, sh_env->name) != true && sh_env != tmp)
//		sh_env = sh_env->next;
//	if (sh_env == tmp)
//		return (NULL);
//	return (sh_env);
//}

char	*path_cmd(const char *cmd)
{
	char	*path;
	int		len;


	len = ft_strlen(cmd);
	path = malloc(sizeof(char) * (len + 1));
	path[len] = 0;
	while (len--)
		path[len] = cmd[len];
	return (path);
}

void	signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
}