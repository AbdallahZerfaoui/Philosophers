/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:36:07 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/06 13:36:07 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_log	*create_log(long long timestamp, int philo_id, const char *action,
		const char *color)
{
	t_log	*log;

	log = ft_calloc(1, sizeof(t_log));
	if (log == NULL)
		return (NULL);
	log->timestamp = timestamp;
	log->philo_id = philo_id;
	ft_strcpy(log->action, action);
	ft_strcpy(log->color, color);
	return (log);
}

t_log	*add_log(t_log *log_lst, t_log *log)
{
	t_log	*current;
	t_log	*prev;

	if (log_lst == NULL)
		return (log);
	current = log_lst;
	prev = NULL;
	while (current != NULL && log->timestamp >= current->timestamp)
	{
		prev = current;
		current = current->next;
	}
	if (prev == NULL)
	{
		log->next = log_lst;
		return (log);
	}
	else
	{
		prev->next = log;
		log->next = current;
		return (log_lst);
	}
}

/***
 * @note philos are indexed from 1 to num_philos for the display
 */
int	display_log(const t_log *log, const char *color)
{
	int	nbr_chars_printed;

	nbr_chars_printed = printf("%s%lld [%d] %s%s\n", color, log->timestamp,
			log->philo_id + 1, log->action, RESET);
	return (nbr_chars_printed);
}
