/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:45:59 by azerfaou          #+#    #+#             */
/*   Updated: 2024/11/28 16:16:19 by azerfaou         ###   ########.fr       */
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
	simulation->philosophers = \
		ft_calloc(simulation->table->num_philosophers, sizeof(t_philosopher));
	init_philosophers(simulation, mini_nbr_meals);
	return (simulation);
}


