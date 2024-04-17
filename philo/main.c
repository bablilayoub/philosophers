/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:14:55 by abablil           #+#    #+#             */
/*   Updated: 2024/04/17 12:34:11 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	delete_data(t_data *data, int free_data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		pthread_mutex_destroy(&data->philos[i].philo_lock);
	i = -1;
	while (++i < data->n_philos)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->time_lock);
	if (free_data)
	{
		free(data->forks);
		free(data->philos);
	}
}

int	main(int total, char **args)
{
	t_data	data;

	if (total < 5 || total > 6)
		return (exit_program("Invalid number of arguments", &data, 0));
	if (init_data(&data, args) == -1)
		return (exit_program("Failed to init data", &data, 0));
	if (init_philos(&data) == -1)
		return (exit_program("Failed to init philos", &data, 0));
	if (init_checker(&data) == -1)
		return (exit_program("Failed to init checker", &data, 1));
	if (checker_monitor(&data) == -1)
		return (exit_program("Failed to start monitor", &data, 1));
	delete_data(&data, 1);
	return (0);
}
