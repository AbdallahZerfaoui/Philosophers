/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scribe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:26:32 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/21 20:25:58 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	scribe_routine(t_simulation *simulation)
{
	while (!get_someone_died(simulation) && !dinner_is_over(simulation))
	{
		if (simulation)
			print_logs(simulation);
		sleep_ms(SCRIBE_TIME);
	}
	print_logs(simulation);
}
