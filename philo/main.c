/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:14:55 by abablil           #+#    #+#             */
/*   Updated: 2024/02/07 16:49:39 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

typedef struct s_data
{
	int				n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				n_times_to_eat;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	full;
}	t_data;

typedef struct s_philo
{
	int				id;
	long			start_time;
	long			last_meal;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;
	pthread_mutex_t	*full;
}	t_philo;

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
	if (data->n_philos <= 0 || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60 
		|| (args[5] && data->n_times_to_eat <= 0))
		return (-1);
	return (0);
}

int	init_philos(t_data *data)
{
	static int	i = -1;

	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
		return (-1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (-1);
	while (++i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].start_time = get_time();
		data->philos[i].last_meal = get_time();
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->n_philos];
		data->philos[i].print = &data->print;
		data->philos[i].death = &data->death;
		data->philos[i].full = &data->full;
		pthread_mutex_init(&data->forks[i], NULL);
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->full, NULL);
	return (0);
}

int main(int total, char **args)
{
	t_data	data;
	
	if (total < 5 || total > 6)
		return (exit_program("Invalid number of arguments"));
	if (init_data(&data, args) == -1)
		return (exit_program("Failed to init data"));
	if (init_philos(&data) == -1)
		return (exit_program("Failed to init philos"));
	if (start_simulation(&data) == -1)
		return (exit_program("Failed to start simulation"));
	return (0);
}