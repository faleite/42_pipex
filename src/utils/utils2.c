/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faaraujo <faaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:35:06 by faaraujo          #+#    #+#             */
/*   Updated: 2023/07/25 18:57:56 by faaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * @brief The error case function, returns an error message, frees the data
 * and closes the file descriptors
 * @param msg The error message
 * @param data The data to be freed
*/
void	err_case(char *msg, t_data *data)
{
	perror(msg);
	free(data);
	if (data->in_fd > -1)
		close(data->in_fd);
	if (data->out_fd > -1)
		close(data->out_fd);
	exit(EXIT_FAILURE);
}

/**
 * @brief The funcition initializes the data structure
*/
void	init_data(t_data **buff)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	data->cmd = NULL;
	data->args_cmds = NULL;
	data->in_fd = -1;
	data->out_fd = -1;
	*buff = data;
}

/**
 * @brief The function prints the error message
 * for the wrong number of arguments
 * More message you can added:
 * ft_putstr_fd("Error: wrong number of arguments\n", 1);
*/
void	using(void)
{
	ft_putstr_fd("Use ./prog infile cmd0 cmd2 outfile\n", 2);
	exit(EXIT_FAILURE);
}
