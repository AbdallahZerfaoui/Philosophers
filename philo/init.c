/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:45:59 by azerfaou          #+#    #+#             */
/*   Updated: 2024/11/29 18:30:13 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philosophers(t_simulation *simulation, int mini_nbr_meals)
{
	int	i;

	i = 0;
	while (i < simulation->table->num_philosophers)
	{
		simulation->philosophers[i].id = i;
		simulation->philosophers[i].times_eaten = 0;
		simulation->philosophers[i].mini_nbr_meals = mini_nbr_meals;
		simulation->philosophers[i].last_meal_time = 0;
		simulation->philosophers[i].table = simulation->table;
		i++;
	}
}

static void	init_forks(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->table->num_philosophers)
	{
		simulation->table->forks[i].id = i;
		pthread_mutex_init(&simulation->table->forks[i].mutex, NULL);
		i++;
	}
}

/***
 * @brief Parse the inputs and initialize the simulation structure
 * 1. We allocate memory for the simulation structure and the table structure.
 * 2. We fill the table struct
 * 3. We check if the number of meals is provided, if not, we set it to INT_MAX
 * 4. We allocate memory for the forks and the philosophers
 * @return t_simulation*
 */
t_simulation	*parse_inputs(char **argv)
{
	t_simulation	*simulation;
	int				mini_nbr_meals;

	simulation = ft_calloc(1, sizeof(t_simulation));
	simulation->table = ft_calloc(1, sizeof(t_table));
	simulation->table->num_philosophers = ft_atoi(argv[1]);
	simulation->table->time_to_die = ft_atoi(argv[2]);
	simulation->table->time_to_eat = ft_atoi(argv[3]);
	simulation->table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		mini_nbr_meals = ft_atoi(argv[5]);
	else
		mini_nbr_meals = INT_MAX;
	simulation->table->forks = \
		ft_calloc(simulation->table->num_philosophers, sizeof(t_fork));
	init_forks(simulation);
	simulation->philosophers = \
		ft_calloc(simulation->table->num_philosophers, sizeof(t_philosopher));
	init_philosophers(simulation, mini_nbr_meals);
	simulation->table->start_time = current_time();
	return (simulation);
}
