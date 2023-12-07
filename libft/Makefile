# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 19:45:57 by yuboktae          #+#    #+#              #
#    Updated: 2023/12/04 13:19:40 by djacobs          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRC		=		ft_isalpha.c \
	  			ft_isdigit.c \
	  			ft_isalnum.c \
	  			ft_isprint.c \
	  			ft_strlen.c \
	  			ft_memset.c \
	  			ft_bzero.c \
	  			ft_memcpy.c \
	  			ft_memmove.c \
				ft_strcpy.c \
	  			ft_toupper.c \
	  			ft_tolower.c \
				ft_strcmp.c \
				ft_strstr.c	\
	  			ft_strncmp.c \
	  			ft_memcmp.c \
	  			ft_strnstr.c \
	  			ft_strtrim.c \
	  			ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_strchr.c \
				ft_strjoin.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_putchar_fd.c \
				ft_substr.c \
				ft_itoa.c \

SRC_BONUS	=	ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \


OBJ		=	${SRC:%.c=%.o}

OBJ_BONUS	=	${SRC_BONUS:%.c=%.o}

HEADER		=	libft.h

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -g3

all:	$(NAME)

%.o: %.c $(HEADER)
		@$(CC) -c $(CFLAGS) -o $@ $<
		
		
$(NAME): $(OBJ) $(OBJ_BONUS)
		@ar rc $(NAME) $^
#		@echo  "$(GREEN)Libft: Mandatory created!$(DEFAULT)"
clean:
	@rm -f $(OBJ) $(OBJ_BONUS)
#	@echo  "$(YELLOW)Libft: object files deleted!$(DEFAULT)"
	
fclean:	clean
	@rm -f $(NAME)
#	@echo  "$(RED)Libft: all deleted!$(DEFAULT)"
	
re:	fclean all

.PHONY: all clean fclean re

#COLORS
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
DEFAULT	= \033[0m
