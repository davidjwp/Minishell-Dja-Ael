/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:03:47 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/20 19:06:40 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	mini_export_pwd(char *cwd, t_cleanup *cl)
{
	t_token	**token;
	char	*new_cwd;

	new_cwd = NULL;
	new_cwd = getcwd(new_cwd, 0);
	if (!new_cwd)
		return (free(cwd));
	token = malloc_token();
	if (!token)
		return ;
	token[0]->content = ft_strdup("export");
	if (cwd && new_cwd)
	{
		token[1]->content = ft_strjoin("OLDPWD=", cwd);
		token[2]->content = ft_strjoin("PWD=", new_cwd);
	}
	else if (!cwd && new_cwd)
	{
		token[1]->content = ft_strjoin("PWD=", new_cwd);
		token[2]->content = NULL;
	}
	token[3]->content = NULL;
	if (token[1] && token[1]->content)
		mini_export(cl, token);
	return (free_token(token), free(cwd), free(new_cwd));
}

static char	*check_case(char *jcd, t_cleanup *cl)
{
	if (!strcmp(jcd, ".."))
	{
		free(jcd);
		jcd = ft_strdup("../");
	}
	if (!strcmp(jcd, "-"))
	{
		if (srch_env(cl->env, "OLDPWD"))
		{
			free(jcd);
			jcd = ft_strdup(srch_env(cl->env, "OLDPWD")->value);
		}
		else
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
	}
	return (jcd);
}

static char	*join_split_command(t_token **token, t_cleanup *cl)
{
	char	*join_str;
	int		i;

	if (token[1] && token[1]->content)
		join_str = ft_strdup(token[1]->content);
	if (token[2] && token[2]->content)
		join_str = ft_strjoin(join_str, " ");
	i = 2;
	while (token && token[i] && token[i]->content)
	{
		join_str = ft_strjoin(join_str, token[i]->content);
		if (token[i + 1] && token[i + 1]->content)
			join_str = ft_strjoin(join_str, " ");
		i++;
	}
	join_str = check_case(join_str, cl);
	return (join_str);
}

int	mini_cd(t_cleanup *cl, t_token **token)
{
	int		exit_status;
	char	*cwd;
	char	*join_cd;

	join_cd = NULL;
	exit_status = 0;
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!token[1] && !srch_env(cl->env, "HOME"))
		return (free(cwd), ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	else if (get_token_len(token) == 1 && srch_env(cl->env, "HOME"))
		chdir(srch_env(cl->env, "HOME")->value);
	else if (get_token_len(token) > 1)
	{
		if (cwd)
		{
			join_cd = join_split_command(token, cl);
			if (ft_strcmp(join_cd, "-"))
				mini_cd_exec(join_cd, &exit_status);
		}
		else
			ft_putendl_fd("chdir: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory", 2);
	}
	return (mini_export_pwd(cwd, cl), free(join_cd), exit_status);
}
