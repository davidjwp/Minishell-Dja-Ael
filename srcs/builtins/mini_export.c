/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:28:31 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 19:30:36 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	export_vintab(char *cmd, char **tab)
// {
// 	int	i;
// 	int	pos;

// 	i = 0;
// 	pos = ft_strchr_i(cmd, '=');
// 	if (pos == -1)
// 		return (-1);
// 	while (tab[i])
// 	{
// 		if (!ft_strncmp(tab[i], cmd, pos))
// 		{
// 			return (i);
// 		}
// 		i++;
// 	}
// 	return (-1);
// }

// static int	mini_export_verif(char *str)
// {
// 	int	i;
// 	int	equal_present;

// 	i = 1;
// 	if ((str[0] == '=' || ft_isdigit(str[0])) && !(str[i] == '_' || ft_isalpha(str[0])))
// 		return (0);
// 	equal_present = 0;
// 	while (str && str[i])
// 	{
// 		if (!(str[i] == '_' || ft_isalnum(str[i]) || str[i] == '='))
// 			return (0);
// 		if (str[i] == '=')
// 			equal_present = 1;
// 		i++;
// 	}
// 	if (!equal_present)
// 		return (2);
// 	return (1);
// }

// static int	export_no_arg(t_expand *ex)
// {
// 	int	i;

// 	i = 0;
// 	while (ex->tab[i])
// 	{
// 		ft_printf("declare -x ");
// 		ft_printf("%s\n", ex->tab[i]);
// 		i++;
// 	}
// 	return (0);
// }
// // https://pubs.opengroup.org/onlinepubs/
// // 000095399/basedefs/xbd_chap06.html#tagtcjh_3
// // https://stackoverflow.com/questions/2821043/
// // allowed-characters-in-linux-environment-variable-names
// static int	do_the_export(t_expand *ex, char **split_command)
// {
// 	int		i;
// 	int		pos;

// 	i = 0;
// 	// ft_printf("export: %s", split_command[1]);
// 	while (split_command[++i])
// 	{
// 		// ft_printf("split_command: %s\n", split_command[i]);
// 		if (mini_export_verif(split_command[i]) == 1)
// 		{
// 			pos = export_vintab(split_command[i], ex->tab);
// 			if (pos >= 0)
// 			{
// 				free(ex->tab[pos]);
// 				ex->tab[pos] = ft_strdup(split_command[i]);
// 			}
// 			else
// 				ex->tab = ft_extend_matrix(ex->tab, split_command[i]);
// 		}
// 		else if (mini_export_verif(split_command[i]) == 0)
// 			return (mini_export_error(split_command[i]));
// 	}
// 	return (0);
// }
// // FIX LES LEAKS

// int	mini_export(t_expand *ex, char **split_command)
// {
// 	int	return_value;

// 	return_value = 0;
// 	if (ft_matrixlen(split_command) == 1)
// 		return (export_no_arg(ex));
// 	else if (ft_matrixlen(split_command) > 1)
// 		return_value = do_the_export(ex, split_command);
// 	return (return_value);
// }
