/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:29:06 by azerfaou          #+#    #+#             */
/*   Updated: 2024/11/28 16:20:41 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_missing_values(void)
{
	ft_putstr("Missing values\n");
	ft_putstr("Usage: ./philo [nbr_of_philosophers] [time_to_die] ");
	ft_putstr("[time_to_eat] [time_to_sleep] [minimum_nbr_meals]\n");
	exit(1);
}

void	handle_invalid_args(void)
{
	ft_putstr("Invalid arguments\n");
	exit(1);
}

/***
 * @brief Handle allocation failure
 * levels depends on how deep in the code the allocation failed
 * the earlier the failure, the lower the level
 */
void	*handle_allocation_failure(t_simulation *simulation, int level)
{
	if (!simulation)
		return (NULL);
	if (level >= 5)
		free(simulation->monitors);
	if (level >= 4)
	{
		destroy_mutexes(simulation);
		free(simulation->table->forks);
	}
	if (level >= 3)
		free(simulation->table);
	if (level >= 2)
		free(simulation);
	return (NULL);
}
