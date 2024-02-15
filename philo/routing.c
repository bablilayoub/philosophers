/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:55:29 by abablil           #+#    #+#             */
/*   Updated: 2024/02/15 12:44:21 by abablil          ###   ########.fr       */
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

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	philo->is_eating = 1;
	philo->last_meal = get_time();
	print(philo, "is eating");
	philo->meals++;
	if (philo->data->n_times_to_eat != -1 && philo->meals == philo->data->n_times_to_eat)
		philo->is_full = 1;
	pthread_mutex_unlock(&philo->data->lock);
	custom_usleep(philo->data->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->is_full)
		return (1);
	return (0);
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

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (get_time() - philo->last_meal > philo->data->time_to_die && !philo->is_eating)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

void *routine(t_philo *philo)
{
	if (philo->id % 2 && philo->data->n_philos != 1)
		custom_usleep(philo->data->time_to_eat);
	while (!is_dead(philo) && !philo->is_full)
	{
		take_forks(philo);
		if (eat(philo))
			break ;
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}