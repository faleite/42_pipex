/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faaraujo <faaraujo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:18:23 by faaraujo          #+#    #+#             */
/*   Updated: 2023/07/11 21:29:58 by faaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

#endif /* PIPEX_H */