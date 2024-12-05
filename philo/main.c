/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:17:03 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/05 20:36:49 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run_simulation(t_simulation *simulation)
{
	int	i;
	// int	duration;

	i = 0;
	while (i < simulation->table->num_philosophers)
	{
		simulation->philosophers[i].last_meal_time = current_time();
		pthread_create(&simulation->philosophers[i].thread, NULL,
			(void *)philosopher_routine, &simulation->philosophers[i]);
		// printf("philo %d has started\n", i);
		// sleep_ms(100 * i + 100); 
		i++;
	}
	pthread_create(&simulation->monitor, NULL, (void *)monitoring_routine, simulation);
	// duration = 0;
	// while (!is_simulation_over(simulation) && duration < SIMU_DURATION)
	// {
	// 	duration = current_time() - simulation->table->start_time;
	// 	// printf("alles gut : %d\n", simulation->someone_died);
	// }
	i = 0;
	while (i < simulation->table->num_philosophers)
	{
		pthread_join(simulation->philosophers[i].thread, NULL);
		// printf("philo %d has finished\n", i);
		i++;
	}
	pthread_join(simulation->monitor, NULL);
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
		// printf("im here\n");
	}
	// printf("im here\n");
	printf("log size : %d\n", log_size(simulation->log_lst));
	if (simulation->log_lst != NULL)
	{
		print_logs(simulation->log_lst);
	}
	// print_simu_status(simulation);
	destroy_mutexes(simulation);
	free_simulation(simulation);
	return (0);
}
