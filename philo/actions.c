/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:48:21 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/05 20:37:54 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***
 * @brief The philosopher takes the forks
 * so we lock the mutexes of the forks, no other philosopher can take them
 */
void	take_forks(t_philosopher *philosopher, int side)
{
	t_simulation	*simulation;
	t_table			*table;
	int				left_fork;
	int				right_fork;
	t_forks_data	forks_data;

	simulation = philosopher->simulation;
	table = simulation->table;
	get_forks_ids(philosopher->id, &forks_data.left_fork,
		&forks_data.right_fork, simulation->table->num_philosophers);
	left_fork = forks_data.left_fork;
	right_fork = forks_data.right_fork;
	sprintf(forks_data.message_left, "has taken the left fork %d", left_fork);
	sprintf(forks_data.message_right, "has taken the right fork %d", right_fork);
	if (im_alive(philosopher))
	{
		if (side == 0)
		{
			lock_safely(&table->forks[left_fork].fork_mutex);
			set_fork_owner(&philosopher->left_fork, left_fork, TAKE);
			log_action(simulation, philosopher->id, forks_data.message_left);
			// pthread_mutex_lock(&table->nbr_forks_mutex);
			// table->nbr_forks--;
			// pthread_mutex_unlock(&table->nbr_forks_mutex);
			if (table->num_philosophers == 1)
				sleep_ms(2 * table->time_to_die);
			// log_action(simulation, philosopher->id, forks_data.message_left);
			// pthread_mutex_lock(&table->forks[right_fork].fork_mutex);
			else if (philosopher->simulation->table->num_philosophers % 2 >= 0) // != 0
			{
				if (lock_safely(&table->forks[right_fork].fork_mutex) == 0)
				{
					set_fork_owner(&philosopher->right_fork, right_fork, TAKE);
					log_action(simulation, philosopher->id, forks_data.message_right);
					// pthread_mutex_lock(&table->nbr_forks_mutex);
					// table->nbr_forks--;
					// pthread_mutex_unlock(&table->nbr_forks_mutex);
					philosopher->is_eating = 1;
				}
				else // if he can't take the right fork
				{
					unlock_safely(&table->forks[left_fork].fork_mutex);
					set_fork_owner(&philosopher->left_fork, left_fork, RELEASE);
					log_action(simulation, philosopher->id, "has released the left fork"); // to remove
					// pthread_mutex_lock(&table->nbr_forks_mutex);
					// table->nbr_forks++;
					// pthread_mutex_unlock(&table->nbr_forks_mutex);
					// log_action(simulation, philosopher->id, "has released the left fork");
					take_forks(philosopher, 0);
				}
			}
			else 
			{
				lock_safely(&table->forks[right_fork].fork_mutex);
				set_fork_owner(&philosopher->right_fork, right_fork, TAKE);
				// pthread_mutex_lock(&table->nbr_forks_mutex);
				// table->nbr_forks--;
				// pthread_mutex_unlock(&table->nbr_forks_mutex);
				log_action(simulation, philosopher->id, forks_data.message_right);
				philosopher->is_eating = 1;
			}
		}
		else // side 1
		{
			lock_safely(&table->forks[right_fork].fork_mutex);
			set_fork_owner(&philosopher->right_fork, right_fork, TAKE);
			// pthread_mutex_lock(&table->nbr_forks_mutex);
			// table->nbr_forks--;
			// pthread_mutex_unlock(&table->nbr_forks_mutex);
			log_action(simulation, philosopher->id, forks_data.message_right);
			lock_safely(&table->forks[left_fork].fork_mutex);
			set_fork_owner(&philosopher->left_fork, left_fork, TAKE);
			// pthread_mutex_lock(&table->nbr_forks_mutex);
			// table->nbr_forks--;
			// pthread_mutex_unlock(&table->nbr_forks_mutex);
			log_action(simulation, philosopher->id, forks_data.message_left);
			philosopher->is_eating = 1;
		}
	}
}
/**
 * @note last meal time is the moment when the philosopher started eating
 * and not when he finished eating
 */
void	eat(t_philosopher *philosopher)
{
	t_table			*table;
	int				left_fork;
	int				right_fork;
	t_forks_data	forks_data;

	table = philosopher->simulation->table;
	get_forks_ids(philosopher->id, &left_fork, &right_fork,
		table->num_philosophers);
	sprintf(forks_data.message_left, "has released the left fork %d",
		left_fork);
	sprintf(forks_data.message_right, "has released the right fork %d",
		right_fork);
	if (im_alive(philosopher))
	{
		// philosopher->last_meal_time = current_time();
		// set_last_time_meal(philosopher);
		// set_meal_end_time(philosopher);
		// set_wake_up_time(philosopher);
		set_philo_times(philosopher);
		// philosopher->meal_end_time = philosopher->last_meal_time
		// 	+ table->time_to_eat;
		// philosopher->wake_up_time = philosopher->meal_end_time
		// 	+ table->time_to_sleep;
		log_action(philosopher->simulation, philosopher->id, "is eating");
		// sleep_ms(table->time_to_eat);
		// sleep_till(philosopher->meal_end_time);
		sleep_till(get_meal_end_time(philosopher));
		unlock_safely(&table->forks[left_fork].fork_mutex);
		set_fork_owner(&philosopher->left_fork, left_fork, RELEASE);
		// pthread_mutex_lock(&table->nbr_forks_mutex);
		// table->nbr_forks++;
		// pthread_mutex_unlock(&table->nbr_forks_mutex);
		// log_action(philosopher->simulation, philosopher->id,
		// 	forks_data.message_left);
		unlock_safely(&table->forks[right_fork].fork_mutex);
		set_fork_owner(&philosopher->right_fork, right_fork, RELEASE);
		// pthread_mutex_lock(&table->nbr_forks_mutex);
		// table->nbr_forks++;
		// pthread_mutex_unlock(&table->nbr_forks_mutex);
		// log_action(philosopher->simulation, philosopher->id,
		// 	forks_data.message_right);
		philosopher->is_eating = 0;
		// pthread_mutex_lock(&philosopher->times_eaten_mutex);
		// philosopher->times_eaten++;
		// pthread_mutex_unlock(&philosopher->times_eaten_mutex);
		set_eaten_meals(philosopher, 1);
	}
	else if (philosopher->is_eating)
	{
		// report_death(philosopher);
		// if (set_fork_owner(philosopher, left_fork, RELEASE) == philosopher->id)
		// 	pthread_mutex_unlock(&table->forks[left_fork].fork_mutex);
		// if (set_fork_owner(philosopher, right_fork, RELEASE) == philosopher->id)
		// 	pthread_mutex_unlock(&table->forks[right_fork].fork_mutex);
		unlock_my_forks(philosopher);
		// philosopher->is_eating = 0; // im not sure about it
		// pthread_mutex_lock(&table->nbr_forks_mutex);
		// table->nbr_forks += 2;
		// pthread_mutex_unlock(&table->nbr_forks_mutex);
	}
}

void	get_a_nap(t_philosopher *philosopher)
{
	// long long	nap_duration;

	// nap_duration = philosopher->simulation->table->time_to_sleep;
	if (im_alive(philosopher))
	{
		log_action(philosopher->simulation, philosopher->id, "is sleeping");
		// if (current_time() < philosopher->wake_up_time)
		// sleep_till(philosopher->wake_up_time);
		sleep_till(get_wake_up_time(philosopher));
	}
	// else
	// {
	// 	sleep_ms(2 * philosopher->simulation->table->time_to_die);
	// }
}

void	think(t_philosopher *philosopher)
{
	if (im_alive(philosopher))
		log_action(philosopher->simulation, philosopher->id, "is thinking");
}

// void	unlock_my_forks(t_philosopher *philosopher)
// {
// 	t_simulation	*simulation;
// 	int	left_fork;
// 	int	right_fork;

// 	simulation = philosopher->simulation;
// 	get_forks_ids(philosopher->id, &left_fork, &right_fork, simulation->table->num_philosophers);
// 	// printf("fork left : %d, fork right : %d\n", left_fork, right_fork);
// 	// pthread_mutex_lock(&simulation->table->forks[left_fork].owner_mutex);
// 	if (set_fork_owner(philosopher, left_fork, RELEASE) == philosopher->id)
// 	{
// 		pthread_mutex_unlock(&simulation->table->forks[left_fork].fork_mutex);
// 	}
// 	// pthread_mutex_unlock(&simulation->table->forks[left_fork].owner_mutex);
// 	// pthread_mutex_lock(&simulation->table->forks[right_fork].owner_mutex);
// 	if(set_fork_owner(philosopher, right_fork, RELEASE) == philosopher->id)
// 	{
// 		pthread_mutex_unlock(&simulation->table->forks[right_fork].fork_mutex);
// 	}
// 	// pthread_mutex_unlock(&simulation->table->forks[right_fork].owner_mutex);
// }

void	unlock_my_forks(t_philosopher *philosopher)
{
	t_simulation	*simulation;
	int	left_fork;
	int	right_fork;

	simulation = philosopher->simulation;
	// get_forks_ids(philosopher->id, &left_fork, &right_fork, simulation->table->num_philosophers);
	left_fork = philosopher->left_fork;
	right_fork = philosopher->right_fork;
	// if (set_fork_owner(philosopher, left_fork, RELEASE) == philosopher->id)
	if (left_fork != -1)
	{
		unlock_safely(&simulation->table->forks[left_fork].fork_mutex);
		philosopher->left_fork = -1;
	}
	// pthread_mutex_unlock(&simulation->table->forks[left_fork].owner_mutex);
	// pthread_mutex_lock(&simulation->table->forks[right_fork].owner_mutex);
	// if(set_fork_owner(philosopher, right_fork, RELEASE) == philosopher->id)
	if (right_fork != -1)
	{
		unlock_safely(&simulation->table->forks[right_fork].fork_mutex);
		philosopher->right_fork = -1;
	}
	// pthread_mutex_unlock(&simulation->table->forks[right_fork].owner_mutex);
}

