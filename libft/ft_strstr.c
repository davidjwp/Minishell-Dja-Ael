/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:14:17 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/28 19:18:19 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
//#include <stdio.h>

static int	to_find_len(char *to_find)
{
	int	index;
	int	len;

	len = 0;
	index = 0;
	while (to_find[index])
	{
		len++;
		index++;
	}
	return (len);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	find_index;
	int	src_index;
	int	find_len;

	find_index = 0;
	src_index = 0;
	find_len = to_find_len(to_find);
	if (find_len == 0)
		return (str);
	while (str[src_index] && to_find[find_index])
	{
		if (str[src_index] == to_find[find_index])
				find_index++;
		else
			find_index = 0;
		if (find_index == find_len)
			return (&str[src_index - (find_index - 1)]);
		src_index++;
	}
	return NULL;
}
/* int main(void)
{
	char *str = "/mnt/nfs/homes/rmohamma/Downloads/28nov_unsetPWD/1";
	char *str2 = "/mnt/nfs/homes/rmohamma/.local/share/Trash/files/1.8";
	printf("%s \n", ft_strstr(str, str2));
	return 0;
} */
