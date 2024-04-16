/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:57:38 by abablil           #+#    #+#             */
/*   Updated: 2024/04/16 19:33:05 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_semaphores(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("print");
	data->forks = sem_open("forks", O_CREAT, 0644, data->n_philos);
	if (data->forks == SEM_FAILED)
		return (-1);
	data->print = sem_open("print", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
		return (-1);
	return (0);
}

int	init_data(t_data *data, char **args)
{
	data->n_philos = get_number(args[1]);
	data->time_to_die = get_number(args[2]);
	data->time_to_eat = get_number(args[3]);
	data->time_to_sleep = get_number(args[4]);
	if (args[5])
		data->n_times_to_eat = get_number(args[5]);
	else
		data->n_times_to_eat = -1;
	if (data->n_philos <= 0 || data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60 || (args[5] && data->n_times_to_eat <= 0))
		return (-1);
	data->philos = malloc(sizeof(int) * data->n_philos);
	if (!data->philos)
		return (-1);
	data->meals = 0;
	data->forks = NULL;
	data->start_time = 0;
	data->last_time_eat = 0;
	if (init_semaphores(data) == -1)
	{
		free(data->philos);
		return (-1);
	}
	return (0);
}

int	init_process(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->n_philos)
	{
		data->philos[i] = fork();
		if (data->philos[i] == -1)
			exit_program("Failed to fork", 1, data);
		if (data->philos[i] == 0)
		{
			data->philo_id = i + 1;
			data->last_time_eat = data->start_time;
			if (pthread_create(&data->check_monitor,
					NULL, &check_death, data))
				exit_program("Failed to create thread", 1, data);
			routine(data);
		}
	}
	return (0);
}
