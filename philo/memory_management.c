/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:03:25 by azerfaou          #+#    #+#             */
/*   Updated: 2024/11/29 21:03:52 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_simulation(t_simulation *simulation)
{
	free(simulation->table->forks);
	free(simulation->table->philosophers);
	free(simulation->table);
	free(simulation);
}