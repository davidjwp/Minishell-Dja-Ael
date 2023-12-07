/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:04:53 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:44:00 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	new_len;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	new_len = ft_strlen(&s[start]);
	if (new_len < len)
		len = new_len;
	sub_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub_str)
		return (0);
	ft_strlcpy(sub_str, &s[start], len + 1);
	return (sub_str);
}

// int main(void)
// {
// 	printf("%s\n", ft_substr("this is a test aaaaaa", 1919, 4));
// }
