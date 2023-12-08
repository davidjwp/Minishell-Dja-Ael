/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:33:26 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/08 18:31:45 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static void	cat_colour(char *dest, char *src, char *col)
{
	ft_strcat(dest, col);
	ft_strcat(dest, src);
	ft_strcat(dest, RESET);
}

//. or getcwd() or $PWD
static char	*_procd(char *procd, t_env *env)
{
	char	buf[BUFSIZ];
	int		i;

	i = 0;
	ft_bzero(procd, BUFSIZ);
	if (getcwd(buf, BUFSIZ) == NULL && find_env("PWD", env) == NULL)
		return (*procd = '.', procd);
	else if (getcwd(buf, BUFSIZ) == NULL)
	{
		ft_bzero(buf, BUFSIZ);
		ft_strcat(buf, find_env("PWD", env)->value);
	}
	while (buf[i])
		i++;
	while (buf[i] != '/')
		i--;
	ft_strcat(procd, &buf[i]);
	return (procd);
}

char	*cr_prompt(t_cleanup *cl, t_env *sh_env)
{
	char		procd[BUFSIZ];
	char		*prompt;

	_procd(procd, sh_env);
	prompt = ft_calloc((ft_strlen(find_env("USER",sh_env)->value) + \
	ft_strlen(procd) + ((ft_strlen(BLUE) + ft_strlen(RESET)) * 3)) + 4, \
	sizeof(char));
	if (prompt == NULL)
		return (err_msg("crt_prompt malloc fail"), cl->prompt = NULL, NULL);
	cat_colour(prompt, find_env("USER", sh_env)->value, GREEN);
	cat_colour(prompt, ":~", WHITE);
	cat_colour(prompt, procd, BLUE);
	prompt[ft_strlen(prompt)] = ' ';
	cl->prompt = prompt;
	return (prompt);
}
