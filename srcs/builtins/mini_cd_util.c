/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:01:49 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/18 14:36:15 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	**malloc_token(void)
{
	t_token	**token;
	int		i;

	token = NULL;
	i = 0;
	token = malloc(sizeof(t_token *) * 4);
	if (!token)
		return (token);
	while (token && i < 4)
	{
		token[i] = malloc(sizeof(t_token));
		if (!token[i++])
			return (token);
	}
	return (token);
}

void	free_token(t_token **token)
{
	int	i;

	i = 0;
	while (token && i < 4)
	{
		if (token[i]->content)
			free(token[i]->content);
		free(token[i++]);
	}
	free(token);
}

void	mini_cd_exec(char *join_cd, int *exit_status)
{
	DIR	*dir;

	dir = NULL;
	dir = opendir(join_cd);
	if (join_cd && dir && access(join_cd, F_OK) != -1)
		chdir(join_cd);
	else if (join_cd && access(join_cd, F_OK) == -1)
		*exit_status = mini_cd_error_1(NDIR, join_cd, 1);
	else if (join_cd && access(join_cd, R_OK) == -1)
		*exit_status = mini_cd_error_1(NPERM, join_cd, 1);
	else if (join_cd)
		*exit_status = mini_cd_error_1(NOT_DIR, join_cd, 1);
	if (join_cd && dir)
		closedir(dir);
}

t_env	*srch_env(t_env *env, char *str)
{
	t_env	*tmp_env;

	if (!ft_strcmp(str, env->name))
		return (env);
	env = env->next;
	tmp_env = env;
	while (env->next != tmp_env)
	{
		if (!ft_strcmp(str, env->name))
			return (env);
		env = env->next;
	}
	return (NULL);
}
