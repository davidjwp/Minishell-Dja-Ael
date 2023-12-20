/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:03:47 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/20 20:56:12 by ael-malt         ###   ########.fr       */
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

char	*join_token_u(t_token **token, t_cleanup *cl, char *join_str, char *tmp)
{
	int		i;

	i = 2;
	while (token && token[i] && token[i]->content)
	{
		tmp = ft_strjoin(join_str, token[i]->content);
		free(join_str);
		if (token[i + 1] && token[i + 1]->content)
		{
			join_str = ft_strjoin(tmp, " ");
			free(tmp);
		}
		else
			join_str = tmp;
		i++;
	}
	join_str = check_case(join_str, cl);
	return (join_str);
}

static char	*join_token(t_token **token, t_cleanup *cl)
{
	char	*join_str;
	char	*tmp;

	join_str = NULL;
	if (token[1] && token[1]->content)
		tmp = ft_strdup(token[1]->content);
	if (token[2] && token[2]->content)
	{
		join_str = ft_strjoin(tmp, " ");
		if (tmp)
			free(tmp);
		join_str = join_token_u(token, cl, join_str, tmp);
	}
	else
		join_str = tmp;
	return (join_str);
}

int	mini_cd(t_cleanup *c, t_token **t)
{
	int		exit_status;
	char	*cw;
	char	*join_cd;

	join_cd = NULL;
	exit_status = 0;
	cw = NULL;
	cw = getcwd(cw, 0);
	if (!t[1] && !srch_env(c->env, "HOME"))
		return (free(cw), ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	else if (get_token_len(t) == 1 && srch_env(c->env, "HOME"))
		chdir(srch_env(c->env, "HOME")->value);
	else if (get_token_len(t) > 1)
	{
		if (cw || (ft_strcmp(t[1]->content, "-") && find_env("OLDPWD", c->env)))
		{
			join_cd = join_token(t, c);
			if (ft_strcmp(join_cd, "-"))
				mini_cd_exec(join_cd, &exit_status);
		}
		else
			ft_putendl_fd("chdir: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory", 2);
	}
	return (mini_export_pwd(cw, c), free(join_cd), exit_status);
}
