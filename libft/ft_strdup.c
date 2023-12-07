/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidjwp <davidjwp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:55:00 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/03 22:24:08 by davidjwp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicate;
	int		index;

	index = 0;
	duplicate = malloc(ft_strlen((char *)s) + 1);
	if (!duplicate)
		return (0);
	while (s[index])
	{
		duplicate[index] = s[index];
		index++;
	}
	duplicate[index] = '\0';
	return (duplicate);
}