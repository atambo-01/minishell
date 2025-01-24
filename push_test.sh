clear && make re && clear && valgrind --leak-check=full --show-leak-kinds=all --suppressions=./push_rl.supp --trace-children=yes --track-origins=yes --track-fds=yes -s ./minishell
