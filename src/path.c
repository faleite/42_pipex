/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faaraujo <faaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:33:08 by faaraujo          #+#    #+#             */
/*   Updated: 2023/07/21 19:07:50 by faaraujo         ###   ########.fr       */
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
/*
void	free_mem(char **split)
{
	while (*split)
		free(*split++);
}
*/
/*
int	main(int argc, char *argv[], char *envp[])
{
//	char s1[] = "Fabr    ";
//	char s2[] = "icio";
//	char **path;
//	size_t len;
	t_data *data;
	
	init_data(&data);

	(void)argc;
	(void)argv;
	data->args_cmds = ft_split(argv[1], ' ');
	printf("%s", cmd_path(envp, data->args_cmds[0]));

	return (0);
}
*/
