/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faaraujo <faaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:33:08 by faaraujo          #+#    #+#             */
/*   Updated: 2023/07/25 18:57:39 by faaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * @brief Returns the path variable from the environment
 * @param envp The environment variable
*/
char	*var_path(char *envp[])
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			return (path);
		}
		i++;
	}
	return (path);
}

/**
 * @brief Concatenates the path with the command
 * @param envp The environment variable
 * @param cmd The command to be concatenated
*/
char	*cmd_path(char *envp[], char *cmd)
{
	char	*command;
	char	**path_arr;
	size_t	p_len;
	size_t	c_len;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	path_arr = ft_split(var_path(envp), ':');
	command = NULL;
	while (*path_arr != NULL)
	{
		p_len = ft_strlen(*path_arr);
		c_len = ft_strlen(cmd);
		command = (char *)malloc(sizeof(char) * (p_len + c_len + 2));
		if (!command)
			return (NULL);
		if (access(strcpys(command, *path_arr, '/', cmd), F_OK) == 0)
			return (command);
		free(command);
		path_arr++;
	}
	return (NULL);
}
