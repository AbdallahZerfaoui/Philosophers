/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scribe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:26:32 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/25 18:07:49 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_logs(t_simulation *simulation)
{
	t_log	*current;
	t_log	*prev;
	int		died;

	lock_safely(&simulation->log_mutex);
	current = simulation->log_lst;
	if (current == NULL)
	{
		unlock_safely(&simulation->log_mutex);
		return (0);
	}
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
	return (died);
}

void	scribe_routine(t_simulation *simulation)
{
	int	died;

	if (!simulation)
		return ;
	died = 0;
	while (!died && !dinner_is_over(simulation))
	{
		died = print_logs(simulation);
		sleep_ms(SCRIBE_TIME);
	}
}
