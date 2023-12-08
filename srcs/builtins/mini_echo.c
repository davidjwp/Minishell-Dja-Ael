/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:40:59 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 20:52:13 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_echo(t_astn *tree, int i)
{
	while (tree->token && tree->token[i] && tree->token[i]->content)
	{
		ft_printf("%s", tree->token[i]->content);
		if (tree->token[i + 1] && tree->token[i + 1]->content)
			ft_printf(" ");
		i++;
	}
}

int	mini_echo(t_astn *tree)
{
	int	i;
	int	n;
	int	j;

	i = 1;
	n = 0;
	while (tree->token[i] && tree->token[i]->content && \
		!ft_strncmp(tree->token[i]->content, "-n", 2))
	{
		j = 1;
		while (tree->token[i] && tree->token[i]->content[j] == 'n')
			j++;
		if (tree->token[i] && tree->token[i]->content[j - 1]
			&& tree->token[i]->content[j] == '\0')
		{
			n = 1;
			i++;
		}
		else
			break ;
	}
	print_echo(tree, i);
	if (!n)
		ft_printf("\n");
	return (0);
}
