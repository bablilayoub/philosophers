/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:55:29 by abablil           #+#    #+#             */
/*   Updated: 2024/03/30 22:31:06 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	print(philo, FORK);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	print(philo, EAT);
	philo->death_time = get_time() + philo->data->time_to_die;
	philo->meals_count++;
	pthread_mutex_unlock(&philo->philo_lock);
	custom_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	not_over_yet(t_data *data)
{
	int	over;

	pthread_mutex_lock(&data->death_lock);
	over = data->is_over;
	pthread_mutex_unlock(&data->death_lock);
	if (over == 1)
		return (0);
	return (1);
}

void	*one_philo(void *input)
{
	t_philo		*philo;
	long long	init_time;

	philo = (t_philo *) input;
	init_time = get_start_time(philo->data);
	pthread_mutex_lock(&philo->philo_lock);
	philo->death_time = init_time + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->philo_lock);
	pthread_mutex_lock(philo->left_fork);
	print(philo, FORK);
	pthread_mutex_lock(&philo->philo_lock);
	custom_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(&philo->philo_lock);
	pthread_mutex_unlock(philo->left_fork);
	print(philo, DEAD);
	return (NULL);
}

void	*routine(t_philo *philo)
{
	long long	init_time;

	if (philo->id % 2 == 0)
		custom_usleep(philo->data->time_to_eat / 10);
	init_time = get_start_time(philo->data);
	pthread_mutex_lock(&philo->philo_lock);
	philo->death_time = init_time + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->philo_lock);
	while (not_over_yet(philo->data))
	{
		take_forks(philo);
		eat(philo);
		print(philo, SLEEP);
		custom_usleep(philo->data->time_to_sleep);
		print(philo, THINK);
		if (philo->meals_count == philo->data->n_times_to_eat
			&& philo->data->n_times_to_eat != -1)
		{
			pthread_mutex_lock(&philo->philo_lock);
			philo->is_full = 1;
			pthread_mutex_unlock(&philo->philo_lock);
			break ;
		}
	}
	return (NULL);
}
