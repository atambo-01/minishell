clear && make re && clear && gdb -ex	"set  confirm off" -ex	"handle SIGINT SIGQUIT nostop noprint pass" -ex	"run" --args ./minishell
