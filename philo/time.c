/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:50:49 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/09 14:23:42 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// long long	current_time(void)
// {
// 	struct timeval	tv;
// 	long long		time;

// 	gettimeofday(&tv, NULL);
// 	time = (tv.tv_sec * 1000LL + (tv.tv_usec / 1000LL));
// 	return (time);
// }

long long	current_time_us(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000000LL + tv.tv_usec);
	return (time);
}

long long	current_time(void)
{
	return (current_time_us() / 1000LL);
}

void	sleep_till(long long target_time)
{
	long long	diff;

	diff = target_time * 1000LL - current_time_us();
	while (diff > 0)
	{
		usleep(diff / 2);
		diff = 1000LL * target_time - current_time_us();
	}
}

void	sleep_ms(int ms)
{
	long long	target_time_us;

	target_time_us = current_time_us() + (ms * 1000LL);
	usleep(1000LL * ms - 100);
	while (current_time_us() < target_time_us)
		;
}
