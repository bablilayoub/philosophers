/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:14:55 by abablil           #+#    #+#             */
/*   Updated: 2024/03/30 22:27:44 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	delete_data(t_data *data)
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
	free(data->forks);
	free(data->philos);
}

int	main(int total, char **args)
{
	t_data	data;

	if (total < 5 || total > 6)
		return (exit_program("Invalid number of arguments"));
	if (init_data(&data, args) == -1)
		return (exit_program("Failed to init data"));
	if (init_philos(&data) == -1)
		return (exit_program("Failed to init philos"));
	if (init_checker(&data) == -1)
		return (exit_program("Failed to init checker"));
	if (checker_monitor(&data) == -1)
		return (exit_program("Failed to start monitor"));
	delete_data(&data);
	return (0);
}
