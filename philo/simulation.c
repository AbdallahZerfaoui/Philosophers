/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:46:39 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/26 14:41:45 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_monitoring_data	*init_monitoring_data(t_simulation *simulation,
		int nbr_monitors)
{
	t_monitoring_data	*m_data;
	int					i;

	i = 0;
	m_data = (t_monitoring_data *)ft_calloc(nbr_monitors,
			sizeof(t_monitoring_data));
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

static void	create_philosophers(t_simulation *simulation)
{
	int	i;
	int	nbr_philosophers;

	i = 0;
	nbr_philosophers = simulation->table->num_philosophers;
	while (i < nbr_philosophers)
	{
		set_last_time_meal(&simulation->philosophers[i]);
		pthread_create(&simulation->philosophers[i].thread, NULL,
			(void *)philosopher_routine, &simulation->philosophers[i]);
		i++;
	}
}

static void	create_monitors(t_simulation *simulation, t_monitoring_data *m_data,
		int nbr_monitors)
{
	int	i;

	i = 0;
	while (i < nbr_monitors)
	{
		pthread_create(&simulation->monitors[i], NULL,
			(void *)monitoring_routine, &m_data[i]);
		i++;
	}
}

void	wait_for_threads(pthread_t *threads, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

/**
 * @brief Executes the main simulation flow for
 * the philosopher problem.
 * 1. Calculates the number of monitoring threads needed based
 * on the number of philosophers.
 * 2. Initializes monitoring data structures.
 * 3. Records the start time of the simulation.
 * 4. Creates philosopher threads to simulate their behavior.
 * 5. Creates monitoring threads to supervise philosophers' states.
 * 6. Starts a scribe thread to log simulation events.
 * 7. Waits for all philosopher threads to finish execution.
 * 8. Joins monitoring threads and cleans up monitoring resources.
 * 9. Waits for the scribe thread to finish logging before concluding.
 * @param simulation A pointer to the simulation structure
 * containing all necessary data.
 * @return void
 **/
void	run_simulation(t_simulation *simulation)
{
	int					i;
	int					nbr_monitors;
	int					nbr_philosophers;
	t_monitoring_data	*m_data;

	nbr_philosophers = simulation->table->num_philosophers;
	nbr_monitors = get_nbr_chuncks(nbr_philosophers);
	m_data = init_monitoring_data(simulation, nbr_monitors);
	simulation->table->start_time = current_time();
	create_philosophers(simulation);
	create_monitors(simulation, m_data, nbr_monitors);
	pthread_create(&simulation->scribe, NULL, (void *)scribe_routine,
		simulation);
	i = 0;
	while (i < nbr_philosophers)
	{
		pthread_join(simulation->philosophers[i].thread, NULL);
		i++;
	}
	wait_for_threads(simulation->monitors, nbr_monitors);
	free(m_data);
	pthread_join(simulation->scribe, NULL);
}
