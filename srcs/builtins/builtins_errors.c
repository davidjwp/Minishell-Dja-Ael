/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:28:26 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/18 17:07:02 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	empty_env_export(t_cleanup *cl, t_token **token, int i)
{
	if (!cl->env)
	{
		cl->env = env_node(token[i]->content);
		cl->env->next = cl->env;
	}
}

int	mini_cd_error_1(int err_type, char *param, int err)
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

int	mini_export_error(char *arg)
{
	char	*value;
	int		i;
	int		j;

	i = ft_strchr_i(arg, '=');
	if (i == -1)
		i = ft_strlen(arg);
	value = malloc(sizeof(char) * (i + 2));
	if (!value)
		return (1);
	j = 0;
	while (j <= i)
	{
		value[j] = arg[j];
		j++;
	}
	value[j] = '\0';
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(value, 2);
	free(value);
	ft_putstr_fd("' not an identifier\n", 2);
	return (1);
}
