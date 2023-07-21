/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faaraujo <faaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:18:23 by faaraujo          #+#    #+#             */
/*   Updated: 2023/07/21 18:40:42 by faaraujo         ###   ########.fr       */
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
	char	*cmd;
	char	**args_cmds;
	pid_t	pid1; /* para o fork (indicador de processos dos filhos) */
	pid_t	pid2; /* para o fork (indicador de processos dos filhos) */
}	t_data;

/* UTILS */

/**
 * @brief Computes the length of the string s excluding the terminating null 
 * byte ('\0').
 * @param s Pointer of string.
 * @return Returns the number of bytes in the string pointed to by s.  
*/
int		ft_strlen(char *s);

/**
 * @brief compares only the first (at most) n bytes of s1 and s2. 
 * @param s1 Pointer of string.
 * @param s2 Pointer of string.
 * @param n for comparing len characters
 * @return an integer greater than, equal to, or less than 0, according as the
 * string s1 is greater than, equal to, or less than the string s2
 * The comparison is done using unsigned characters, so that `\200' is greater
 * than `\0'.
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Outputs the string ’s’ to the given file descriptor.
 * @param s The string to output.
 * @param fd The file descriptor on which to write.
*/
void	ft_putstr_fd(char *s, int fd);
void	err_case(char *msg, t_data *data);
void	init_data(t_data **buff);
void	using(void);

/**
 * @brief Allocates (with malloc(3)) and returns an array of strings obtained by
 * splitting ’s’ using the character ’c’ as a delimiter
 * The array must end with a NULL pointer.
 * @param s The string to be split.
 * @param c The delimiter character.
 * @return The array of new strings resulting from the split. NULL if the
 * allocation fails.
*/
char	**ft_split(char const *s, char c);
char	*strcpys(char *dest, const char *src1, char c, const char *src2);
char    *var_path(char *envp[]);
char	*cmd_path(char *envp[], char *cmd);

#endif /* PIPEX_H */
