#include "pipex.h"

typedef struct s_data
{
	int	pipe_fd[2]; /* array de file descriptors para o pipe */
	int	in_fd; /* file descriptor para o ficheiro a ler */
	int	out_fd; /* file descriptor para o ficheiro a escrever */
	int	status; /* para o wait pai */
	pid_t	pid1; /* para o fork (indicador de processos dos filhos) */
	pid_t	pid2; /* para o fork (indicador de processos dos filhos) */
}	t_data;

int	main(int argc, char *argv[], char *envp[])
{
	int fd1[2]; /* array de file descriptors para o pipe */
	int fd2; /* file descriptor para o ficheiro a escrever */
	int status; /* para o wait pai */
	pid_t pid; /* para o fork (indicador de processos dos filhos) */

	pipe(fd1); /* cria o pipe para ls e wc */
	if (pipe(fd1) == -1) /* se o pipe falhar */
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	pid = fork(); /* cria o primeiro filho */
	if (pid == -1) /* se o fork falhar */
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) /* se for o primeiro filho, executa "ls -l" */
	{
		close(fd1[READ_END]); /* fecha o extremo de leitura do pipe */

		dup2(fd1[WRITE_END], STDOUT_FILENO); /* duplica o extremo de escrita do pipe para o stdout */
		close(fd1[WRITE_END]); /* fecha o extremo de escrita do pipe */

		char *args[3];

		args[0] = "ls";
		args[1] = "-l";
		args[2] = NULL;
		execve("/bin/ls", args, NULL); /* executa o comando ls */ 
	}
	else /* Processo Pai */
	{
		close(fd1[WRITE_END]); /* fecha o extremo de escrita do pipe */

		pid = fork(); /* cria o segundo filho */

		if (pid == -1) /* se o fork falhar */
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			/* - O número "0644" especifica que o proprietário do
			 * arquivo tem permissão de leitura e escrita, enquanto
			 * o grupo do arquivo e outros usuários têm permissão de
			 *  leitura somente.
			 * - O_WRONLY = Somente escrita
			 * - O_CREAT = Cria o arquivo se o mesmo nao existir
			 * - O_TRUNC =  ao abrir um arquivo em modo de escrita,
			 * o conteúdo anterior do arquivo é apagado e o arquivo
			 * é truncado para o comprimento zero, o que significa
			 * que o arquivo é esvaziado.*/
			fd2 = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0644); /* abre o ficheiro para escrita */

			dup2(fd1[READ_END], STDIN_FILENO); /* duplica o extremo de leitura do pipe para o stdin */
			close(fd1[READ_END]); /* fecha o extremo de leitura do pipe */

			dup2(fd2, STDOUT_FILENO); /* duplica o ficheiro para o stdout */

			execlp("/usr/bin/wc", "wc", NULL); /* executa o comando wc */
		}
		else /* Processo Pai */
		{
			close(fd1[READ_END]); /* fecha o extremo de leitura do pipe */
		}

		wait(&status); /* espera pelo segundo filho */
		wait(&status); /* espera pelo segundo filho */
		//waitpid(pid, &status, 0); /* espera pelo segundo filho */
		//waitpid(pid, &status, 0); /* espera pelo primeiro filho */

	}
	 return (0);

}