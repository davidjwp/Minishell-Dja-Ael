valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes ./minishell

valgrind --suppressions=./minishell.supp --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes ./minishell