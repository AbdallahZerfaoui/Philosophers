/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:46:04 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/20 17:11:36 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	try_take_fork(t_philosopher *philosopher,
	int fork_id, int *fork)
{
	t_table	*table;

	table = philosopher->simulation->table;
	lock_safely(&table->forks[fork_id].fork_mutex);
	set_fork_owner(fork, fork_id, TAKE);
	log_action(philosopher->simulation, philosopher->id,
		"has taken a fork", YELLOW);
}

void	release_fork(t_philosopher *philosopher, int fork_id, int *fork)
{
	t_table	*table;

	table = philosopher->simulation->table;
	unlock_safely(&table->forks[fork_id].fork_mutex);
	set_fork_owner(fork, fork_id, RELEASE);
}

void	handle_single_philosopher(const t_table *table)
{
	sleep_ms(2 * table->time_to_die);
}
