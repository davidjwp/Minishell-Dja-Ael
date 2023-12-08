/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:12:11 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:44:00 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (*(s + i) == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

// int	main()
// {
// 	char s[50] = "GeeksForGeeks is for programming geeks.";
// 	char c = 'i';
// 	char *ptr;
// 	char *ptr1;

// 	printf("Before    strchr(): %s\n", s);
// 	printf("Before ft_strchr(): %s\n\n", s);

// 	ptr = strchr(s, c);
// 	ptr1 = ft_strchr(s, c);

// 	printf("After    strchr():  %s\n", ptr);
// 	printf("After ft_strchr():  %s\n", ptr1);

// 	return 0;
// }
