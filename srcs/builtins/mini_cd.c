/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:03:47 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/09 16:58:11 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	mini_export_pwd(char *cwd, t_cleanup *cl)
{
	t_token	**token;
	int		i;

	i = 0;
	token = malloc(sizeof(t_token *) * 4);
	if (!token)
		return ;
	while(token && i < 4)
	{
		token[i] = malloc(sizeof(t_token));
		if (!token[i++])
			return ;
	}
	i = 0;
	token[0]->content = ft_strdup("export");
	if (cwd && getcwd(NULL, 0))
	{
		token[1]->content = ft_strjoin("OLDPWD=", cwd);
		token[2]->content = ft_strjoin("PWD=", getcwd(NULL, 0));
	}
	else if (!cwd && getcwd(NULL, 0))
	{
		token[1]->content = ft_strjoin("PWD=", getcwd(NULL, 0));
		token[2]->content = NULL;
	}
	free(cwd);
	token[3]->content = NULL;
	if (getcwd(NULL, 0))
		mini_export(cl, token);
	// printf("token[1]->content: %s\n", token[1]->content);
	while(token && i < 4)
	{
		if (token[i]->content)
			free(token[i]->content);
		free(token[i++]);
	}
	free(token);
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
// ESTALE
// bash: ../: Stale file handle
// ESTALE
// shell-init: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory

static char *join_split_command(t_token **token, t_cleanup *cl)
{
	char	*join_str;
	int	i;

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
	(void) cl;
	(void) token;
	int		exit_status;
	char	*cwd;
	char	*join_cd;

	cwd = NULL;
	join_cd = NULL;
	exit_status = 0;
	cwd = getcwd(cwd, 0);
	if (!token[1] && !srch_env(cl->env, "HOME"))
		ft_putendl_fd("minishell: cd: HOME not set", 2);
	else if (get_token_len(token) == 1 && srch_env(cl->env, "HOME"))
		chdir(srch_env(cl->env, "HOME")->value);
	else if (get_token_len(token) > 1)
	{
		if (cwd)
		{
			// printf("ici\n");
			join_cd = join_split_command(token, cl);
			if (ft_strcmp(join_cd, "-"))
				mini_cd_error(join_cd, &exit_status);
		}
			else
			{
				ft_putendl_fd("chdir: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
			}
	}
	mini_export_pwd(cwd, cl);
	return (free(join_cd), exit_status);
}
