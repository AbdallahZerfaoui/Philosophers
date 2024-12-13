/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:45:59 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/05 20:56:32 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philosophers(t_simulation *simulation, int mini_nbr_meals)
{
	t_philosopher	*philosopher;
	int	i;

	i = 0;
	while (i < simulation->table->num_philosophers)
	{
		philosopher = &simulation->philosophers[i];
		philosopher->id = i;
		philosopher->times_eaten = 0;
		philosopher->last_meal_time = 0;
		pthread_mutex_init(&philosopher->philo_mutex, NULL);
		// pthread_mutex_init(&philosopher->times_eaten_mutex, NULL);
		// pthread_mutex_init(&philosopher->last_meal_time_mutex, NULL);
		// pthread_mutex_init(&philosopher->meal_end_time_mutex, NULL);
		// pthread_mutex_init(&philosopher->wake_up_time_mutex, NULL);
		philosopher->mini_nbr_meals = mini_nbr_meals;
		set_last_time_meal(philosopher);
		philosopher->meal_end_time = 0;
		philosopher->wake_up_time = 0;
		philosopher->left_fork = -1;
		philosopher->right_fork = -1;
		philosopher->is_eating = 0;
		// philosopher->got_left_fork_time = 0;
		philosopher->simulation = simulation;
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
		// simulation->table->forks[i].owner = -1;
		pthread_mutex_init(&simulation->table->forks[i].fork_mutex, NULL);
		// pthread_mutex_init(&simulation->table->forks[i].owner_mutex, NULL);
		i++;
	}
}

/***
 * @brief Unlock all the forks
 * @note this function is called when a philosopher dies
 */
// void unlock_all_forks(t_simulation *simulation)
// {
// 	int	i;

// 	i = 0;
// 	while (i < simulation->table->num_philosophers)
// 	{
// 		pthread_mutex_unlock(&simulation->table->forks[i].fork_mutex);
// 		i++;
// 	}
// }

void	destroy_mutexes(t_simulation *simulation)
{
	int	i;

	i = 0;
	// unlock_all_forks(simulation);
	while (i < simulation->table->num_philosophers)
	{
		pthread_mutex_destroy(&simulation->table->forks[i].fork_mutex);
		pthread_mutex_destroy(&simulation->philosophers[i].philo_mutex);
		// pthread_mutex_destroy(&simulation->table->forks[i].owner_mutex);
		// pthread_mutex_destroy(&simulation->philosophers[i].times_eaten_mutex);
		// pthread_mutex_destroy(&simulation->philosophers[i].last_meal_time_mutex);
		// pthread_mutex_destroy(&simulation->philosophers[i].meal_end_time_mutex);
		// pthread_mutex_destroy(&simulation->philosophers[i].wake_up_time_mutex);
		i++;
	}
	// pthread_mutex_destroy(&simulation->print_mutex);
	pthread_mutex_destroy(&simulation->log_mutex);
	pthread_mutex_destroy(&simulation->death_mutex);
	// pthread_mutex_destroy(&simulation->starvation_mutex);
	pthread_mutex_destroy(&simulation->table->start_time_mutex);
	// pthread_mutex_destroy(&simulation->table->nbr_forks_mutex);
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
	if (simulation == NULL)
		return (NULL);
	simulation->someone_died = 0;
	// simulation->someone_starving = 0;
	simulation->log_lst = NULL;
	simulation->table = ft_calloc(1, sizeof(t_table));
	if (simulation->table == NULL)
	{
		free(simulation);
		return (NULL);
	}
	simulation->table->num_philosophers = ft_atoi(argv[1]);
	// simulation->table->nbr_forks = ft_atoi(argv[1]);
	simulation->table->time_to_die = ft_atoi(argv[2]);
	simulation->table->time_to_eat = ft_atoi(argv[3]);
	simulation->table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		mini_nbr_meals = ft_atoi(argv[5]);
	else
		mini_nbr_meals = INT_MAX;
	simulation->table->forks = (t_fork *) \
		ft_calloc(simulation->table->num_philosophers, sizeof(t_fork));
	if (simulation->table->forks == NULL)
	{
		free(simulation->table);
		free(simulation);
		return (NULL);
	}
	init_forks(simulation);
	// pthread_mutex_init(&simulation->print_mutex, NULL);
	pthread_mutex_init(&simulation->log_mutex, NULL);
	pthread_mutex_init(&simulation->death_mutex, NULL);
	// pthread_mutex_init(&simulation->starvation_mutex, NULL);
	pthread_mutex_init(&simulation->table->start_time_mutex, NULL);
	// pthread_mutex_init(&simulation->table->nbr_forks_mutex, NULL);
	simulation->philosophers = (t_philosopher *) \
		ft_calloc(simulation->table->num_philosophers, sizeof(t_philosopher));
	if (simulation->philosophers == NULL)
	{
		destroy_mutexes(simulation);
		free(simulation->table->forks);
		free(simulation->table);
		free(simulation);
		return (NULL);
	}
	simulation->table->philosophers = simulation->philosophers;
	init_philosophers(simulation, mini_nbr_meals);
	simulation->table->start_time = current_time();
	simulation->start_simulation = simulation->table->start_time + 10; // should i keep this variable?
	return (simulation);
}
