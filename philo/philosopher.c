/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:56:50 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/05 20:14:58 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	calculate_side(t_philosopher *philosopher)
{
	int	side;
	int	nbr_philos;

	nbr_philos = philosopher->simulation->table->num_philosophers;
	nbr_philos += 1;
	side = 1;
	// if (nbr_philos % 2 == 0)
	// 	side = philosopher->id % 2;
	// else if (philosopher->id != 0)
	// 	side = (philosopher->id + 1) % 2;
	// else
	// 	side = philosopher->times_eaten % 2;
	// if (philosopher->id == (philosopher->times_eaten % philosopher->simulation->table->num_philosophers))
	// 	side = 0;
	// else
	// 	side = 1;
	// return (side);
	if (philosopher->id == 0)
		side = 0;
	return (side);
}

void	report_death(t_philosopher *philosopher)
{
	t_simulation	*simulation;

	simulation = philosopher->simulation;
	log_action(simulation, philosopher->id, "HAS DIED");
	// pthread_mutex_lock(&simulation->death_mutex);
	// simulation->someone_died = philosopher->id + 1;
	// pthread_mutex_unlock(&simulation->death_mutex);
	set_someone_died(philosopher);
}
/***
 *@note the difference between im alive and is alive is that im alive takes 
 the last meal time from the philosopher structure
 without using the mutex, while is alive uses the getter 
 function to get the last meal time
 */
int	im_alive(const t_philosopher *philosopher)
{
	long long	time_since_last_meal;
	// int			nbr_meals_eaten;

	// pthread_mutex_lock(&philosopher->times_eaten_mutex);
	// nbr_meals_eaten = philosopher->times_eaten;
	// pthread_mutex_unlock(&philosopher->times_eaten_mutex);
	time_since_last_meal = current_time() - philosopher->last_meal_time;
	// if (time_since_last_meal > philosopher->simulation->table->time_to_die
	// 	&& nbr_meals_eaten < philosopher->mini_nbr_meals)
	if (time_since_last_meal > philosopher->simulation->table->time_to_die)
	{
		return (0);
	}
	return (1);
}

int	is_alive(const t_simulation *simulation, const t_philo_shared_data *data)
{
	long long	time_since_last_meal;

	time_since_last_meal = current_time() - data->last_meal_time;
	if (time_since_last_meal > simulation->table->time_to_die)
	{
		return (0);
	}
	return (1);
}

/***
 * @note the condition number of philosophers >= 1 is useless
 * the first philo starts left and then we alternate
 */
void	*philosopher_routine(t_philosopher *philosopher)
{
	const t_table	*table;
	int				left_fork;
	int				right_fork;
	int				side;

	table = philosopher->simulation->table;
	get_forks_ids(philosopher->id, &left_fork, &right_fork,
		table->num_philosophers);
	// sleep_till(philosopher->simulation->start_simulation);
	if (philosopher->id % 2 == 0)
		sleep_ms(table->time_to_eat / 4);
	while (!is_simulation_over(philosopher->simulation))
	{
		side = calculate_side(philosopher);
		// side = 0;
		// side = philosopher->id % 2;
		// if (philosopher->id == (philosopher->times_eaten % philosopher->simulation->table->num_philosophers))
		// 	side = 0;
		// else
		// 	side = 1;
		// 	side = (philosopher->id + philosopher->simulation->table->num_philosophers) % 2;
		// else
		// 	side = (philosopher->id) % 2;
		think(philosopher);
		// handle_greediness(*philosopher);
		take_forks(philosopher, side);
		eat(philosopher);
		get_a_nap(philosopher);
		// }
	}
	// ft_putstr("im out\n");
	unlock_my_forks(philosopher);
	return (NULL);
}
