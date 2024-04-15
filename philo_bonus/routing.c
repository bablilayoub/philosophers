/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:55:29 by abablil           #+#    #+#             */
/*   Updated: 2024/04/15 23:45:12 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_death(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	while (1)
	{
		if (get_time() - data->last_time_eat > data->time_to_die)
		{
			sem_wait(data->print);
			printf("%lld %ld died\n", get_time() - data->start_time,
				data->philo_id);
			exit(1);
		}
		if (data->n_times_to_eat != -1 && data->meals >= data->n_times_to_eat)
			exit(0);
	}
	return (NULL);
}

void	*routine(t_data *data)
{
	while (1)
	{
		sem_wait(data->forks);
		print(data, "has taken a fork");
		sem_wait(data->forks);
		print(data, "has taken a fork");
		print(data, "is eating");
		custom_usleep(data->time_to_eat);
		data->last_time_eat = get_time();
		sem_post(data->forks);
		sem_post(data->forks);
		data->meals += 1;
		print(data, "is sleeping");
		custom_usleep(data->time_to_sleep);
		print(data, "is thinking");
	}
}
