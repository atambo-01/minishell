echo > push_valgrind_log.txt && \
clear && \
make re && \
clear && \
valgrind --leak-check=full \
         --show-leak-kinds=all \
		 --log-file=push_valgrind_log.txt \
         --trace-children=yes \
         --track-origins=yes \
         --track-fds=yes \
         -s ./minishell
