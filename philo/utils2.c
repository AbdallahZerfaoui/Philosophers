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

int	custom_mutex_trylock(pthread_mutex_t *mutex)
{
	// struct timeval start, now;
	long long elapsed;
	long long start, now;

	// Record the start time
	// gettimeofday(&start, NULL);
	start = current_time_us();

	// Attempt to lock the mutex
	while (pthread_mutex_lock(mutex) != 0)
	{
		// Get the current time
		now = current_time_us();

		// Calculate elapsed time (in microseconds)
		elapsed = now - start;

		// Return failure if mutex couldn't be acquired within a minimal interval (non-blocking)
		if (elapsed > 2)
		{             // 10 microseconds as a non-blocking threshold
			return (1); // Simulate failure (mutex already locked)
		}
	}
	// Successfully locked the mutex
	return (0);
}
