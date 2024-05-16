/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:01:50 by abablil           #+#    #+#             */
/*   Updated: 2024/05/16 15:02:32 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*checker(void *args)
{
	t_data		*data;
	long long	current_time;
	long long	last_meal;

	data = (t_data *)args;
	while (1)
	{
		sem_wait(data->lock);
		current_time = get_time();
		last_meal = data->last_meal;
		sem_post(data->lock);
		if (current_time - last_meal > data->time_to_die)
		{
			sem_wait(data->print);
			printf("%lld %ld died\n", current_time - data->start_time,
				data->philo_id);
			exit(1);
		}
		if (data->n_times_to_eat != -1
			&& data->meals_count >= data->n_times_to_eat)
			exit(0);
		usleep(100);
	}
	return (NULL);
}
