clear && \
make re && \
clear && \
valgrind --leak-check=full \
         --show-leak-kinds=all \
		 --log-file=push_valgrind_log.txt \
         --suppressions=./push_rl.supp \
         --trace-children=yes \
         --track-origins=yes \
         --track-fds=yes \
         -s ./minishell
