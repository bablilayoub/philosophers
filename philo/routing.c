/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:55:29 by abablil           #+#    #+#             */
/*   Updated: 2024/02/12 17:56:48 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print(philo, "has taken a fork");
}

void eat(t_philo *philo)
{
	philo->last_meal = get_time();
	print(philo, "is eating");
	philo->meals++;
	custom_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void sleeping(t_philo *philo)
{
	print(philo, "is sleeping");
	custom_usleep(philo->data->time_to_sleep);
}

void thinking(t_philo *philo)
{
	print(philo, "is thinking");
}

void *routine(t_philo *philo)
{
	if (philo->id % 2 && philo->data->n_philos != 1)
		custom_usleep(philo->data->time_to_eat);
	while (all_alive(philo->data))
	{
		if (philo->data->n_times_to_eat != -1 && philo->meals == philo->data->n_times_to_eat)
			break;
		take_forks(philo);
		eat(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}