/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:50:49 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/20 20:29:34 by azerfaou         ###   ########.fr       */
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

void	sleep_ms(int ms)
{
	long long	target_time;

	target_time = current_time() + ms;
	usleep(1000LL * ms - 100);
	while (current_time() < target_time)
		;
}
