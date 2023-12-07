/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_A.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/06 16:08:53 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
	
char	*print_type(int type)
{
	char	*types[14];
	int		num[14];
	int		i;

	i = -1;
	if (type != 0 && !(type % 11))
		return ((char *[7]){"ECHO", "CD", "PWD", "EXPORT", "UNSET", "ENV"\
		, "EXIT"}[(type / 10) - 2]);
	while (++i < 15)
	{
		types[i] = (char *[15]){"WORD", "SEPR", "HERD", "EXST", "APRD", \
		"SQUO", "ARGT", "OPER", "REDL", "VARE", "DQUO", "BUIT", "REDR", \
		"COMD", "PIPE"}[i];
		num[i] = (int [15]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, \
		14}[i];
	}
	i = 0;
	while (type != num[i])
		i++;
	return (types[i]);
}

void	print_tree(t_astn *node)
{
	int	i;

	i = 0;
	if (node->left != NULL)
		print_tree(node->left);
	if (node->right != NULL)
		print_tree(node->right);
	if (node->type != COMD)
		printf ("______\nnode %s %p\nleft %p\nright %p\ntoken %p\nparent %p\n"\
		, print_type(node->type), node, node->left, node->right, \
		node->token, node->parent);
	else
	{
		printf ("______\nnode %s %p\nleft %p\nright %p\ntoken %p\nparent %p\n"\
		, print_type(node->type), node, node->left, node->right, node->token, \
		node->parent);
		while (node->token[i] != NULL)
		{
			printf("%s %li %s\n", node->token[i]->content, node->token[i]->len \
			, print_type(node->token[i]->type));
			i++;
		}
	}
}

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

void	print_sh_env(t_env *sh_env)
{
	FILE	*_file;
	t_env	*tmp;

	tmp = sh_env;
	_file = fopen("sh_env_file", "w+");
	fprintf(_file, "%s=%s\n", sh_env->name, sh_env->value);
	sh_env = sh_env->next;
	while (sh_env != tmp)
	{
		fprintf(_file, "%s=%s\n", sh_env->name, sh_env->value);
		sh_env = sh_env->next;
	}
	fclose(_file);
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
