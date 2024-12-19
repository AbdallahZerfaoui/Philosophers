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
	const char *action, char *color)
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
	return (head);
}

// int	log_size(t_log *lst)
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

// void	print_logs(t_log *log_lst)
// {
// 	t_log	*current;
// 	t_log	*prev;
// 	char	message[256];

// 	if (log_lst == NULL)
// 		return ;
// 	current = log_lst;
// 	while (current != NULL)
// 	{
// 		sprintf(message, "%lld %d %s\n",
// 			current->timestamp, current->philo_id, current->action);
// 		// printf("%lld %d %s\n",
// 		// 	current->timestamp, current->philo_id, current->action);
// 		ft_putstr(message);
// 		prev = current;
// 		current = current->next;
// 		free_log(prev);
// 	}
// }

static void	display_log(t_log *log, char *color)
{
	// ft_putstr(RESET);
	ft_putstr(color);
	ft_putnbr(log->timestamp);
	ft_putstr(" ");
	ft_putnbr(log->philo_id);
	ft_putstr(" ");
	ft_putstr(log->action);
	ft_putstr("\n");
}


void	print_logs(t_simulation *simulation)
{
	t_log	*current;
	t_log	*prev;
	t_log	*log_lst;
	// char	message[256];

	lock_safely(&simulation->log_mutex);
	log_lst = simulation->log_lst;
	if (log_lst == NULL)
	{
		unlock_safely(&simulation->log_mutex);
		return ;
	}
	current = log_lst;
	while (current != NULL)
	{
		// sprintf(message, "%lld %d %s\n",
		// 	current->timestamp, current->philo_id, current->action);
		// printf("%lld %d %s\n",
		// 	current->timestamp, current->philo_id, current->action);
		// ft_putstr(message);
		display_log(current, current->color);
		prev = current;
		current = current->next;
		free(prev);
	}
	simulation->log_lst = current;
	unlock_safely(&simulation->log_mutex);
}

// void	print_logs_before(t_simulation *simulation, long long limit)
// {
// 	t_log	*current;
// 	t_log	*tmp;
// 	t_log	*log_lst;
// 	char	message[256];

// 	log_lst = get_log_lst(simulation);
// 	if (log_lst == NULL)
// 		return ;
// 	// if (log_lst == NULL)
// 	// {
// 	// 	pthread_mutex_unlock(&simulation->log_mutex);
// 	// 	return ;
// 	// }
// 	lock_safely(&simulation->log_mutex);
// 	current = log_lst;
// 	// printf("Size of the log: %d\n", log_size(log_lst));
// 	while (current != NULL && current->timestamp < limit)
// 	{
// 		// printf("%lld - philo : %d - %s\n",
// 		// 	current->timestamp, current->philo_id, current->action);
// 		sprintf(message, "%lld %d %s\n",
// 			current->timestamp, current->philo_id, current->action);
// 		ft_putstr(message);
// 		// printf("%lld %d %s\n",
// 		// 	current->timestamp, current->philo_id, current->action);
// 		tmp = current;
// 		current = current->next;
// 		free(tmp);
// 	}
// 	simulation->log_lst = current;
// 	unlock_safely(&simulation->log_mutex);
// }

/***
 * @brief Free the log properly
 */
// void free_log(t_log *log)
// {
// 	free(log);
// }
