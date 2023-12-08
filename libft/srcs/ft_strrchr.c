/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:35:21 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:44:00 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s) + 1;
	while (i--)
		if (*(s + i) == (char)c)
			return ((char *)s + i);
	return (NULL);
}

// int main()
// {
// 	char s[50] = "GeeksForGeeks is for programming geeks.";
// 	char c = 'i';
// 	char *ptr;
// 	char *ptr1;

// 	printf("Before    strrchr(): %s\n", s);
// 	printf("Before ft_strrchr(): %s\n\n", s);

// 	ptr = strrchr(s, c);
// 	ptr1 = ft_strrchr(s, c);

// 	printf("After    strrchr():  %s\n", ptr);
// 	printf("After ft_strrchr():  %s\n", ptr1);

// 	return 0;
// }
