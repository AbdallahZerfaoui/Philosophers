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

static int	calculate_side(const t_philosopher *philosopher)
{
	int	side;

	side = 1;
	if (philosopher->id == 0)
		side = 0;
	return (side);
}

/***
 * @note the condition number of philosophers >= 1 is useless
 * the first philo starts left and then we alternate
 */
void	philosopher_routine(t_philosopher *philosopher)
{
	const t_table	*table;
	int				left_fork;
	int				right_fork;
	int				side;

	table = philosopher->simulation->table;
	get_forks_ids(philosopher->id, &left_fork, &right_fork,
		table->num_philosophers);
	if (philosopher->id % 2 == 1)
		usleep(DELAY_AFTER_CREATION);
	side = calculate_side(philosopher);
	while (!is_simulation_over(philosopher->simulation))
	{
		think(philosopher);
		take_forks(philosopher, side);
		eat(philosopher);
		get_a_nap(philosopher);
	}
	unlock_my_forks(philosopher);
}
