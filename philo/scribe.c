/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scribe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:26:32 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/24 16:51:50 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	scribe_routine(t_simulation *simulation)
{
	// long long	wait_time;

	// wait_time = simulation->table->time_to_eat + simulation->table->time_to_sleep;
	// sleep_ms(100);
	while (!get_someone_died(simulation) && !dinner_is_over(simulation))
	{
		if (simulation)
			print_logs(simulation);
		sleep_ms(SCRIBE_TIME);
	}
	// print_logs(simulation);
	handle_end_of_simulation_log(simulation);
}
