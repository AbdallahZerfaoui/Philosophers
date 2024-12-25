/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scribe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:26:32 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/25 23:21:13 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_logs(t_simulation *simulation)
{
	t_log		*current;
	t_log		*prev;
	int			died;
	long long	now;

	lock_safely(&simulation->log_mutex);
	now = current_time() - simulation->table->start_time;
	current = simulation->log_lst;
	if (current == NULL)
		return (unlock_safely(&simulation->log_mutex), 0);
	died = 0;
	while (current != NULL && !died)
	{
		if (current->timestamp > now - SCRIBE_TIME_GAP)
			break ;
		display_log(current, current->color);
		prev = current;
		died = (ft_strncmp(current->action, "died", 5) == 0);
		current = current->next;
		free(prev);
	}
	simulation->log_lst = current;
	unlock_safely(&simulation->log_mutex);
	return (died);
}

void	scribe_routine(t_simulation *simulation)
{
	static int	died;

	if (!simulation)
		return ;
	died = 0;
	sleep_ms(SCRIBE_TIME_GAP);
	while (!died && !dinner_is_over(simulation))
	{
		died = print_logs(simulation);
		sleep_ms(SCRIBE_SLEEP_TIME);
	}
}
