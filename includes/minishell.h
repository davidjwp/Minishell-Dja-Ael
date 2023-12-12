/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:44:55 by rmohamma          #+#    #+#             */
/*   Updated: 2023/12/12 16:39:50 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "SH_structs.h"
# include "headers.h"
# include "../libft/includes/libft.h"

//MAIN+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//minishell.c
void		clean_up(t_cleanup *cl, int flag);
bool		sh_init(t_env *sh_env, t_cleanup *cl);
int			shell_loop(t_astn *tree, t_env *sh_env, t_cleanup *cl);

//prompt.c
char		*cr_prompt(t_cleanup *cl, t_env *sh_env);

//LEXER++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//create_ast
int			nbr_token(const char *input, size_t l_ind, int tokcnt);
t_token		*get_token(const char *input, size_t *l_ind, t_token *tok, int *e);
t_astn		*ast_cmd(const char *input, size_t *g_ind, t_cms c, int *err);
bool		ast_pipe(const char *in, size_t *g_ind, t_astn *pipe, t_astn *p);
t_astn		*create_ast(const char *input, size_t *i, int *error, t_astn *p);

//lexerutils_A
int			type(const char *s, size_t i);
bool		_pipe(const char *input);
bool		cmp(const char *content, const char *input);
bool		check_spec(const char *input, size_t *i);
bool		check_quote(const char *input, size_t *i);

//lexerutils_B
int			built_in(const char *input);
int			get_token_type(char	*token);
bool		it_token(const char *input, size_t *i);
char		*get_content(const char *input, size_t *ind, t_token *tok, int *e);
void		free_tok(t_token **tokens, int last);

//lexerutils_C
void		free_cmd_node(t_astn *cmd, bool cmdbool);
int			cut_len(const char *input, int flag);
int			init_node(t_astn *node, int nbr, t_astn *p, int *error);
const char	*cut_r(const char *input, int flag);
const char	*cut_l(const char *input, int flag);

//lexerutils_D
int			get_node_type(const char *input, size_t *g_ind);
void		free_tree(t_astn *node);
void		free_node(t_astn *red);
bool		it_sep(const char *input, size_t *i);

//utils
void		free_split(char **split);
char		**ft_split(const char *s, char c);

//PARSER+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//parser.c
bool		parser_rules(t_astn *node, int *error, t_cleanup *cl);
char		*expand_exst(int status, int *len);
t_astn		*parser(const char *input, t_cleanup *cl);

//parser_A.c
bool		pipe_rules(t_astn *node, int *error, t_cleanup *cl);
bool		redl_rules(t_token *tok, int *error, t_cleanup *cl);
bool		redr_rules(t_token *tok, int *error, t_cleanup *cl);
bool		comd_rules(t_token **tok, int *err, t_cleanup *cl);

//parser_B.c
char		*rem_quotes(char *content, int *t, int *err);

//parser_C.c
int			gnl(char **line);
size_t		ft_strcat(char *dest, const char *src);

//expander.c
char		*expand(char *var, char *cont, t_env *env, t_exp ep);
int			exp_novar(const char *content, size_t *i);
int			exp_newlen(char *content, size_t len, t_env *var);
char		*expand_cont(char *content, int *err, t_cleanup *cl);
t_env		*exp_findenv(char *name, int *err, t_env *sh_env);

//msgs.c
void		syntax_error(int type, t_cleanup *cl);
void		not_found(char *cmd, int *status);
void		err_msg(char *msg);
void		no_such_file(const char *file, t_cleanup *cl);
void		is_a_dir(char *dir, t_cleanup *cl);
void		perm_denied(char *file, t_cleanup *cl);

//EXEC+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//exe.c
int			exec_comd(t_astn *tree, t_env *sh_env, t_cleanup *cl);
int			sh_red(t_token **tok, int pos, t_cleanup *cl);
int			sh_pipe(t_astn *tree, t_env *sh_env, t_cleanup *cl);
int			execute(t_astn *tree, t_env *sh_env, t_cleanup *cl);

//exe_utils_A
char		*cr_pathname(const char *cmd, t_env *sh_env, int *status, int i);
char		**cr_envp(t_env *sh_env);
char		**cr_args(t_token **tokens, char *pathname);
char		*envcat(const char *name, const char *value);
int			rem_tokens(t_astn *node, int pos);

//exe_utils_B
int			sh_envlen(t_env *sh_env);
void		close_pipe(int *pipe);
void		close_fds(t_fds *fds);
void		wait_pipe(t_pipe p);
void		free_env(t_env *env);

//exe_utils_C
char		*path_cmd(const char *cmd);
bool		red_herd(t_token **tok);
void		get_pos(t_token **tokens, int *pos);
void		free_tokens(t_astn *node, int pos);

//heredoc.c
t_token		*get_herd(t_token **tokens, int *pos);
int			here_doc(char *delimiter, int out, int *err, t_cleanup *cl);
int			exe_herd(t_astn *node, int pos, t_cleanup *cl);
bool		cmp_del(char *del, char *new);
char		*str_realloc(char *ptr, int nmember, int size);

//fds.c
int			fd_red(void *type, int redpipe);
void		res_fd(int fd, int res, t_cleanup *cl);
void		rem_fd(t_fds *fd_lst, int fd);
int			add_fd(t_fds *fd_lst, int fd);
t_fds		*init_fds(void);


//UTILS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//utils_A.c
char		*print_type(int type);
void		print_tree(t_astn *node);
void		print_sh_env(t_env *sh_env);
char		*strccat(const char *str1, char c, const char *str2);

//utils_B.c
void		input_enter(void);
int			get_fd(int stdio, t_fds *fds);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);

//utils_C.c
int			gnl(char **line);

t_env		*cr_empty_env(void);
t_env		*cr_env(char **env);
t_env		*env_node(char *env);
t_astn		*parser(const char *input, t_cleanup *cl);
t_astn		*ast_cmd(const char *input, size_t *index, t_cms c, int *error);
t_env		*find_env(char *name, t_env *sh_env);

void		free_env(t_env *env);
void		printenvp(char **envp);

//signals
void		ctrl_c(int sig);
void		signals(void);

//-------------------------------BUILTINS------------------------------//

void		child_builtin(t_astn *tree, t_cleanup *cl, int type);
void		builtin(t_astn *tree, t_cleanup *cl, int type);
int			is_builtin(t_astn *tree);

		//--------------------BUILTINS_ERRORS.C---------------------//
int	mini_cd_error_1(int err_type, char *param, int err);
int		mini_export_error(char *arg);
void	mini_cd_exec(char *join_cd, int *exit_status);

		//-----------------------CD_UTIL.C--------------------------//
t_token	**malloc_token(void);
void	free_token(t_token **token);
t_env	*srch_env(t_env *env, char *str);

			//--------------------------CD.C----------------------------//
int			mini_cd(t_cleanup *cl, t_token **token);

			//-------------------------ECHO.C---------------------------//
int			mini_echo(t_astn *tree);

		//--------------------------ENV.C---------------------------//
void	insert_new_env_entry(t_cleanup *cl, char *content, t_env *tmp_env);
int		get_token_len(t_token **token);
int		get_env_len(t_env *env);
int		mini_env(t_env	*env);

			//-------------------------EXIT.C--------------------------//
int			mini_exit(t_cleanup *cl, t_token **token);

		//------------------------EXPORT.C--------------------------//
int		mini_export_error(char *cmd);
int		mini_export(t_cleanup *cl, t_token **token);

			//--------------------------PWD.C---------------------------//
int			mini_pwd(void);

			//-------------------------UNSET.C--------------------------//
int			unset_vintab(char *av, char **tab);
int			mini_unset(t_cleanup *cl, t_token **token);
char		**new_tab(t_cleanup *cl, int index);

#endif
