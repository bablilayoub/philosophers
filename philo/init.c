/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:57:38 by abablil           #+#    #+#             */
/*   Updated: 2024/03/30 06:18:49 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int init_data(t_data *data, char **args)
{
	data->n_philos = get_number(args[1]);
	data->time_to_die = get_number(args[2]);
	data->time_to_eat = get_number(args[3]);
	data->time_to_sleep = get_number(args[4]);
	if (args[5])
		data->n_times_to_eat = get_number(args[5]);
	else
		data->n_times_to_eat = -1;
	if (data->n_philos <= 0 || data->time_to_die < 60 || data->time_to_eat < 60 || data->time_to_sleep < 60 || (args[5] && data->n_times_to_eat <= 0))
		return (-1);
	data->philos = NULL;
	data->forks = NULL;
	data->is_over = 0;
	data->start_time = 0;
	if (pthread_mutex_init(&data->time_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->death_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (1);
	return (0);
}

int init_philos(t_data *data)
{
	int i;

	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
		return (-1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (-1);
	i = -1;
	while (++i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_count = 0;
		data->philos[i].death_time = 0;
		data->philos[i].is_eating = 0;
		data->philos[i].is_full = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->n_philos];
		if (pthread_mutex_init(&data->philos[i].philo_lock, NULL))
			return (-1);
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (-1);
	}
	return (0);
}

int init_checker(t_data *data)
{
	int i;

	i = 0;
	data->start_time = get_time();
	if (data->n_philos == 1)
	{
		if (pthread_create(&data->philos[i].thread, NULL, (void *)&one_philo, &data->philos[i]))
			return (-1);
	}
	else
	{
		while (i < data->n_philos)
		{
			if (pthread_create(&data->philos[i].thread, NULL, (void *)&routine, &data->philos[i]))
				return (-1);
			i++;
		}
	}
	return (0);
}