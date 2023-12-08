#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../includes/minishell.h"

#define DFLT_PROMPT "$> "
#define GREEN "\033[1m\033[32m"
#define BLUE "\033[1m\033[34m"
#define RESET "\033[0m"

/*
	THIS IS FOR CREATING A BASH ACCURATE PROMPT, IT IS NOT FINISHED
	MISSING THE ADDED COLOURS AND I"M NOT SURE ABOUT THE
	CURRENT WORKING DIRECTORY
*/
void	err_msg(char *msg)
{
	write(2, "minishell: ", 12);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	ptr_size;

	ptr_size = (int)(nmemb * size);
	if (size != 0 && nmemb != (size_t)ptr_size / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	while (ptr_size--)
		ptr[ptr_size] = 0;
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		i++;
	}
	return (i);
}

size_t	ft_strcat(char *dest, const char *src)
{
	unsigned int	index;
	size_t			d_len;

	index = 0;
	if (!*src)
		return (0);
	d_len = ft_strlen(dest);
	while (src[index])
	{
		dest[d_len + index] = src[index];
		index++;
	}
	dest[d_len + index] = 0;
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && s2[i] && s1[i] == s2[i])
			i++;
		return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	}
	return (0);
}

t_env	*find_env(char *name, t_env *sh_env)
{
	t_env	*tmp;

	tmp = sh_env;
	while (ft_strcmp(name, tmp->name))
	{
		tmp = tmp->next;
		if (tmp == NULL)
			break ;
	}
	return (tmp);
}

void	free_env(t_env *env)
{
	t_env	*tmp;
	t_env	*f;

	tmp = env;
	env = env->next;
	while (env != tmp)
	{
		f = env;
		env = env->next;
		free(f->name);
		free(f->value);
		free(f->cl);
		free(f);
	}
	free(env->name);
	free(env->value);
	free(env->cl);
	free(env);
}

void	putnsplit(char *split, char *env, int n)
{
	int	i;

	i = 0;
	while (env[i] && i < n)
	{
		split[i] = env[i];
		i++;
	}
}

char	**split_env(char *env)
{
	char	**split;
	int		len;

	len = 0;
	split = malloc(sizeof(char *) * 3);
	while (env[len] && env[len] != '=')
		len++;
	split[0] = ft_calloc((len + 1), sizeof(char));
	putnsplit(split[0], env, len);
	split[1] = ft_calloc(ft_strlen(&env[len + 1]) + 1, sizeof(char));
	putnsplit(split[1], &env[len + 1], ft_strlen(&env[len + 1]));
	split[2] = NULL;
	return (split);
}

//free_split might free name and value
t_env	*env_node(char *env)
{
	t_env	*node;
	char	**split;

	split = split_env(env);
	if (split == NULL)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (free_split(split), NULL);
	node->name = split[0];
	node->value = split[1];
	node->cl = split;
	node->next = NULL;
	return (node);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split[i]);
	free(split);
}

t_env	*cr_env(char **env)
{
	t_env	*sh_env;
	t_env	*tmp;
	int		i;

	if (!*env)
		return (0);
	i = 0;
	sh_env = env_node(env[i]);
	if (sh_env == NULL)
		return (NULL);
	tmp = sh_env;
	while (env[++i] != NULL)
	{
		sh_env->next = env_node(env[i]);
		if (sh_env->next == NULL)
			return (sh_env->next = tmp, free_env(sh_env), NULL);
		sh_env = sh_env->next;
	}
	sh_env->next = tmp;
	sh_env = sh_env->next;
	return (sh_env);
}




//this is the function

//USER@NAME:~cwd this is the way the prompt would be structured 
char	*crt_prompt(t_cleanup *cl)
{
	char		*prompt;

	if (cl->env == NULL)
		return ("~> ");
	prompt = ft_calloc(ft_strlen(find_env("USER",cl->env)->value) + \
	ft_strlen(getcwd(NULL, 0)) + 4, sizeof(char));
	if (prompt == NULL)
		return (err_msg("crt_prompt malloc fail"), NULL);
	ft_strcat(prompt, find_env("USER", cl->env)->value);
	ft_strcat(prompt, ":~");
	ft_strcat(prompt, getcwd(NULL, 0));
	prompt[ft_strlen(prompt)] = ' ';
	return (prompt);
}

int	main(int argc, char **argv, char **env)
{
	t_cleanup	*cl;
	char		*prompt;

	cl = malloc(sizeof(t_cleanup));
	if (cl == NULL)
		return (err_msg("cl malloc fail"), 0);
	cl->env = cr_env(env);
	prompt = crt_prompt(cl);
	if (prompt == NULL)
		return (0);
	return (printf("%s\n", prompt), 0);
}