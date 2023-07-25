/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faaraujo <faaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:02:35 by faaraujo          #+#    #+#             */
/*   Updated: 2023/07/25 18:42:50 by faaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * @brief Computes the length of the string s excluding the terminating null 
 * byte ('\0').
 * @param s Pointer of string.
 * @return Returns the number of bytes in the string pointed to by s.  
*/
int	ft_strlen(char *s)
{
	int	i;
	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	return (i);
}

/**
 * @brief Outputs the string ’s’ to the given file descriptor.
 * @param s The string to output.
 * @param fd The file descriptor on which to write.
*/
void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

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

	if (!src1 || !src2)
		return (NULL);
	i = 0;
	while (*src1 != '\0')
		dest[i++] = *src1++;
	dest[i++] = c;
	while (*src2 != '\0')
		dest[i++] = *src2++;
	dest[i] = '\0';
	return (dest);
}
