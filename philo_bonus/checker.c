/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:01:50 by abablil           #+#    #+#             */
/*   Updated: 2024/04/16 19:33:09 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_death(void *args)
{
	t_data		*data;
	long long	current_time;

	data = (t_data *)args;
	while (1)
	{
		current_time = get_time();
		if (current_time - data->last_time_eat > data->time_to_die)
		{
			sem_wait(data->print);
			printf("%lld %ld died\n", current_time - data->start_time,
				data->philo_id);
			exit(1);
		}
		if (data->n_times_to_eat != -1 && data->meals >= data->n_times_to_eat)
			exit(0);
	}
	return (NULL);
}
