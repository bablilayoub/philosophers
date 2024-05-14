/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:01:50 by abablil           #+#    #+#             */
/*   Updated: 2024/05/14 19:37:40 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*checker(void *args)
{
	t_data		*data;
	long long	current_time;

	data = (t_data *)args;
	while (1)
	{
		current_time = get_time();
		if (current_time - data->last_meal > data->time_to_die)
		{
			sem_wait(data->print);
			printf("%lld %ld died\n", current_time - data->start_time,
				data->philo_id);
			exit(1);
		}
		if (data->n_times_to_eat != -1
			&& data->meals_count >= data->n_times_to_eat)
			exit(0);
		custom_usleep(100);
	}
	return (NULL);
}
