/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:58:39 by abablil           #+#    #+#             */
/*   Updated: 2024/02/13 13:38:54 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	all_full(int *track, t_data *data)
{
	int i;

	i = -1;
	while (++i < data->n_philos)
	{
		if (data->philos[i].meals < data->n_times_to_eat)
			return (0);
	}
	*track = 1;
	return (1);
}

int	all_alive(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		if (data->philos[i].dead)
			return (0);
	}
	return (1);
}

void check_death(t_data *data)
{
	int i;
	int track;

	track = 0;
	while (1)
	{
		pthread_mutex_lock(&data->print);
		i = -1;
		while (++i < data->n_philos)
		{
			if (data->n_times_to_eat != -1 && all_full(&track, data))
				break;
			if (get_time() - data->philos[i].last_meal > data->time_to_die)
			{
				printf("%ld %d died\n", get_time() - data->start_time, data->philos[i].id);
				data->philos[i].dead = 1;
				track = 1;
			}
			if ((data->n_times_to_eat != -1 && data->philos[i].meals >= data->n_times_to_eat) || track)
				break;
		}
		pthread_mutex_unlock(&data->print);
		if (track)
			break ;
	}
}