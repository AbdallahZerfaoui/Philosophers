/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:39:30 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/14 16:39:30 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @note
 * 1. Check that every philosopher is still alive
 * 2. Check if the dinner is over
 */
void	monitoring_routine(t_simulation *simulation)
{
	int					i;
	int					death_detected;
	t_philo_shared_data	*data;

	death_detected = 0;
	data = NULL;
	while (!get_someone_died(simulation))
	{
		i = 0;

		while (i < simulation->table->num_philosophers)
		{
			data = get_philo_data(&simulation->philosophers[i]);
			if (!is_alive(simulation, data) && !death_detected)
			{
				report_death(&simulation->philosophers[i]);
				death_detected = 1;
				break ;
			}
			free(data);
			data = NULL;
			i++;
		}
		free(data); // think about removing this allocation
		if (dinner_is_over(simulation))
			break ;
		// print_logs_before(simulation, current_time()
		// 	- get_start_time(simulation));
	}
}
