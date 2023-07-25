/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faaraujo <faaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:18:23 by faaraujo          #+#    #+#             */
/*   Updated: 2023/07/25 18:51:42 by faaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ_END 0 // index extremo da leitura do pipe
# define WRITE_END 1 // index extremo da escrita do pipe

# include <stdio.h>// perror
# include <stdlib.h>// exit, malloc, free, execve, wait, waitpid
# include <unistd.h>//access, close, dup2, execve, fork, pipe, read, write
# include <fcntl.h>// open
# include <sys/wait.h>// wait, waitpid

/**
 * 1. pipe_fd -> array de file descriptors para o pipe
 * 2. in_fd -> file descriptor para o ficheiro de entrada
 * 3. out_fd -> file descriptor para o ficheiro de saida
 * 4. cmd -> path do comando
 * 5. args_cmds -> array de strings com os argumentos do comando
 * 6. pid1 -> para o fork (indicador de processos dos filhos)
 * 7. pid2 -> para o fork (indicador de processos dos filhos) 
 */
typedef struct s_data
{
	char	*cmd;
	char	**args_cmds;
	int		pipe_fd[2];
	int		in_fd;
	int		out_fd;
	pid_t	pid1;
	pid_t	pid2;
}	t_data;

int		ft_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	err_case(char *msg, t_data *data);
void	init_data(t_data **buff);
void	using(void);
char	**ft_split(char const *s, char c);
char	*strcpys(char *dest, const char *src1, char c, const char *src2);
char	*var_path(char *envp[]);
char	*cmd_path(char *envp[], char *cmd);

#endif /* PIPEX_H */
