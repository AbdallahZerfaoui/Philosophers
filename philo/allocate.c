/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:58:18 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/20 17:02:38 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_forks(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->table->num_philosophers)
	{
		simulation->table->forks[i].id = i;
		pthread_mutex_init(&simulation->table->forks[i].fork_mutex, NULL);
		i++;
	}
}

static void	init_philosophers(t_simulation *simulation, int mini_nbr_meals)
{
	t_philosopher	*philosopher;
	int				i;

	i = 0;
	while (i < simulation->table->num_philosophers)
	{
		philosopher = &simulation->philosophers[i];
		philosopher->id = i;
		pthread_mutex_init(&philosopher->philo_mutex, NULL);
		philosopher->mini_nbr_meals = mini_nbr_meals;
		set_last_time_meal(philosopher);
		philosopher->left_fork = -1;
		philosopher->right_fork = -1;
		philosopher->simulation = simulation;
		i++;
	}
}

t_simulation	*allocate_simulation(void)
{
	t_simulation	*simulation;

	simulation = ft_calloc(1, sizeof(t_simulation));
	return (simulation);
}

int	allocate_forks(t_simulation *simulation)
{
	t_table	*table;

	table = simulation->table;
	table->forks = ft_calloc(table->num_philosophers, sizeof(t_fork));
	if (table->forks == NULL)
		return (-1);
	init_forks(simulation);
	return (0);
}

int	allocate_philosophers(t_simulation *simulation, int mini_nbr_meals)
{
	simulation->philosophers = (t_philosopher *)
		ft_calloc(simulation->table->num_philosophers, sizeof(t_philosopher));
	if (simulation->philosophers == NULL)
		return (-1);
	simulation->table->philosophers = simulation->philosophers;
	init_philosophers(simulation, mini_nbr_meals);
	return (0);
}
