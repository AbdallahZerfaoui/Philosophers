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

t_log	*create_log(long long timestamp, int philo_id, const char *action)
{
	t_log	*log;

	log = ft_calloc(1, sizeof(t_log));
	if (log == NULL)
		return (NULL);
	log->timestamp = timestamp;
	log->philo_id = philo_id;
	log->action = ft_strdup(action);
	if (log->action == NULL)
	{
		free(log);
		return (NULL);
	}
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
	while (lst->next != NULL)
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
	prev = NULL;
	while (log_lst->next != NULL)
	{
		if (log->timestamp < log_lst->timestamp)
		{
			head = insert_after(head, prev, log);
			return (head);
		}
		prev = log_lst;
		log_lst = log_lst->next;
	}
	log_lst->next = log;
	return (head);
}

int	log_size(t_log *lst)
{
	int		len;
	t_log	*current;

	len = 0;
	current = lst;
	while (current != NULL)
	{
		len++;
		current = current->next;
	}
	return (len);
}

void	print_logs(t_log *log_lst)
{
	t_log	*current;

	if (log_lst == NULL)
		return ;
	current = log_lst;
	// printf("Size of the log: %d\n", log_size(log_lst));
	while (current != NULL)
	{
		// printf("%lld - philo : %d - %s\n",
		// 	current->timestamp, current->philo_id, current->action);
		printf("%lld %d %s\n",
			current->timestamp, current->philo_id, current->action);
		current = current->next;
	}
}

void	print_logs_before(t_simulation *simulation, long long limit)
{
	t_log	*current;
	t_log	*tmp;
	t_log	*log_lst;

	log_lst = simulation->log_lst;
	if (log_lst == NULL)
		return ;
	current = log_lst;
	// printf("Size of the log: %d\n", log_size(log_lst));
	while (current != NULL && current->timestamp < limit)
	{
		// printf("%lld - philo : %d - %s\n",
		// 	current->timestamp, current->philo_id, current->action);
		pthread_mutex_lock(&simulation->log_mutex);
		printf("%lld %d %s\n",
			current->timestamp, current->philo_id, current->action);
		pthread_mutex_unlock(&simulation->log_mutex);
		tmp = current;
		current = current->next;
		free_log(tmp);
	}
	simulation->log_lst = current;
}

/***
 * @brief Free the log properly
 */
void free_log(t_log *log)
{
	free(log->action);
	free(log);
}
