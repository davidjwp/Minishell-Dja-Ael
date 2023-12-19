/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:28:31 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/18 16:22:08 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_cmp_token_to_env(t_env *env, char *content)
{
	int	pos;

	pos = ft_strchr_i(content, '=');
	if (pos == -1)
		return (0);
	if (!ft_strncmp(env->name, content, pos))
	{
		free(env->value);
		if (content[pos + 1])
			env->value = ft_strdup(&content[pos + 1]);
		env->cl[1] = env->value;
		return (1);
	}
	return (0);
}

int	mini_export_verif(char *str)
{
	int	i;

	i = 1;
	if (!(str[0] == '_' || ft_isalpha(str[0])))
		return (0);
	while (str && str[i] && str[i] != '=')
	{
		if (!(str[i] == '_' || ft_isalnum(str[i])))
			return (0);
		i++;
	}
	if (str[i] != '=')
		return (2);
	return (1);
}

// // https://pubs.opengroup.org/onlinepubs/
// // 000095399/basedefs/xbd_chap06.html#tagtcjh_3
// // https://stackoverflow.com/questions/2821043/
// // allowed-characters-in-linux-environment-variable-names

static int	do_the_export(t_cleanup *cl, t_token **token, int i)
{
	t_env	*first_env;

	first_env = cl->env;
	while (token && token[i] && token[i]->content)
	{
		if (mini_export_verif(token[i]->content) == 1)
		{
			cl->env = first_env;
			while (cl->env)
			{
				if (export_cmp_token_to_env(cl->env, token[i]->content))
					break ;
				if (cl->env->next == first_env && \
					insert_new_env_entry(cl, token[i]->content, first_env))
					break ;
				cl->env = cl->env->next;
			}
			empty_env_export(cl, token, i);
		}
		else if (mini_export_verif(token[i]->content) == 0)
			return (mini_export_error(token[i]->content));
		i++;
	}
	return (0);
}

static int	export_no_arg(t_env *env)
{
	int	len;

	if (!env)
		return (0);
	len = get_env_len(env) + 1;
	while (len--)
	{
		printf("export %s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}

int	mini_export(t_cleanup *cl, t_token **token)
{
	int	i;
	int	return_value;

	i = 1;
	return_value = 0;
	if (get_token_len(token) == 1)
		return (export_no_arg(cl->env));
	else if (get_token_len(token) > 1)
		return_value = do_the_export(cl, token, i);
	return (return_value);
}
