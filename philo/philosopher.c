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

// void	push_local_log(t_philosopher *philosopher)
// {
// 	int	i;
// 	t_simulation	*simulation;
// 	int	id;
// 	t_log	*log;

// 	i = 0;
// 	id = philosopher->id;
// 	simulation = philosopher->simulation;
// 	lock_safely(&simulation->log_mutex);
// 	while (philosopher->log_buffer[i] != 0)
// 	{
// 		if (i == 1 || i == 2)
// 			log = create_log(philosopher->log_buffer[i], id, "has taken a fork", YELLOW);
// 		else if (i == 3)
// 			log = create_log(philosopher->log_buffer[i], id, "is eating", GREEN);
// 		else if (i == 4)
// 			log = create_log(philosopher->log_buffer[i], id, "is sleeping", BLUE);
// 		else if (i == 0)
// 			log = create_log(philosopher->log_buffer[i], id, "is thinking", CYAN);
// 		simulation->log_lst = add_log(simulation->log_lst, log);
// 		i++;
// 	}
// 	unlock_safely(&simulation->log_mutex);
// 	memset(philosopher->log_buffer, 0, sizeof(philosopher->log_buffer));
// }

static int	calculate_side(t_philosopher *philosopher)
{
	int	side;

	side = 1;
	if (philosopher->id == 0)
		side = 0;
	return (side);
}

void	report_death(t_philosopher *philosopher)
{
	t_simulation	*simulation;

	simulation = philosopher->simulation;
	set_someone_died(philosopher);
	log_action(simulation, philosopher->id, "has died", RED);
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
		sleep_ms(1);
	side = calculate_side(philosopher);
	while (!is_simulation_over(philosopher->simulation))
	{
		think(philosopher);
		// handle_greediness(*philosopher);
		take_forks(philosopher, side);
		eat(philosopher);
		get_a_nap(philosopher);
		// push_local_log(philosopher);
	}
	// ft_putstr("im out\n");
	unlock_my_forks(philosopher);
	return (NULL);
}
