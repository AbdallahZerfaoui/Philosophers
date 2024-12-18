/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/11/29 11:39:26 by azerfaou          #+#    #+#             */
/*   Updated: 2024/11/30 15:51:17 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// The calloc() function allocates memory for an array of nmemb elements of
// size bytes each and returns a pointer to the allocated memory.
// The memory is set to zero. If nmemb or size is 0, then calloc() returns
// either NULL, or a unique pointer value that can later be successfully
// passed to free().

// A less known difference is that in operating systems with optimistic memory
// allocation, like Linux, the pointer returned by malloc isn't backed by real
// memory until the program actually touches it.

// calloc does indeed touch the memory (it writes zeroes on it) and thus you'll
// be sure the OS is backing the allocation with actual RAM (or swap).
// This is also why it is slower than malloc (not only does it have to zero it,
// the OS must also find a suitable memory area by possibly swapping out other
// processes)

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (nitems != 0 && size > SIZE_MAX / nitems)
		return (NULL);
	total_size = nitems * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	memset(ptr, 0, total_size);
	return (ptr);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	while (str[i] == '0')
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = 1 - 2 * (str[i++] == '-');
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (sign * res);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

ssize_t	ft_putstr(char *str)
{
	ssize_t	len;

	len = write(1, str, ft_strlen(str));
	return(len);
}

void	ft_putnbr(long long n)
{
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

void	ft_strcpy(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}
