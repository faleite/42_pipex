/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faaraujo <faaraujo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:19:34 by faaraujo          #+#    #+#             */
/*   Updated: 2023/07/15 19:53:58 by faaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_data **buff)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	*buff = data;
}

void	err_case(char *msg, t_data *data)
{
	perror(msg);
	close(data->pipe_fd[READ_END]);
	close(data->pipe_fd[WRITE_END]);
	exit(EXIT_FAILURE);
}

void	first_children(t_data *data, char *argv[], char *envp[])
{
	pipe(data->pipe_fd); /* cria o pipe  para cmd1 */
	if (data->pipe_fd[0] < 0 || data->pipe_fd[1] < 0)
		err_case("pipe", data->pipe_fd);
	
	data->pid1 = fork(); /* cria o primeiro filho */
	if (data->pid1 < 0)
		err_case("fork", data->pid1);
	else if (data->pid1 == 0) /* se for o filho */
	{
		close(data->pipe_fd[READ_END]); /* fecha extremo de leitura do pipe */
		
		/* duplica o extremo de escrita do pipe para o stdout */
		if (dup2(data->pipe_fd[WRITE_END], STDOUT_FILENO) < 0)
			err_case("dup2", data->pipe_fd[WRITE_END]);
		close(data->pipe_fd[WRITE_END]); /* fecha o extremo de escrita do pipe */

		/* argv[0] = in_fd, argv[1] = path_cmd1, argv[2] = cmd1, argv[3] = NULL */
		execve("/bin/ls", &argv[2], envp); /* executa o comando cmd1 */
	}
}

void	second_children(t_data *data, char *argv[], char *envp[])
{
	close(data->pipe_fd[WRITE_END]); /* fecha o extremo de escrita do pipe */

	data->pid2 = fork(); /* cria o segundo filho */
	if (data->pid2 < 0)
		err_case("fork", data->pid2);
	else if (data->pid2 == 0) /* se for o filho */
	{
		close(data->pipe_fd[WRITE_END]); /* fecha extremo de leitura do pipe */
		
		/* duplica o extremo de escrita do pipe para o stdout */
		if (dup2(data->pipe_fd[READ_END], STDIN_FILENO) < 0)
			err_case("dup2", data->pipe_fd[READ_END]);
		close(data->pipe_fd[READ_END]); /* fecha o extremo de escrita do pipe */

		dup2(data->out_fd, STDOUT_FILENO); /* duplica o ficheiro de saida para o stdout */

		execve("/usr/bin/wc", &argv[2], envp); /* executa o comando cmd2 */
	}
	else
		close(data->pipe_fd[READ_END]); /* fecha o extremo de leitura do pipe */
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	if (argc != 5)
	{
		perror("Use ./prog infile cmd1 cmd2 outfile\n");
		exit(EXIT_FAILURE);
		// option perror() - ft_putstr_fd("text", 2);
		// return (1);
	}
	init_data(&data);
	data->in_fd = open(argv[1], O_RDONLY); /* abre o ficheiro a ler */
	if (data->in_fd < 0) /* se o ficheiro nao existir */
		err_case("open", data->in_fd);
	/* abre o ficheiro a escrever */
	data->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->out_fd < 0)
		err_case("open", data->out_fd);
	first_children(data, argv, envp);
	second_children(data, argv, envp);
	
	waitpid(data->pid1, NULL, 0); /* espera pelo segundo filho */
	waitpid(data->pid2, NULL, 0); /* espera pelo segundo filho */
	return (0);
}