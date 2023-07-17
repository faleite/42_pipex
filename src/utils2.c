/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faaraujo <faaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:33:08 by faaraujo          #+#    #+#             */
/*   Updated: 2023/07/17 22:26:52 by faaraujo         ###   ########.fr       */
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

int	main(int argc, char *argv[], char *envp[])
{
	char s1[] = "Fabr";
	char s2[] = "icio";
	char s3[8];
	char **path;

	path = ft_split(var_path(envp), ':');
	strcpy(s1, s2);
	// printf("%s\n", var_path(envp));

	while(*path)
	{
		printf("%s\n", *path);
		path++;
	}
	printf("%s\n", s1); 
	return (0);
}