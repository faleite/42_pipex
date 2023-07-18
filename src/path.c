/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faaraujo <faaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:33:08 by faaraujo          #+#    #+#             */
/*   Updated: 2023/07/18 20:41:09 by faaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *var_path(char *envp[])
{
	int i;
	char *path;

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

char	*cmd_path(char *envp[], char *cmd)
{
	char	*command;
	char	**path_arr;
	size_t	p_len;
	size_t	c_len;

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

int	main(int argc, char *argv[], char *envp[])
{
//	char s1[] = "Fabr    ";
//	char s2[] = "icio";
//	char **path;
//	size_t len;

	(void)argc;
	(void)argv;

	printf("%s", cmd_path(envp, "cat"));

	return (0);
}