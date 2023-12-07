/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_edited.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 10:25:43 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/07 13:31:57 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//static char	*session_part(t_env *sh_env);
//static char	*rest_part(t_env *sh_env, char *session);
//static char	*final_prompt(char *joined);
//static char	*ft_tilde_prompt(char *joined2, char *pointer, char *home);

//char	*ft_prompt(t_env *sh_env)
//{
//	char	*prompt;
//	char	*session;
//	char	*joined;

//	session = session_part(sh_env);
//	joined = rest_part(sh_env, session);
//	prompt = final_prompt(joined);
//	free(session);
//	free(joined);
//	return (prompt);
//}

//static char	*session_part(t_env *sh_env)
//{
//	int		i;
//	char	*session;
//	char	*tmp;
//	char	*point;
//	char	*session2;
//	char	*session3;

//	i = 0;
//	session = find_env_value("SESSION_MANAGER", sh_env);
//	session = ft_strchr(session, '/');
//	tmp = ++session;
//	point = ft_strchr(tmp, '.');
//	while (tmp <= point)
//	{
//		i++;
//		tmp++;
//	}
//	session2 = ft_substr(session, 0, i - 1);
//	session3 = ft_strjoin("@", session2);
//	free(session2);
//	return (session3);
//}

//static char	*rest_part(t_env *sh_env, char *session)
//{
//	char	*user;
//	char	*joined;
//	char	*home;
//	char	*pointer;
//	char	*joined1;
//	char	*joined2;
//	int		k;

//	k = 0;
//	user = find_env_value("USER", sh_env);
//	joined1 = ft_strjoin(user, session);
//	joined2 = ft_strjoin(joined1, ":");
//	home = find_env_value("HOME", sh_env);
//	pointer = find_env_value("PWD", sh_env);
//	if (!pointer)
//	{
//		pointer = getcwd(NULL, 0);
//		k = 1;
//	}
//	if (home && *home && ft_strcmp(pointer, home) >= 0)
//		joined = ft_tilde_prompt(joined2, pointer, home);
//	else
//		joined = ft_strjoin(joined2, pointer);
//	if (k)
//		free(pointer);
//	free(joined1);
//	free(joined2);
//	return (joined);
//}

//static char	*final_prompt(char *joined)
//{
//	int		len2;
//	int		i;
//	char	*prompt;

//	i = 0;
//	len2 = ft_strlen(joined);
//	prompt = (char *)malloc(sizeof(char) * (len2 + 2));
//	if (!prompt)
//	{
//		printf("Alloc failure\n");
//		return (NULL);
//	}
//	while (joined && *joined)
//	{
//		prompt[i] = *joined;
//		i++;
//		joined++;
//	}
//	prompt[i++] = '$';
//	prompt[i] = '\0';
//	return (prompt);
//}

//static char	*ft_tilde_prompt(char *joined2, char *pointer, char *home)
//{
//	int		len;
//	char	*joined3;
//	char	*joined;

//	joined3 = ft_strjoin(joined2, "~");
//	len = ft_strlen(home);
//	pointer = pointer + len;
//	joined = ft_strjoin(joined3, pointer);
//	free(joined3);
//	return (joined);
//}
