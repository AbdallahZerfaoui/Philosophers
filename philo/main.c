/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:19:38 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/14 16:19:38 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run_simulation(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->table->num_philosophers)
	{
		set_last_time_meal(&simulation->philosophers[i]);
		pthread_create(&simulation->philosophers[i].thread, NULL,
			(void *)philosopher_routine, &simulation->philosophers[i]);
		i++;
	}
	set_start_time(simulation);
	pthread_create(&simulation->monitor, NULL, (void *)monitoring_routine,
		simulation);
	pthread_create(&simulation->scribe, NULL, (void *)scribe_routine,
		simulation);
	i = 0;
	while (i < simulation->table->num_philosophers)
	{
		pthread_join(simulation->philosophers[i].thread, NULL);
		i++;
	}
	pthread_join(simulation->monitor, NULL);
	pthread_join(simulation->scribe, NULL);
}

/***
 * @note the mutex is initailized inside the init_forks function
 * in parse_inputs
 */
int	main(int argc, char **argv)
{
	t_simulation	*simulation;

	if (argc < MINIMUM_INPUTS)
	{
		simulation = NULL;
		handle_missing_values();
	}
	else
	{
		simulation = parse_inputs(argv);
		if (simulation == NULL)
			return (1);
		run_simulation(simulation);
	}
	// if (get_log_lst(simulation) != NULL)
	// {
	// 	print_logs(simulation);
	// }
	// print_simu_status(simulation);
	destroy_mutexes(simulation);
	free_simulation(simulation);
	return (0);
}
