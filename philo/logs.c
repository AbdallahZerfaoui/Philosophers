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

/***
 * @note this function must always be called after locking the right mutex
 */
long long	get_highest_timestamp(t_simulation *simulation)
{
	t_log		*current;
	long long	highest;

	highest = 0;
	current = simulation->log_lst;
	while (current != NULL)
	{
		if (current->timestamp > highest)
			highest = current->timestamp;
		current = current->next;
	}
	return (highest);
}

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
	log->next = NULL;
	return (head);
}

void	swap_logs(t_log *a, t_log *b)
{
	t_log	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_logs(t_log *log_lst)
{
	t_log	*current;
	t_log	*next;

	current = log_lst;
	next = NULL;
	while (current->next != NULL)
	{
		next = current->next;
		if (current->timestamp > next->timestamp)
		{
			swap_logs(current, next);
			current = log_lst;
		}
		else
			current = current->next;
	}
}

/***
 * @note philos are indexed from 1 to num_philos for the display
 */
static void	display_log(const t_log *log, char *color)
{
	printf("%s%lld [%d] %s%s\n",
		color, log->timestamp, log->philo_id + 1, log->action, RESET);
}

void	print_logs(t_simulation *simulation)
{
	t_log	*current;
	t_log	*prev;
	t_log	*log_lst;
	int		died;
	long long	last_timestamp;

	lock_safely(&simulation->log_mutex);
	log_lst = simulation->log_lst;
	if (log_lst == NULL)
	{
		unlock_safely(&simulation->log_mutex);
		return ;
	}
	// t_log	*last_sorted = is_sorted(log_lst);
	// if (last_sorted != NULL)
	// {
	// 	printf("Logs are not sorted\n");
	// 	printf("last timestamp: %lld\n", last_sorted->timestamp);
	// 	unlock_safely(&simulation->log_mutex);
	// 	exit(1);
	// }
	sort_logs(log_lst);
	current = log_lst;
	last_timestamp = get_highest_timestamp(simulation);
	died = 0;
	while (current != NULL && !died)
	{
		if (current->timestamp > last_timestamp - 100)
			break ;
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
