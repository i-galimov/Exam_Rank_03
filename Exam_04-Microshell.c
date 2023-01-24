#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int ft_err(char *str, char *arg) {
	while (*str)
		write(2, str++, 1);
	if (arg)
		while(*arg)
			write(2, arg++, 1);
	write(1, "\n", 1);
	return (1);
}
int ft_exe(char *av[], int i; int tmp_fd, char *env[]) {
	av[i] = NULL;
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	execve(av[0], av, env);
	return (ft_err("error: cannot execute ", av[0]));
}
int main(int ac, char *av[], char *env[]) {
	int i = 0;
	int pid = 0;
	int tmp_fd = dup(STDIN_FILENO);
	(void)ac;
	int fd[2];
        // Part 1: includes, ft_err, ft_exe, var in main.
	while(av[i] && av[i + 1])
	{
		av = &av[i + 1];
		i = 0;
		while (av[i] && strcmp(av[i], ";") && strcmp(av[i], "|"))
			i++;
		if (strcmp(av[0], "cd") == 0)
		{
			if (i != 2)
				ft_err("error: cd: bad arguments", NULL);
			else if (chdir(av[1]) != 0)
				ft_err("error: cd: cannot change directory to ", av[1]);
		}
                //Part 2: cycle, av++, cd - i != 2, cd - chdir(av[1]) != 0.
		else if (i != 0 && (av[i] == NULL || strcmp(av[i], ";") == 0))
		{
			pid = fork();
			if (pid == 0)
			{
				if (ft_exe(av, i, tmp_fd, env))
					return(1)
			}
			else
			{
				close(tmp_fd);
				while(waitpid(-1, NULL, WUNTRACED) != -1)
					;
				tmp_fd = dup(STDIN_FILENO)
			}
		}
                //Part 3: pid = fork(), if pid == 0 - ft_exe, if pid != 0 - waitpid.
		else if (i != 0 && strcmp(av[i], "|") == 0)
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				if (ft_exe(av, i, tmp_fd, env))
					return (1);
			}
			else
			{
				close(fd[1]);
				close(tmp_fd);
				tmp_fd = fd[0];
			}
                //Part 4: pipe(fd), pid = fork(), if pid == 0, if pid != 0.
		}
	}
	close(tmp_fd);
	return (0);
}
