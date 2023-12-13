/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:33:26 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/13 18:13:06 by ael-malt         ###   ########.fr       */
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
	ft_bzero(buf, BUFSIZ);
	if (getcwd(buf, BUFSIZ) == NULL)
	{
		if (find_env("PWD", env) == NULL)
			return (*procd = '.', procd);
		ft_strcat(buf, find_env("PWD", env)->value);
	}
	while (buf[i])
		i++;
	while (buf[i - 1] != '/')
		i--;
	ft_strcat(procd, &buf[i]);
	return (procd);
}

static char	*_prouser(char *prouser, t_env *env)
{
	ft_bzero(prouser, BUFSIZ);
	if (find_env("USER", env) == NULL)
		ft_strcat(prouser, "guest");
	else
		ft_strcat(prouser, find_env("USER", env)->value);
	return (prouser);
}

char	*cr_prompt(t_cleanup *cl, t_env *sh_env)
{
	char		procd[BUFSIZ];
	char		prouser[BUFSIZ];
	char		*prompt;

	_procd(procd, sh_env);
	_prouser(prouser, sh_env);
	prompt = ft_calloc((ft_strlen(prouser) + ft_strlen(procd) + \
	(((ft_strlen(BLUE) + ft_strlen(RESET))) * 4)) + 9, sizeof(char));
	if (prompt == NULL)
		return (err_msg("crt_prompt malloc fail"), cl->prompt = NULL, NULL);
	cat_colour(prompt, prouser, GREEN);
	cat_colour(prompt, "@Mini", RED);
	cat_colour(prompt, ":", WHITE);
	cat_colour(prompt, procd, BLUE);
	prompt[ft_strlen(prompt)] = '$';
	prompt[ft_strlen(prompt)] = ' ';
	cl->prompt = prompt;
	return (prompt);
}
