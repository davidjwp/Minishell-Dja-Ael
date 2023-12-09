/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:28:26 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/09 16:02:52 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	mini_cd_error_1(int err_type, char *param, int err)
{
	if (err_type == NDIR)
		ft_putstr_fd("minishell: No such file or directory: ", 2);
	else if (err_type == NPERM)
		ft_putstr_fd("minishell: permission denied: ", 2);
	else if (err_type == NOT_DIR)
		ft_putstr_fd("minishell: Not a directory: ", 2);
	ft_putendl_fd(param, 2);
	return (err);
}

void	mini_cd_error(char *join_cd, int *exit_status)
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

int		mini_export_error(char *arg)
{
	char	*value;
	int		i;
	int		j;
	
	i = ft_strchr_i(arg, '=');
	if (i == -1)
		i = ft_strlen(arg);
	value = malloc(sizeof(char) * (i + 1));
	if (!value)
		return(1);
	j = 0;
	while (j <= i)
	{
		value[j] = arg[j];
		j++;
	}
	value[j] = '\0';
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd("' not an identifier\n", 2);
	return (1);
}

