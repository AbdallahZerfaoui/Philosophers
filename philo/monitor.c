/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:04:57 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/04 13:55:13 by azerfaou         ###   ########.fr       */
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
	int	i;

	while (!simulation->someone_died)
	{
		i = 0;
		// reset the starvation flag if the philosopher is not starving anymore
		if (simulation->someone_starving && !check_starvation(&simulation->philosophers[simulation->someone_starving - 1]))
		{
			pthread_mutex_lock(&simulation->starvation_mutex);
			simulation->someone_starving = 0;
			pthread_mutex_unlock(&simulation->starvation_mutex);
		}

		while (i < simulation->table->num_philosophers)
		{
			if (!is_alive(&simulation->philosophers[i]))
			{
				report_death(&simulation->philosophers[i]);
				exit(1);
				// break ;
			}
			if (check_starvation(&simulation->philosophers[i]) && !simulation->someone_starving)
			{
				report_starvation(&simulation->philosophers[i]);
			}
			i++;
		}
		if (dinner_is_over(simulation))
		{
			// pthread_mutex_lock(&simulation->print_mutex);
			// printf("DINNER IS OVER\n");
			// pthread_mutex_unlock(&simulation->print_mutex);
			print_action(simulation, 0, "DINNER IS OVER");
			exit(0);
		}
	}
}

// void	monitoring_routine(t_simulation *simulation)
// {
// 	int	i;

// 	while (1)
// 	{
// 		i = 0;
// 		while (i < simulation->table->num_philosophers)
// 		{
// 			if (simulation->someone_died)
// 			{
// 				pthread_mutex_lock(&simulation->print_mutex);
// 				print_action(simulation, simulation->someone_died - 1, "died");
// 				pthread_mutex_unlock(&simulation->print_mutex);
// 				exit(1);
// 			}
// 			if (!is_alive(&simulation->philosophers[i]))
// 			{
// 				report_death(&simulation->philosophers[i]);
// 				exit(1);
// 			}
// 			i++;
// 		}
// 		if (dinner_is_over(simulation))
// 		{
// 			pthread_mutex_lock(&simulation->print_mutex);
// 			print_action(simulation, 0, "dinner is over");
// 			pthread_mutex_unlock(&simulation->print_mutex);
// 			exit(0);
// 		}
// 	}
// }
