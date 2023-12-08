/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:28:31 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/08 20:18:37 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_vintab(char *cmd, char **tab)
{
	int	i;
	int	pos;

	i = 0;
	pos = ft_strchr_i(cmd, '=');
	if (pos == -1)
		return (-1);
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], cmd, pos))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}
static void	insert_new_env_entry(t_cleanup *cl, char *content, t_env *tmp_env)
{
	t_env	*new_env_entry;

	new_env_entry = env_node(content);
	cl->env->next = new_env_entry;
	new_env_entry->next = tmp_env;
}
static int	cmp_token_to_env(t_env *env, char *content)
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

static int	mini_export_verif(char *str)
{
	int	i;
	int	equal_present;

	i = 1;
	if ((str[0] == '=' || ft_isdigit(str[0])) && !(str[i] == '_' || ft_isalpha(str[0])))
		return (0);
	equal_present = 0;
	while (str && str[i])
	{
		if (!(str[i] == '_' || ft_isalnum(str[i]) || str[i] == '='))
			return (0);
		if (str[i] == '=')
			equal_present = 1;
		i++;
	}
	if (!equal_present)
		return (2);
	return (1);
}

// // https://pubs.opengroup.org/onlinepubs/
// // 000095399/basedefs/xbd_chap06.html#tagtcjh_3
// // https://stackoverflow.com/questions/2821043/
// // allowed-characters-in-linux-environment-variable-names
static int	do_the_export(t_cleanup *cl, t_token **token)
{
	int		i;
	t_env	*tmp_env;

	tmp_env = cl->env;
	i = 1;
	while (token && token[i] && token[i]->content)
	{
		if (mini_export_verif(token[i]->content) == 1)
		{
			while (cl->env)
			{
				if (cmp_token_to_env(cl->env, token[i]->content))
					break ;
				if (cl->env->next == tmp_env)
				{
					insert_new_env_entry(cl, token[i]->content, tmp_env);
					break ;
				}
				cl->env = cl->env->next;
			}
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

	len = get_env_len(env);
	while (len--)
	{
		printf("export %s=%s\n",env->name,env->value);
		env = env->next;
	}
	return (0);
}

static int get_token_len(t_token **token)
{
	int i;

	i = 0;
	while (token[i] && token[i]->content)
		i++;
	return (i);
}

int	mini_export(t_cleanup *cl, t_token **token)
{
	int	return_value;

	return_value = 0;
	if (get_token_len(token) == 1)
		return (export_no_arg(cl->env));
	else if (get_token_len(token) > 1)
		return_value = do_the_export(cl, token);
	return (return_value);
}
