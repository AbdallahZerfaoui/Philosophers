/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scribe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:26:32 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/16 11:40:43 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int	log_size(t_log *lst)
// {
// 	int		len;
// 	t_log	*current;

// 	len = 0;
// 	current = lst;
// 	while (current != NULL)
// 	{
// 		len++;
// 		current = current->next;
// 	}
// 	return (len);
// }

void	scribe_routine(t_simulation *simulation)
{
	long long	time_between_prints;

	time_between_prints = SCRIBE_TIME; //simulation->table->time_to_eat;
	while (!get_someone_died(simulation) && !dinner_is_over(simulation))
	{
		if (simulation)
			print_logs(simulation);
		sleep_ms(time_between_prints);
	}
	print_logs(simulation);
	// print_simu_status(simulation);
	// return (NULL);
}
