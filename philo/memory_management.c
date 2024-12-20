/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:03:25 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/03 17:52:52 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_log_lst(t_log *log_lst)
{
	t_log	*current;
	t_log	*prev;

	if (log_lst == NULL)
		return ;
	current = log_lst;
	while (current != NULL)
	{
		prev = current;
		current = current->next;
		free(prev);
	}
}

void	free_simulation(t_simulation *simulation)
{
	free(simulation->table->forks);
	free(simulation->table->philosophers);
	free(simulation->table);
	free(simulation->monitors);
	free_log_lst(simulation->log_lst);
	free(simulation);
}

