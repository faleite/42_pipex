/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faaraujo <faaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:19:34 by faaraujo          #+#    #+#             */
/*   Updated: 2023/07/17 22:26:46 by faaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_children(t_data *data, char *argv[], char *envp[])
{
	if (pipe(data->pipe_fd) < 0)/* cria o pipe  para cmd1 */
		err_case("pipe", data);
	
	data->pid1 = fork(); /* cria o primeiro filho */
	if (data->pid1 < 0)
		err_case("fork", data);
	if (data->pid1 == 0) /* se for o filho */
	{
		data->in_fd = open(argv[1], O_RDONLY); /* abre o ficheiro a ler */
		if (data->in_fd < 0) /* se o ficheiro nao existir */
			err_case("open", data);
		
		close(data->pipe_fd[READ_END]); /* fecha extremo de leitura do pipe */
		
		/* duplica o extremo de escrita do pipe para o stdout */
		if (dup2(data->pipe_fd[WRITE_END], STDOUT_FILENO) < 0)
			err_case("dup2", data);
		close(data->pipe_fd[WRITE_END]); /* fecha o extremo de escrita do pipe */

		dup2(data->in_fd, STDIN_FILENO); /* duplica o ficheiro de saida para o stdout */
		
		/* argv[0] = in_fd, argv[1] = path_cmd1, argv[2] = cmd1, argv[3] = NULL */
		// execve("/bin/ls", &argv[2], envp); /* executa o comando cmd1 */
		//char *args[] = {"ls", NULL};
		//execlp(argv[2], args, NULL);
		execlp("/bin/ls", argv[2], NULL);
	}
}

void	second_children(t_data *data, int argc, char *argv[], char *envp[])
{
	//close(data->pipe_fd[WRITE_END]); /* fecha o extremo de escrita do pipe */

	data->pid2 = fork(); /* cria o segundo filho */
	if (data->pid2 < 0)
		err_case("fork", data);
	if (data->pid2 == 0) /* se for o filho */
	{	
		data->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->out_fd < 0)
			err_case("open", data);
		/* duplica o extremo de escrita do pipe para o stdout */
		if (dup2(data->pipe_fd[READ_END], STDIN_FILENO) < 0)
			err_case("dup2", data);		

		dup2(data->out_fd, STDOUT_FILENO); /* duplica o ficheiro de saida para o stdout */

		//char *args2[] = {"cat", "cat", NULL};
		//execlp(argv[3], args2, NULL); /* executa o comando cmd2 */
		execlp("/bin/cat", argv[3], NULL);
	}
	close(data->pipe_fd[WRITE_END]); /* fecha extremo de leitura do pipe */
	close(data->pipe_fd[READ_END]); /* fecha o extremo de escrita do pipe */
	//else
		//close(data->pipe_fd[READ_END]); /* fecha o extremo de leitura do pipe */
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	if (argc != 5)
		using();
	init_data(&data);
//	data->in_fd = open(argv[1], O_RDONLY); /* abre o ficheiro a ler */
//	if (data->in_fd < 0) /* se o ficheiro nao existir */
//		err_case("open", data);
	/* abre o ficheiro a escrever */
//	data->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	if (data->out_fd < 0)
//		err_case("open", data);
	first_children(data, argv, envp);
	second_children(data, argc, argv, envp);
	
	waitpid(data->pid1, NULL, 0); /* espera pelo segundo filho */
	waitpid(data->pid2, NULL, 0); /* espera pelo segundo filho */
	free(data);
	return (0);
}