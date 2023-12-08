/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:39:25 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 20:25:29 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mini_pwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf)
	{
		printf("%s\n", buf);
		free(buf);
	}
	else
		ft_putendl_fd("chdir: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory", 2);

	return (0);
}
