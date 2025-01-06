/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:01:16 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/20 16:01:16 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***
 * @note should i create the log before or after locking the mutex???
 */
void	log_action(t_simulation *simulation, int philo_id, const char *action,
		const char *color)
{
	t_log		*log;
	long long	timestamp;
	long long	start_time;

	start_time = get_start_time(simulation);
	timestamp = current_time() - start_time;
	log = create_log(timestamp, philo_id, action, color);
	if (!log)
	{
		return ;
	}
	lock_safely(&simulation->log_mutex);
	simulation->log_lst = add_log(simulation->log_lst, log);
	unlock_safely(&simulation->log_mutex);
}

/***
 * @brief Get the forks ids for the philosopher with its given id
 * @note We count in the time sense, so the left fork is the philosopher id
 */
void	get_forks_ids(int philo_id, int *left_fork, int *right_fork,
		int num_philosophers)
{
	*left_fork = philo_id;
	*right_fork = (philo_id + num_philosophers - 1) % num_philosophers;
}

/***
 * @brief Check if the dinner is over
 */
int	dinner_is_over(t_simulation *simulation)
{
	int	i;
	int	mini_nbr_meals;
	int	nbr_meals_eaten;

	i = 0;
	mini_nbr_meals = simulation->philosophers[0].mini_nbr_meals;
	if (mini_nbr_meals == INT_MAX)
		return (0);
	while (i < simulation->table->num_philosophers)
	{
		nbr_meals_eaten = get_times_eaten(&simulation->philosophers[i]);
		if (nbr_meals_eaten < mini_nbr_meals)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

/***
 * @brief Check if the simulation is over
 * The simulation is over if someone died or if the dinner is over
 * @note dinner_over variable is used to decrease the lock time
 */
int	is_simulation_over(t_simulation *simulation)
{
	int	dinner_over;
	int	someone_died;

	someone_died = get_someone_died(simulation);
	if (someone_died)
		return (1);
	dinner_over = dinner_is_over(simulation);
	return (dinner_over);
}
