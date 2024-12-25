/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:18:01 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/05 20:57:21 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_log	*create_log(long long timestamp, int philo_id,
	const char *action, const char *color)
{
	t_log	*log;

	log = ft_calloc(1, sizeof(t_log));
	if (log == NULL)
		return (NULL);
	log->timestamp = timestamp;
	log->philo_id = philo_id;
	ft_strcpy(log->action, action);
	ft_strcpy(log->color, color);
	log->next = NULL;
	return (log);
}

t_log	*insert_after(t_log *lst, t_log *target, t_log *log)
{
	t_log	*head;

	if (target == NULL)
	{
		log->next = lst;
		return (log);
	}
	head = lst;
	while (lst != NULL)
	{
		if (lst == target)
		{
			log->next = lst->next;
			lst->next = log;
			break ;
		}
		lst = lst->next;
	}
	return (head);
}

t_log	*add_log(t_log *log_lst, t_log *log)
{
	t_log	*head;
	t_log	*prev;

	if (log_lst == NULL)
		return (log);
	head = log_lst;
	while (log_lst != NULL)
	{
		if (log->timestamp < log_lst->timestamp)
		{
			head = insert_after(head, prev, log);
			return (head);
		}
		prev = log_lst;
		log_lst = log_lst->next;
	}
	prev->next = log;
	log->next = NULL;
	return (head);
}

/***
 * @note philos are indexed from 1 to num_philos for the display
 */
void	display_log(const t_log *log, const char *color)
{
	printf("%s%lld [%d] %s%s\n",
		color, log->timestamp, log->philo_id + 1, log->action, RESET);
}
