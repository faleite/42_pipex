/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faaraujo <faaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:19:34 by faaraujo          #+#    #+#             */
/*   Updated: 2023/07/21 19:40:14 by faaraujo         ###   ########.fr       */
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

		if (dup2(data->in_fd, STDIN_FILENO) < 0) /* duplica o ficheiro de saida para o stdout */
			err_case("dup2", data);
		//close(data->in_fd);
		
		data->args_cmds = ft_split(argv[2], ' ');
		data->cmd = cmd_path(envp, data->args_cmds[0]);
		/* argv[0] = in_fd, argv[1] = path_cmd1, argv[2] = cmd1, argv[3] = NULL */
		execve(data->cmd, data->args_cmds, envp);
		//char *args[] = {"ls", NULL};
		//execlp(argv[2], args, NULL);
		//execlp(data->cmd, argv[2], NULL);
	}
}

void	second_children(t_data *data, int argc, char *argv[], char *envp[])
{
	data->pid2 = fork(); /* cria o segundo filho */
	if (data->pid2 < 0)
		err_case("fork", data);
	if (data->pid2 == 0) /* se for o filho */
	{	
		/* data->out_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644); */
		data->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->out_fd < 0)
			err_case("open", data);
		
		/* duplica o extremo de escrita do pipe para o stdout */
		if (dup2(data->pipe_fd[READ_END], STDIN_FILENO) < 0)
			err_case("dup2", data);		
		close(data->pipe_fd[WRITE_END]); /* fecha extremo de leitura do pipe */
		close(data->pipe_fd[READ_END]); /* fecha o extremo de escrita do pipe */
		
		if (dup2(data->out_fd, STDOUT_FILENO) < 0) /* duplica o ficheiro de saida para o stdout */
			err_case("HERE!!!", data);
		close(data->out_fd);

		data->args_cmds = ft_split(argv[3], ' ');
		data->cmd = cmd_path(envp, data->args_cmds[0]);
		execve(data->cmd, data->args_cmds, envp);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	if (argc != 5)
		using();
	init_data(&data);

	first_children(data, argv, envp);
	second_children(data, argc, argv, envp);
	
	waitpid(data->pid1, NULL, 0); /* espera pelo primeiro filho */
	/* waitpid(data->pid2, NULL, 0); [> espera pelo segundo filho <] */
	free(data);
	return (0);
}
