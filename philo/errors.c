/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:29:06 by azerfaou          #+#    #+#             */
/*   Updated: 2024/11/28 16:20:41 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_missing_values(void)
{
	ft_putstr("Missing values\n");
	ft_putstr("Usage: ./philo [nbr_of_philosophers] [time_to_die] ");
	ft_putstr("[time_to_eat] [time_to_sleep] [minimum_nbr_meals]\n");
	exit(1);
}
