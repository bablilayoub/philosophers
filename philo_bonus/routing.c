/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:55:29 by abablil           #+#    #+#             */
/*   Updated: 2024/04/16 19:32:20 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_data *data)
{
	sem_wait(data->forks);
	print(data, "has taken a fork");
	sem_wait(data->forks);
	print(data, "has taken a fork");
}

void	eat(t_data *data)
{
	print(data, "is eating");
	custom_usleep(data->time_to_eat);
	data->last_time_eat = get_time();
}

void	sleep_and_think(t_data *data)
{
	sem_post(data->forks);
	sem_post(data->forks);
	data->meals += 1;
	print(data, "is sleeping");
	custom_usleep(data->time_to_sleep);
	print(data, "is thinking");
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
