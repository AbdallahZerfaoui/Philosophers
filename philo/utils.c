/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:39:33 by azerfaou          #+#    #+#             */
/*   Updated: 2024/11/29 18:27:18 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000LL);
}

void	sleep_ms(int ms)
{
	long long	start;

	start = current_time();
	if (current_time() - start < ms)
		usleep(ms - (current_time() - start));
}

void	print_action(t_table *table, int philo_id, const char *action)
{
	printf("%lld %d %s\n",
		current_time() - table->start_time, philo_id, action);
}

/***
 * @brief Get the forks ids for the philosopher with its given id
 * @note We count in the time sense, so the left fork is the philosopher id
 */
void	get_forks_ids(int philo_id, int *left_fork,
	int *right_fork, int num_philosophers)
{
	*left_fork = philo_id;
	*right_fork = (philo_id + 1) % num_philosophers;
}
