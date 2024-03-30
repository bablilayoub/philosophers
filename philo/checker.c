/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:58:39 by abablil           #+#    #+#             */
/*   Updated: 2024/03/30 06:30:12 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	checker(t_data *data)
{
	long long	death_time;
	int			is_full;
	int			i;
	int			total_finished;

	(1) && (i = -1, total_finished = 0);
	while (++i < data->n_philos)
	{
		pthread_mutex_lock(&data->philos[i].philo_lock);
		death_time = data->philos[i].death_time;
		is_full = data->philos[i].is_full;
		pthread_mutex_unlock(&data->philos[i].philo_lock);
		if (get_time() >= death_time && death_time && !is_full)
		{
			print(&data->philos[i], DEAD);
			return (0);
		}
		total_finished += is_full;
		if (total_finished == data->n_philos)
		{
			end_simulation(data);
			return (0);
		}
	}
	return (1);
}

void	*checker_routine(void *input)
{
	t_data	*data;

	data = (t_data *) input;
	while (1)
	{
		if (!checker(data))
			break ;
		usleep(100);
	}
	return (NULL);
}

int	checker_monitor(t_data *data)
{
	int		i;

	i = -1;
	if (pthread_create(&data->monitor_thread, NULL,
		checker_routine, (void *) data))
		return (1);
	pthread_join(data->monitor_thread, NULL);
	while (++i < data->n_philos)
		pthread_join(data->philos[i].thread, NULL);
	return (0);
}