/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:03:47 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:33:16 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	mini_cd_error(char *join_cd, int *exit_status)
{
	DIR	*dir;

	dir = NULL;
	dir = opendir(join_cd);
	if (join_cd && dir && access(join_cd, F_OK) != -1)
		chdir(join_cd);
	else if (join_cd && access(join_cd, F_OK) == -1)
	{
		mini_perror(NDIR, join_cd, 1);
		*exit_status = 1;
	}
	else if (join_cd && access(join_cd, R_OK) == -1)
	{
		mini_perror(NPERM, join_cd, 1);
		*exit_status = 1;
	}
	else if (join_cd)
	{
		mini_perror(NOT_DIR, join_cd, 1);
		*exit_status = 1;
	}
	if (join_cd && dir)
		closedir(dir);
}

static void	mini_export_pwd(char *cwd, t_expand *ex)
{
	char	**pwd;

	pwd = malloc(sizeof(char *) * 4);
	if (!pwd)
		return ;
	pwd[0] = ft_strdup("export");
	if (cwd)
	{
		pwd[1] = ft_strjoin("OLDPWD=", cwd);
		pwd[2] = ft_strjoin("PWD=", getcwd(NULL, 0));
	}
	else if (getcwd(NULL, 0))
	{
		pwd[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
		pwd[2] = NULL;
	}
	free(cwd);
	pwd[3] = NULL;
	if (getcwd(NULL, 0))
		mini_export(ex, pwd);
	free(pwd[0]);
	free(pwd[1]);
	free(pwd[2]);
	free(pwd);
}

static char	*check_case(char *jcd, t_expand *ex)
{
	if (!strcmp(jcd, ".."))
	{
		free(jcd);
		jcd = ft_strdup("../");
	}
	if (!strcmp(jcd, "-"))
	{
		// ft_printf("nb: %d\n", export_vintab("OLDPWD=", ex->tab));
		if (export_vintab("OLDPWD=", ex->tab) != -1)
		{
			free(jcd);
			jcd = ft_strdup(&ex->tab[export_vintab("OLDPWD=", ex->tab)][7]);
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

static char *join_split_command(char **split_command, t_expand *ex)
{
	char	*join_str;
	int	i;

	join_str = ft_strdup(split_command[0]);
	if (split_command[1])
		join_str = ft_strjoin(join_str, " ");
	i = 1;
	while (split_command && split_command[i])
	{
		join_str = ft_strjoin(join_str, split_command[i]);
		if (split_command[i + 1])
			join_str = ft_strjoin(join_str, " ");
		i++;
	}
	join_str = check_case(join_str, ex);
	return (join_str);
}

int	mini_cd(t_expand *ex, char **split_command)
{
	int		exit_status;
	char	*cwd;
	char	*join_cd;

	cwd = NULL;
	join_cd = NULL;
	exit_status = 0;
	cwd = getcwd(cwd, 0);
	if (export_vintab("HOME=", ex->tab) == -1 && !split_command[1])
		ft_putendl_fd("minishell: cd: HOME not set", 2);
	else if (ft_matrixlen(split_command) == 1 && 
		export_vintab("HOME=", ex->tab) != 0)
		chdir(&ex->tab[export_vintab("HOME=", ex->tab)][5]);
	else
	{
		if (cwd)
		{
			join_cd = join_split_command(split_command + 1, ex);
			if (ft_strcmp(join_cd, "-"))
				mini_cd_error(join_cd, &exit_status);
		}
		else
		{
			ft_putendl_fd("chdir: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
			ft_putendl_fd("minishell: cd: ../: Stale file handle", 2);
		}
	}
	mini_export_pwd(cwd, ex);	
	return (free(join_cd), exit_status);
}
