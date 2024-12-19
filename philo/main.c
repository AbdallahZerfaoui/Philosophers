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

t_monitoring_data	*init_monitoring_data(t_simulation *simulation, int nbr_monitors)
{
	t_monitoring_data	*m_data;
	int					i;

	i = 0;
	m_data = (t_monitoring_data *)
		ft_calloc(nbr_monitors, sizeof(t_monitoring_data));
	if (m_data == NULL)
		return (NULL);
	while (i < nbr_monitors)
	{
		m_data[i].simulation = simulation;
		m_data[i].id = i;
		m_data[i].nbr_monitors = nbr_monitors;
		i++;
	}
	return (m_data);
}

static void	run_simulation(t_simulation *simulation)
{
	int	i;
	int	nbr_monitors;
	int	nbr_philosophers;
	t_monitoring_data	*m_data;

	i = 0;
	nbr_philosophers = simulation->table->num_philosophers;
	nbr_monitors = get_nbr_chuncks(nbr_philosophers);
	m_data = init_monitoring_data(simulation, nbr_monitors);
	// data0 = (t_monitoring_data *)ft_calloc(1, sizeof(t_monitoring_data));
	// data1 = (t_monitoring_data *)ft_calloc(1, sizeof(t_monitoring_data));
	// data0->simulation = simulation;
	// data1->simulation = simulation;
	// data1->parity = 1;
	// data0->parity = 0;
	set_start_time(simulation);
	while (i < nbr_philosophers)
	{
		set_last_time_meal(&simulation->philosophers[i]);
		pthread_create(&simulation->philosophers[i].thread, NULL,
			(void *)philosopher_routine, &simulation->philosophers[i]);
		i++;
	}
	i = 0;
	while (i < nbr_monitors)
	{
		pthread_create(&simulation->monitors[i], NULL, (void *)monitoring_routine,
			&m_data[i]);
		i++;
	}
	// pthread_create(&simulation->monitor_bonn, NULL, (void *)monitoring_routine,
	// 	data0);
	// pthread_create(&simulation->monitor_berlin, NULL, (void *)monitoring_routine,
	// 	data1);
	pthread_create(&simulation->scribe, NULL, (void *)scribe_routine,
		simulation);
	i = 0;
	while (i < nbr_philosophers)
	{
		pthread_join(simulation->philosophers[i].thread, NULL);
		// printf("joining philo%d\n", i);
		i++;
	}
	i = 0;
	while (i < nbr_monitors)
	{
		pthread_join(simulation->monitors[i], NULL);
		// printf("joining monitor\n");
		i++;
	}
	// pthread_join(simulation->monitor_bonn, NULL);
	// pthread_join(simulation->monitor_berlin, NULL);
	pthread_join(simulation->scribe, NULL);
	// printf("joining scribe\n");
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
	ft_putstr(RESET); // reset the color
	if (simulation != NULL)
	{
		destroy_mutexes(simulation);
		free_simulation(simulation);
	}
	return (0);
}
