/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:54:02 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/12 20:28:33 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_last_time_meal(t_philosopher *philosopher)
{
	long long	last_time_meal;

	pthread_mutex_lock(&philosopher->last_meal_time_mutex);
	last_time_meal = philosopher->last_meal_time;
	pthread_mutex_unlock(&philosopher->last_meal_time_mutex);
	return (last_time_meal);
}

long long	get_meal_end_time(t_philosopher *philosopher)
{
	long long	meal_end_time;

	pthread_mutex_lock(&philosopher->meal_end_time_mutex);
	meal_end_time = philosopher->meal_end_time;
	pthread_mutex_unlock(&philosopher->meal_end_time_mutex);
	return (meal_end_time);
}

long long	get_wake_up_time(t_philosopher *philosopher)
{
	long long	wake_up_time;

	pthread_mutex_lock(&philosopher->wake_up_time_mutex);
	wake_up_time = philosopher->wake_up_time;
	pthread_mutex_unlock(&philosopher->wake_up_time_mutex);
	return (wake_up_time);
}

t_log	*get_log_lst(t_simulation *simulation)
{
	t_log	*log_lst;

	pthread_mutex_lock(&simulation->log_mutex);
	log_lst = simulation->log_lst;
	pthread_mutex_unlock(&simulation->log_mutex);
	return (log_lst);
}

int	get_times_eaten(t_philosopher *philosopher)
{
	int	times_eaten;

	pthread_mutex_lock(&philosopher->times_eaten_mutex);
	times_eaten = philosopher->times_eaten;
	pthread_mutex_unlock(&philosopher->times_eaten_mutex);
	return (times_eaten);
}

long long 		get_start_time(t_simulation *simulation)
{
	long long	start_time;

	pthread_mutex_lock(&simulation->table->start_time_mutex);
	start_time = simulation->table->start_time;
	pthread_mutex_unlock(&simulation->table->start_time_mutex);
	return (start_time);
}

int get_someone_died(t_simulation *simulation)
{
	int someone_died;

	pthread_mutex_lock(&simulation->death_mutex);
	someone_died = simulation->someone_died;
	pthread_mutex_unlock(&simulation->death_mutex);
	return (someone_died);
}
