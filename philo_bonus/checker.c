/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:01:50 by abablil           #+#    #+#             */
/*   Updated: 2024/05/13 18:35:13 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*checker(void *args)
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
		if (data->n_times_to_eat != -1 && data->meals_count >= data->n_times_to_eat)
			exit(0);
	}
	return (NULL);
}