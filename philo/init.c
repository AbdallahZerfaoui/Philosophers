/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:30:26 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/17 13:30:26 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_simulation	*allocate_simulation(void)
{
	t_simulation	*simulation;

	simulation = ft_calloc(1, sizeof(t_simulation));
	// if (simulation == NULL)
	// 	return (NULL);
	return (simulation);
}

int	check_limits(char **argv)
{
	int	i;
	int	len;
	int	val;

	i = 1;
	while (i < 5)
	{
		val = ft_atoi(argv[i]);
		len = ft_strlen(argv[i]);
		if (len > 10 || val <= 0)
			return (0);
		if (i == 1 && val > 200)
			return (0);
		if (i > 1 && val > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	parse_arguments(t_table *table, char **argv)
{
	if (check_limits(argv) == 0)
		handle_invalid_args();
	table->num_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		return (ft_atoi(argv[5]));
	return (INT_MAX);
}

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
		memset(philosopher->log_buffer, 0, sizeof(philosopher->log_buffer));
		i++;
	}
}

void	destroy_mutexes(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->table->num_philosophers)
	{
		pthread_mutex_destroy(&simulation->table->forks[i].fork_mutex);
		pthread_mutex_destroy(&simulation->philosophers[i].philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&simulation->log_mutex);
	pthread_mutex_destroy(&simulation->death_mutex);
	// pthread_mutex_destroy(&simulation->table->start_time_mutex);
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
	int				nbr_monitors;

	simulation = allocate_simulation();
	if (simulation == NULL)
		return (handle_allocation_failure(simulation, 1));
	simulation->table = ft_calloc(1, sizeof(t_table));
	if (simulation->table == NULL)
		return(handle_allocation_failure(simulation, 2));
	mini_nbr_meals = parse_arguments(simulation->table, argv);
	if (allocate_forks(simulation) == -1 || mini_nbr_meals == -1)
		return(handle_allocation_failure(simulation, 3));
	pthread_mutex_init(&simulation->log_mutex, NULL);
	pthread_mutex_init(&simulation->death_mutex, NULL);
	// pthread_mutex_init(&simulation->table->start_time_mutex, NULL);
	if (allocate_philosophers(simulation, mini_nbr_meals) == -1)
		return(handle_allocation_failure(simulation, 4));
	nbr_monitors = get_nbr_chuncks(simulation->table->num_philosophers);
	simulation->monitors = ft_calloc(nbr_monitors, sizeof(pthread_t));
	if (simulation->monitors == NULL)
		return(handle_allocation_failure(simulation, 5));
	simulation->table->philosophers = simulation->philosophers;
	// init_philosophers(simulation, mini_nbr_meals);
	simulation->table->start_time = current_time();
	// simulation->start_simulation = simulation->table->start_time + 10; // should i keep this variable?
	return (simulation);
}
