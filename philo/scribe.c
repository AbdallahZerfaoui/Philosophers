/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scribe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:26:32 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/25 14:49:06 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_logs(t_simulation *simulation)
{
	t_log	*current;
	t_log	*prev;
	t_log	*log_lst;
	int		died;

	lock_safely(&simulation->log_mutex);
	log_lst = simulation->log_lst;
	if (log_lst == NULL)
	{
		unlock_safely(&simulation->log_mutex);
		return ;
	}
	current = log_lst;
	died = 0;
	while (current != NULL && !died)
	{
		display_log(current, current->color);
		prev = current;
		died = (ft_strncmp(current->action, "died", 5) == 0);
		current = current->next;
		free(prev);
	}
	simulation->log_lst = current;
	unlock_safely(&simulation->log_mutex);
}

void	handle_end_of_simulation_log(t_simulation *simulation)
{
	t_log	*current;
	int		died;

	died = 0;
	lock_safely(&simulation->log_mutex);
	current = simulation->log_lst;
	while (current != NULL && !died)
	{
		display_log(current, current->color);
		died = (ft_strncmp(current->action, "died", 5) == 0);
		current = current->next;
	}
	unlock_safely(&simulation->log_mutex);
}

void	scribe_routine(t_simulation *simulation)
{
	while (!get_someone_died(simulation) && !dinner_is_over(simulation))
	{
		if (simulation)
			print_logs(simulation);
		sleep_ms(SCRIBE_TIME);
	}
	handle_end_of_simulation_log(simulation);
}
