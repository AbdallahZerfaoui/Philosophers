/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:19:38 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/14 16:19:38 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***
 * @note the mutex is initailized inside the init_forks function
 * in parse_inputs
 * @note the RESET is used to reset the color of the terminal
 */
int	main(int argc, char **argv)
{
	t_simulation	*simulation;

	if (argc < MINIMUM_INPUTS)
	{
		simulation = NULL;
		handle_missing_values();
	}
	else
	{
		simulation = parse_inputs(argv);
		if (simulation == NULL)
			return (1);
		run_simulation(simulation);
	}
	ft_putstr(RESET);
	if (simulation != NULL)
	{
		destroy_mutexes(simulation);
		free_simulation(simulation);
	}
	return (0);
}
