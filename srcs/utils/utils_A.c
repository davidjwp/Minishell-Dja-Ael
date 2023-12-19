/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_A.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/14 19:12:47 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

//concatenates the str2 after str1 with c in the middle
char	*strccat(const char *str1, char c, const char *str2)
{
	char	*pathname;
	int		len;
	int		y;
	int		i;

	i = -1;
	y = -1;
	len = ft_strlen(str1) + ft_strlen(str2) + 1;
	pathname = malloc(sizeof(char) * (len + 1));
	if (pathname == NULL)
		return (err_msg("cat_str2s malloc fail"), NULL);
	pathname[len] = 0;
	while (str1[++i])
		pathname[i] = str1[i];
	pathname[i] = c;
	while (str2[++y] && ++i < len)
		pathname[i] = str2[y];
	return (pathname);
}

void	err_msg(char *msg)
{
	write (2, "minishell: ", 12);
	write (2, msg, ft_strlen(msg));
	write (2, "\n", 1);
}
