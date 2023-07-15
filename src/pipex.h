/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faaraujo <faaraujo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:18:23 by faaraujo          #+#    #+#             */
/*   Updated: 2023/07/15 19:08:12 by faaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ_END 0 // index extremo da leitura do pipe
# define WRITE_END 1 // index extremo da escrita do pipe
# define FILE_NAME "file.txt" // nome do ficheiro  a escrever

# include <stdio.h>// perror
# include <stdlib.h>// exit, malloc, free, execve, wait, waitpid
# include <unistd.h>//access;close;dup;dup2;execve;fork;pipe;read;unlink;write
# include <fcntl.h>// open
# include <sys/wait.h>// wait, waitpid

/* Others */

# include <errno.h>// errno
# include <string.h>// strerror
# include <sys/types.h>// wait, waitpid
# include <sys/stat.h>// access, open, unlink
# include <stdbool.h>// bool
# include <sys/errno.h>// errno

typedef struct s_data
{
	int	pipe_fd[2]; /* array de file descriptors para o pipe */
	int	in_fd; /* file descriptor para o ficheiro a ler */
	int	out_fd; /* file descriptor para o ficheiro a escrever */
	int	status; /* para o wait pai */
	pid_t	pid1; /* para o fork (indicador de processos dos filhos) */
	pid_t	pid2; /* para o fork (indicador de processos dos filhos) */
}	t_data;

/* UTILS */

int		ft_strlen(char *s);
void	ft_putstr_fd(char *s, int fd);

#endif /* PIPEX_H */