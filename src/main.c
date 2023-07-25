/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faaraujo <faaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:19:34 by faaraujo          #+#    #+#             */
/*   Updated: 2023/07/25 18:40:07 by faaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex.h"

/**
 * 1. cria o primeiro filho
 * 2. abre para leitura o aquivo de entrada
 * 3. duplica o extremo de escrita do pipe para o stdout
 * 4. duplica o ficheiro de saida para o stdout
 * 5. Cria o path do primeiro comando e executa
*/
pid_t	first_children(t_data *data, char *argv[], char *envp[])
{
	data->pid1 = fork();
	if (data->pid1 < 0)
		err_case("fork for first child", data);
	if (data->pid1 == 0)
	{
		data->in_fd = open(argv[1], O_RDONLY);
		if (data->in_fd < 0)
			err_case("open input file", data);
		close(data->pipe_fd[READ_END]);
		if (dup2(data->pipe_fd[WRITE_END], STDOUT_FILENO) < 0)
			err_case("dup2 for stdout", data);
		close(data->pipe_fd[WRITE_END]);
		if (dup2(data->in_fd, STDIN_FILENO) < 0)
			err_case("dup2 for stdin", data);
		close(data->in_fd);
		data->args_cmds = ft_split(argv[2], ' ');
		data->cmd = cmd_path(envp, data->args_cmds[0]);
		execve(data->cmd, data->args_cmds, envp);
	}
	return (data->pid1);
}

/**
 * 1. cria o segundo filho
 * 2. abre para escrita o aquivo de saida
 * 3. duplica o extremo de leitura do pipe para o stdin
 * 4. duplica o ficheiro de saida para o stdout
 * 5. Cria o path do segundo comando e executa
*/
pid_t	second_children(t_data *data, int argc, char *argv[], char *envp[])
{
	close(data->pipe_fd[WRITE_END]);
	data->pid2 = fork();
	if (data->pid2 < 0)
		err_case("fork for second child", data);
	if (data->pid2 == 0)
	{
		data->out_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (data->out_fd < 0)
			err_case("open output file", data);
		if (dup2(data->pipe_fd[READ_END], STDIN_FILENO) < 0)
			err_case("dup2 for stdin", data);
		close(data->pipe_fd[READ_END]);
		if (dup2(data->out_fd, STDOUT_FILENO) < 0)
			err_case("dup2 for stdout", data);
		close(data->out_fd);
		data->args_cmds = ft_split(argv[3], ' ');
		data->cmd = cmd_path(envp, data->args_cmds[0]);
		execve(data->cmd, data->args_cmds, envp);
	}
	return (data->pid2);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	if (argc != 5)
		using();
	init_data(&data);
	if (pipe(data->pipe_fd) < 0)
		err_case("pipe", data);
	if (first_children(data, argv, envp) < 0)
		err_case("fork for first child", data);
	if (second_children(data, argc, argv, envp) < 0)
		err_case("fork for second child", data);
	close(data->pipe_fd[READ_END]);
	close(data->pipe_fd[WRITE_END]);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, NULL, 0);
	free(data);
	return (0);
}
