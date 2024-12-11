/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_fork_timeout.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:59:08 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/06 20:07:04 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_lock_data
{
	pthread_mutex_t	*mutex;
	volatile int	lock_acquired;
}					t_lock_data;

void	*lock_thread_function(void *arg)
{
	t_lock_data	*data;

	data = (t_lock_data *)arg;
	pthread_mutex_lock(data->mutex);
	data->lock_acquired = 1;
	return (NULL);
}

int	take_fork_time_out(t_fork *fork, int philo_id)
{
	long long start = current_time();
	long long now;
	long long timeout = FORK_TIME_OUT + philo_id; // The allowed wait time in ms

	t_lock_data data;
	data.mutex = &fork->fork_mutex;
	data.lock_acquired = 0;

	pthread_t helper_thread;
	if (pthread_create(&helper_thread, NULL, lock_thread_function, &data) != 0)
		return (0); // Thread creation failed, treat as fail.

	// Poll until we either acquire the lock or exceed the timeout
	while (1)
	{
		now = current_time();
		if (data.lock_acquired)
		{
			// Lock acquired
			pthread_join(helper_thread, NULL); // The helper thread is done
			return (1);
		}

		if ((now - start) > timeout)
		{
			// Timeout exceeded
			// The helper thread is likely stuck waiting for the lock
			// Cancel the helper thread
			pthread_cancel(helper_thread);
			pthread_join(helper_thread, NULL);
			return (0);
		}

		// Sleep a bit to avoid busy-waiting
		sleep_ms(1); // Sleep 1ms or adjust as necessary
	}

	// Unreachable code, but included to keep the compiler happy
	return (0);
}
