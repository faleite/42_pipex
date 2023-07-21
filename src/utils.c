/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faaraujo <faaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:02:35 by faaraujo          #+#    #+#             */
/*   Updated: 2023/07/21 19:24:21 by faaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	err_case(char *msg, t_data *data)
{
	perror(msg);
	free(data);
	if (data->in_fd > 0)
		close(data->in_fd);
	if (data->out_fd > 0)
		close(data->out_fd);
	exit(EXIT_FAILURE);
}

void	init_data(t_data **buff)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	data->in_fd = -1;
	data->out_fd = -1;
	*buff = data;
}

void	using(void)
{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		ft_putstr_fd("Use ./prog infile cmd1 cmd2 outfile\n", 2);
		exit(EXIT_FAILURE);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	i = 0;
	while ((cs1[i] || cs2[i]) && i < n)
	{
		if (cs1[i] != cs2[i])
			return (cs1[i] - cs2[i]);
		i++;
	}
	return (0);
}

/**
 * @brief strcpys() function copies the string pointed to by src1 and src2,
 * to the buffer pointed to by dest.
 * @return a pointer to the destination string dest.
 */
char	*strcpys(char *dest, const char *src1, char c, const char *src2)
{
	size_t	i;

	i = 0;
	while (*src1 != '\0')
		dest[i++] = *src1++;
	dest[i++] = c;
	while (*src2 != '\0')
		dest[i++] = *src2++;
	dest[i] = '\0';
	return (dest);
}

/*int	main()
{
	char s[8];
	char s1[] = "/bin";
	char s2[] =	"ls";

	printf("%s", strcpys(s, s1, '/', s2));
}*/
