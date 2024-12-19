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
 * @param simulation
 * @param parity - 0 for even, 1 for odd
 */
void	monitoring_routine(t_monitoring_data *monitor_data)
{
	int					i;
	int					death_detected;
	t_philo_shared_data	*data;
	t_simulation		*simulation;

	simulation = monitor_data->simulation;
	death_detected = 0;
	data = ft_calloc(1, sizeof(t_philo_shared_data));
	if (data == NULL)
		return ;
	while (!get_someone_died(simulation))
	{
		i = monitor_data->id;
		while (i < simulation->table->num_philosophers)
		{
			get_philo_data(&simulation->philosophers[i], data);
			if (!is_alive(simulation, data) && !death_detected)
			{
				report_death(&simulation->philosophers[i]);
				death_detected = 1;
				break ;
			}
			// free(data);
			// data = NULL;
			i += monitor_data->nbr_monitors;
		}
		if (simulation->philosophers[0].mini_nbr_meals != INT_MAX)
		{	
			// printf("dinner is over : %d\n", dinner_is_over(simulation));
			if (dinner_is_over(simulation))
			{
				break ;
			}
		}
		// print_logs_before(simulation, current_time()
		// 	- get_start_time(simulation));
	}
	// print_simu_status(simulation);
	free(data); // think about removing this allocation
}
