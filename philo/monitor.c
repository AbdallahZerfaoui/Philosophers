/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:46:29 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/20 16:46:29 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philosopher_status(t_simulation *simulation,
		t_philo_shared_data *data, int philosopher_id, int *death_detected)
{
	int		status;

	status = 1;
	get_philo_data(&simulation->philosophers[philosopher_id], data);
	if (!is_alive(simulation, data) && !(*death_detected))
	{
		report_death(&simulation->philosophers[philosopher_id]);
		*death_detected = 1;
		status = 0;
	}
	return (status);
}

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
			if (check_philosopher_status
				(simulation, data, i, &death_detected) == 0)
				break ;
			i += monitor_data->nbr_monitors;
		}
		if (dinner_is_over(simulation))
			break ;
	}
	free(data);
}
