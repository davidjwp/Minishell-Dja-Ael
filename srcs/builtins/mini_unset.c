/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:54:21 by lazanett          #+#    #+#             */
/*   Updated: 2023/12/09 14:07:59 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*get_prev_env(t_env *env)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (env->next != tmp_env)
		env = env->next;
	return(env);
}
static int	unset_cmp_token_to_env(t_env *env, char *content)
{
	t_env	*prev_env;
	int	i;

	i = 0;
	prev_env = get_prev_env(env);
	if (!ft_strcmp(env->name, content))
	{
		// printf("ici\n");
		// free(env->name);
		// free(env->value);
		while (env->cl && env->cl[i])
			free(env->cl[i++]);
		free(env->cl);
		prev_env->next = env->next;
		free(env);
		return (1);
	}
	return (0);
}

int	mini_unset(t_cleanup *cl, t_token **token)
{
	t_env	*first_env;
	int		i;

	first_env = cl->env;
	i = 1;
	if (get_token_len(token) > 1)
	{
		while (token && token[i] && token[i]->content)
		{
			cl->env = first_env;
			while (cl->env)
			{
				if (unset_cmp_token_to_env(cl->env, token[i]->content))
					break ;
				else if (cl->env->next == first_env)
					break ;
				cl->env = cl->env->next;
			}
			
			// j = unset_vintab(token[i]->content, cl->env);
			// if (j != -1)
				// ft_matrix_replace_in(&ex->tab, NULL, j);
				i++;
		}
	}
	return (0);
}

int	unset_vintab(char *av, char **tab)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(av);
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], av, len) && (tab[i][ft_strlen(av)] == '='))
			return (i);
		i++;
	}
	return (-1);
}


// int	mini_unset(t_expand *ex, char **split_command)
// {
// 	int	i;
// 	int	len;
// 	int	j;

// 	i = 1;
// 	if (!split_command)
// 		return (0);
// 	while (split_command[i])
// 	{
// 		j = 0;
// 		len = ft_strlen(split_command[i]);
// 		if (len == 0)
// 			return (0);
// 		j = unset_vintab(split_command[i], ex->tab);
// 		if (j >= 0)
// 		{
// 			ex->tab = new_tab(ex, j);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// char	**new_tab(t_expand *ex, int index)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	ex->new_tab = malloc(sizeof (char *) * (ft_matrixlen(ex->tab) + 1));
// 	if (!ex->new_tab)
// 		return (0);
// 	while (ex->new_tab[i])
// 	{
// 		ex->new_tab[i] = NULL;
// 		i++;
// 	}
// 	i = 0;
// 	while (ex->tab[i])
// 	{
// 		if (!(i == index))
// 			ex->new_tab[j++] = ft_strdup(ex->tab[i]);
// 		i++;
// 	}
// 	ft_free_matrix(&ex->tab);
// 	return (ex->new_tab);
// }
