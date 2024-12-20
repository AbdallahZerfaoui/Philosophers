/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:03:25 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/03 17:52:52 by azerfaou         ###   ########.fr       */
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

void	free_log_lst(t_log *log_lst)
{
	t_log	*current;
	t_log	*prev;

	if (log_lst == NULL)
		return ;
	current = log_lst;
	while (current != NULL)
	{
		prev = current;
		current = current->next;
		free(prev);
	}
}

void	free_simulation(t_simulation *simulation)
{
	free(simulation->table->forks);
	free(simulation->table->philosophers);
	free(simulation->table);
	free(simulation->monitors);
	free_log_lst(simulation->log_lst);
	free(simulation);
}
