/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:28:26 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:40:25 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*mini_bt_errors(t_cleanup *cl, int err_type, char *param, int err)
{
	cl->status = err;
	if (err_type == QUOTE)
		ft_putstr_fd("minishell: error while looking for matching quote", 2);
	else if (err_type == NDIR)
		ft_putstr_fd("minishell: No such file or directory: ", 2);
	else if (err_type == NPERM)
		ft_putstr_fd("minishell: permission denied: ", 2);
	else if (err_type == NCMD)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (err_type == DUPERR)
		ft_putstr_fd("minishell: dup2 failed", 2);
	else if (err_type == FORKERR)
		ft_putstr_fd("minishell: fork failed", 2);
	else if (err_type == PIPERR)
		ft_putstr_fd("minishell: error creating pipe", 2);
	else if (err_type == MEM)
		ft_putstr_fd("minishell: no memory left on device", 2);
	else if (err_type == IS_DIR)
		ft_putstr_fd("minishell: Is a directory: ", 2);
	else if (err_type == NOT_DIR)
		ft_putstr_fd("minishell: Not a directory: ", 2);
	ft_putendl_fd(param, 2);
	return (NULL);
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

