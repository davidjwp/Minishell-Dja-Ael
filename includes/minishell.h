/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:44:55 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/07 15:38:16 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "SH_structs.h"
# include "headers.h"
# include "../libft/libft.h"

/*DAVID***********************************************************************/

//MAIN+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int			check_input(char *input);//allows me to cleanly exit
bool		sh_init(char *input, t_env *sh_env, t_cleanup *cl);
int			shell_loop(t_astn *tree, t_env *sh_env, t_cleanup *cl);
int			sh_pipe(t_astn *tree, t_env *sh_env, t_cleanup *cl);

//LEXER++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//create_ast
t_token		*get_token(const char *input, size_t *l_ind, t_token *tok, int *e);
t_astn		*ast_cmd(const char *input, size_t *g_ind, t_cms c, int *err);
bool		ast_pipe(const char *in, size_t *g_ind, t_astn *pipe, t_astn *p);
bool		ast_red(const char *in, size_t *g_ind, t_astn *red, t_astn *p);
t_astn		*create_ast(const char *input, size_t *i, int *error, t_astn *p);

//lexerutils_A
int			type(const char *s, size_t i);
bool		_pipe(const char *input);
bool		_red(const char *input);
bool		cmp(const char *content, const char *input);
bool		check_spec(const char *input, size_t *i);

//lexerutils_B
bool		check_quote(const char *input, size_t *i);
int			built_in(const char *input);
int			get_token_type(char	*token);
bool		it_token(const char *input, size_t *i);
char		*get_content(const char *input, size_t *ind, t_token *tok, int *e);

//lexerutils_C
int			nbr_token(const char *input, size_t l_ind, int tokcnt);
void		free_tok(t_token **tokens, int last);
void		free_cmd_node(t_astn *cmd, bool cmdbool);
int			cut_len(const char *input, int flag);

//lexerutils_D
int			init_node(t_astn *node, int nbr, t_astn *p, int *error);
const char	*cut_r(const char *input, int flag);
const char	*cut_l(const char *input, int flag);
int			get_node_type(const char *input, size_t *g_ind);
void		free_tree(t_astn *node);

//lexerutils_E
bool		it_sep(const char *input, size_t *i);
void		free_node(t_astn *red);

//utils
char		**ft_split(const char *s, char c);
void		free_split(char **split);

//PARSER+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//parser.c
bool		parser_rules(t_astn *node, int *error, t_cleanup *cl);
char		*expand_exst(int status, int *len);
t_astn		*parser(const char *input, t_cleanup *cl);

//parser_A.c
bool		pipe_rules(t_astn *node, int *error, t_cleanup *cl);
bool		apr_rules(t_astn *node, int *error, t_cleanup *cl);
bool		redl_rules(t_astn *node, int *error, t_cleanup *cl);
bool		redr_rules(t_astn *node, int *error, t_cleanup *cl);
bool		comd_rules(t_token **tok, int *err, t_cleanup *cl);

//parser_B.c
char		*rem_quotes(char *content, int *err, int i, int y);

//parser_C.c
int			gnl(char **line);
int			rem_herd(t_astn *node, int pos);
size_t		ft_strcat(char *dest, const char *src);

//expander.c
char		*expand(char *var, char *cont, t_env *env, t_exp ep);
int			exp_novar(const char *content, size_t *i);
int			exp_newlen(char *content, size_t len, t_env *var);
char		*expand_cont(char *content, int *err, t_cleanup *cl);
t_env		*exp_findenv(char *name, int *err, t_env *sh_env);

//msgs.c
void		syntax_error(const char *str, t_cleanup *cl);
void		not_found(char *cmd, int *status);
void		err_msg(char *msg);
void		print_out(char *msg, t_cleanup *cl);


//EXEC+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//exe.c
int			open_file(t_astn *tree, t_red *_red, int flag);
int			sh_red(t_astn *tree, t_env *sh_env, t_cleanup *cl);
int			execute(t_astn *tree, t_env *sh_env, t_cleanup *cl);

//exe_utils_A
char		*cr_pathname(const char *cmd, t_env *sh_env, int *status, int i);
char		**cr_envp(t_env *sh_env);
char		**cr_args(t_token **tokens, char *pathname);
char		*envcat(const char *name, const char *value);
char		*strccat(const char *str1, char c, const char *str2);

//exe_utils_B
int			sh_envlen(t_env *sh_env);
void		close_pipe(int *pipe);
void		close_fds(t_fds *fds);
void		wait_pipe(t_pipe p);
void		free_env(t_env *env);

//exe_utils_C
//t_env		*find_env(const char *name, t_env *sh_env);
char		*path_cmd(const char *cmd);

//heredoc.c
t_token		*get_herd(t_token **tokens, int *pos);
int			here_doc(char *delimiter, int out, int *err, t_cleanup *cl);
int			exe_herd(t_astn *node, int pos, t_env *sh_env, t_cleanup *cl);


//fds.c
int			fd_redirection(void *type, int redpipe, t_cleanup *cl);
void		restore_fd(int fd, int res, t_cleanup *cl);
void		rem_fd(t_fds *fd_lst, int fd);
int			add_fd(t_fds *fd_lst, int fd);
t_fds		*init_fds(void);

//BUILTINS+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//MAIN+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//minishell.c
int			shell_loop(t_astn *tree, t_env *sh_env, t_cleanup *cl);
int			sh_envlen(t_env *sh_env);
void		clean_up(t_cleanup *cl, int flag);

//UTILS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//utils_A.c
char		*print_type(int type);
void		print_tree(t_astn *node);
void		print_sh_env(t_env *sh_env);

//utils_B.c
void		input_enter(void);
int			get_fd(int stdio, t_fds *fds);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);

//utils_C.c
int			gnl(char **line);

t_env		*cr_env(char **env);
t_astn		*parser(const char *input, t_cleanup *cl);
t_astn		*ast_cmd(const char *input, size_t *index, t_cms c, int *error);
t_env		*find_env(char *name, t_env *sh_env);

void		free_env(t_env *env);
void		printenvp(char **envp);


//MESSAGES+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//signals
void		ctrl_c(int sig);
void		signals(void);




#endif