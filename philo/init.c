/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:57:38 by abablil           #+#    #+#             */
/*   Updated: 2024/02/12 18:02:27 by abablil          ###   ########.fr       */
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
	data->start_time = get_time();
	data->philos = NULL;
	data->forks = NULL;
	pthread_mutex_init(&data->print, NULL);
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
		data->philos[i].last_meal = data->start_time;
		data->philos[i].meals = 0;
		data->philos[i].dead = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->n_philos];
		pthread_mutex_init(&data->forks[i], NULL);
	}
	return (0);
}

int init_simulation(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, (void *)&routine, &data->philos[i]))
			return (-1);
		pthread_detach(data->philos[i].thread);
	}
	check_death(data);
	return (0);
}