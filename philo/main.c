/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:14:55 by abablil           #+#    #+#             */
/*   Updated: 2024/02/06 16:18:35 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
} t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	int			is_full;
	long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
} t_philo;

typedef struct s_data
{
	long	n_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	n_times_eat;
	long	start_time;
	int		end_simulation;
	t_fork	*forks;
	t_philo	*philos;
} t_data;

int	init_data(t_data *data, int total, char **args)
{
	if (total < 5 || total > 6)
		return (exit_program("Invalid number of arguments"));
	data->n_philos = ft_atoi(args[1]);
	data->time_to_die = ft_atoi(args[2]);
	data->time_to_eat = ft_atoi(args[3]);
	data->time_to_sleep = ft_atoi(args[4]);
	if (args[5])
		data->n_times_eat = ft_atoi(args[5]);
	if (data->n_philos <= 0 || data->time_to_die <= 60
		|| data->time_to_eat <= 60 || data->time_to_sleep <= 60
		|| (args[5] && data->n_times_eat <= 60))
		return (exit_program("Invalid arguments, values must be bigger than 0"));
	return (0);
}

int	init_philos(t_data *data)
{
	(void)data;
	return (0);
}

int main(int total, char **args)
{
	t_data data;
	
	if (init_data(&data, total, args) == -1)
		return (-1);
	if (init_philos(&data))
		return (-1);
	return (0);
}