/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:50:49 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/20 14:52:46 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000LL + (tv.tv_usec / 1000LL));
	return (time);
}

void	sleep_ms(int ms)
{
	long long	start;

	start = current_time();
	if (current_time() - start < ms)
		usleep(1000LL * (ms - (current_time() - start)));
}

void	sleep_till(long long target_time)
{
	long long	diff;

	diff = target_time - current_time();
	while (diff > 0)
	{
		usleep(1000LL * (diff / 2));
		diff = target_time - current_time();
	}
}
