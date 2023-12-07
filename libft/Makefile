NAME		= libft.a

### SRCS

PATH_SRCS	= srcs/

LIBFT		= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
				ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c \
				ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c \
				ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
				ft_strrchr.c ft_tolower.c ft_toupper.c ft_itoa.c ft_putchar_fd.c \
				ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
				ft_striteri.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_substr.c \
				ft_strchr_i

LIBFT_BONUS	= ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
				ft_lstmap.c ft_lstiter.c ft_lstnew.c ft_lstlast.c ft_lstsize.c

PRINTF		= ft_printf.c ft_printf_utils.c ft_printf_utils_1.c

GNL			= get_next_line.c get_next_line_utils.c

GNL_BONUS	= get_next_line_bonus.c get_next_line_utils_bonus.c

SRCS += $(LIBFT) $(LIBFT_BONUS) $(PRINTF) $(GNL) $(GNL_BONUS)

vpath %.c $(PATH_SRCS)

### HEADER

INCLUDES	= -Iincludes/

HEADER		+= libft.h

vpath %.h $(PATH_HEADER)

### OBJS

PATH_OBJS	= objs/
OBJS		= $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))

### COMPILATION

CC			= clang
RM			= rm -f
CFLAGS		= -Wall -Werror -Wextra -I.

AR = ar rcs

all: 		$(NAME)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)

$(OBJS):	$(PATH_OBJS)/%.o: %.c
			mkdir -p $(PATH_OBJS)
			$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
			$(RM) -r $(PATH_OBJS)

fclean:			clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all test clean fclean re
