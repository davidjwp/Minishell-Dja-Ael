/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SH_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:12:56 by djacobs           #+#    #+#             */
/*   Updated: 2023/12/07 18:36:37 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_STRUCTS_H
# define SH_STRUCTS_H

# include <stdlib.h>

# define PROMPT	"Minishell $> "
# define ABS_PATHS "/usr/bin:/usr/sbin:/bin:/sbin"

//FLAGS
# define C_PIPE 0
# define C_RED 1

# define G_ERROR 0
# define IT_SEP 0
# define IT_TOK	1

# define BLUE_COLOR "\033[1;36m"
# define RESET_BLUE_COLOR "\033[0m"
# define PURPLE_COLOR "\x1b[35m"
# define RESET_PURPLE_COLOR "\x1b[0m"

extern volatile int	g_signal;

enum e_builtin{
	ECHO = 22,
	CD = 33,
	PWD = 44,
	EXPORT = 55,
	UNSET = 66,
	ENV = 77,
	EXIT = 88
};

/*
	token types:
	word 0
	separator 1
	heredoc 2
	exit status 3
	append redirection 4
	quotes 5
	argument 6
	operator 7
	redirection left 8
	variable 9
	pipeline 10
	builtin 11
	redirection right 12
	command 13
	do not touch this, it's built like this on purpose
*/

enum e_type{
	WORD,
	SEPR,
	HERD,
	EXST,
	APRD,
	SQUO,
	ARGT,
	OPER,
	REDL,
	VARE,
	DQUO,
	BUIT,
	REDR,
	COMD,
	PIPE,
};

enum	e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 4,
	DUPERR = 5,
	FORKERR = 6,
	PIPERR = 7,
	PIPENDERR = 8,
	MEM = 9,
	IS_DIR = 10,
	NOT_DIR = 11,
	OPERROR = 12,
	NOTCMD = 13,
	NONAME = 14,
	SYNTAX = 15,
	NOQUOTE = 16
};

enum e_clflags{
	CL_FDS = 1,
	CL_TRE = 2,
	CL_ENV = 4,
	CL_INP = 8,
	CL_HIS = 16,
	CL_CL = 32,
	CL_ALL = 63,
};

enum e_ResFDflags{
	RED_PIP = 1,
	RED_RED = 2,
};

enum e_stdIO{
	STDI,
	STDO,
};

//this structure is used in the expand_cont function to save on arguments
typedef struct ExpandInternalStruct{
	size_t	i;
	size_t	y;
	size_t	pos;
	int		*err;
}	t_exp;

typedef struct s_token{
	int		type;
	size_t	len;
	char	*content;
}	t_token;

typedef struct AbstractSyntaxTreeNode{
	t_token							**token;
	int								type;
	struct AbstractSyntaxTreeNode	*parent;
	struct AbstractSyntaxTreeNode	*left;
	struct AbstractSyntaxTreeNode	*right;
}	t_astn;

typedef struct ShellEnvNode{
	char				*name;
	char				*value;
	char				**cl;
	struct ShellEnvNode	*next;
}	t_env;

typedef struct PipeStruct{
	pid_t	r_pid;
	pid_t	l_pid;
	int		pipe[2];
}	t_pipe;

typedef struct RedirectionStruct{
	int	in;
	int	out;
}	t_red;

typedef struct FileDescriptors{
	int						std;
	int						fd;
	struct FileDescriptors	*next;
}	t_fds;


typedef struct Cmd_Struct_Nodes{
	t_astn	*parent;
	t_astn	*node;
}				t_cms;

typedef struct ExecuteArgumentStruct{
	char	*_path;
	char	**_envp;
	char	**argv;
}	t_exe;

typedef struct CleanUp{
	t_fds	*fds;
	t_env	*env;
	t_astn	*tree;
	char	*input;
	int		status;
}	t_cleanup;

#endif
