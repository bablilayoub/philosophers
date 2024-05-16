/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:55:29 by abablil           #+#    #+#             */
/*   Updated: 2024/05/16 01:32:20 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_data *data)
{
	sem_wait(data->forks);
	print(data, FORK);
	sem_wait(data->forks);
	print(data, FORK);
}

void	eat(t_data *data)
{
	print(data, EAT);
	custom_usleep(data->time_to_eat);
	sem_wait(data->lock);
	data->last_meal = get_time();
	sem_post(data->lock);
}

void	sleep_and_think(t_data *data)
{
	sem_post(data->forks);
	sem_post(data->forks);
	data->meals_count += 1;
	print(data, SLEEP);
	custom_usleep(data->time_to_sleep);
	print(data, THINK);
}

void	*routine(t_data *data)
{
	while (1)
	{
		take_forks(data);
		eat(data);
		sleep_and_think(data);
	}
}
