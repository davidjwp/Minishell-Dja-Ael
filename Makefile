CC				= gcc

NAME			= minishell

INCLUDE			=   includes/minishell.h 

CFLAGS			= -g3 -Wall -Wextra -Werror -no-pie

LIB				= libft/libft.a

LINKER			= -L/usr/include -lreadline 

SRCS			= srcs/main/minishell.c \
			srcs/prompt/prompt_edited.c \
			srcs/signals/ctrl_signal.c \
			srcs/lexer/create_ast.c \
			srcs/lexer/lexerutils_A.c \
			srcs/lexer/lexerutils_B.c \
			srcs/lexer/lexerutils_C.c \
			srcs/lexer/lexerutils_D.c \
			srcs/lexer/lexerutils_E.c \
			srcs/lexer/utils.c \
			srcs/executor/exe.c \
			srcs/executor/exeutils_A.c \
			srcs/executor/exeutils_B.c \
			srcs/executor/exeutils_C.c \
			srcs/executor/fds.c \
			srcs/executor/heredoc.c \
			srcs/utils/cr_env.c \
			srcs/parser/expander.c \
			srcs/parser/msgs.c \
			srcs/parser/parser_A.c \
			srcs/parser/parser_B.c \
			srcs/parser/parser_C.c \
			srcs/parser/parser.c \
			srcs/utils/utils_A.c \
			srcs/utils/utils_B.c \
			srcs/builtins/builtins_errors.c \
			srcs/builtins/builtins.c \
			srcs/builtins/mini_cd.c \
			srcs/builtins/mini_echo.c \
			srcs/builtins/mini_env.c \
			srcs/builtins/mini_exit.c \
			srcs/builtins/mini_export.c \
			srcs/builtins/mini_pwd.c \
			srcs/builtins/mini_unset.c \

OBJS_DIR		= objs/
OBJS			= $(SRCS:srcs/%.c=$(OBJS_DIR)%.o)

all:$(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LINKER) $(LIB) -o $(NAME)

$(OBJS_DIR)%.o: srcs/%.c
	@mkdir -p $(@D)
	@$(CC) -c $(CFLAGS) $< -o $@

$(LIB):
	@make -s -C libft/

clean:
	@rm -f $(OBJS)
	@make clean -C libft/
	
fclean: clean
	@rm -f $(NAME)
	@make -s fclean -C libft/ 

re: fclean all

.PHONY: fclean clean all
