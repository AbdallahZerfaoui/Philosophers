/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:30:10 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/06 19:16:31 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_safely(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		return (LOCK_ERROR);
	}
	return (0);
}

int	unlock_safely(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
	{
		return (UNLOCK_ERROR);
	}
	return (-1);
}

int	get_nbr_chuncks(int num_philosophers)
{
	int	chunks;

	chunks = num_philosophers / CHUNK_SIZE;
	if (num_philosophers % CHUNK_SIZE != 0)
		chunks++;
	return (chunks);
}
