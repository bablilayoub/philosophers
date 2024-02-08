/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:14:55 by abablil           #+#    #+#             */
/*   Updated: 2024/02/08 16:56:32 by abablil          ###   ########.fr       */
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
	long			start_time;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
}	t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	long			meals;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
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
	data->start_time = get_time();
	data->philos = NULL;
	data->forks = NULL;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
		return (-1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
	{
		free(data->philos);
		return (-1);
	}
	i = -1;
	while (++i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].meals = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->n_philos];
		pthread_mutex_init(&data->forks[i], NULL);
	}
	return (0);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d has taken a fork\n", get_time() - philo->data->start_time, philo->id);
	printf("%ld %d has taken a fork\n", get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

void	eat(t_philo *philo)
{
	philo->last_meal = get_time();
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d is eating\n", get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	custom_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_and_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d is sleeping\n", get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	custom_usleep(philo->data->time_to_sleep);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d is thinking\n", get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

void	check_death(t_philo *philo)
{
	if (get_time() - philo->last_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->death);
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d died\n", get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->data->death);
		exit(1);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	if (philo->id % 2)
		custom_usleep(philo->data->time_to_eat);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		philo->meals++;
		if (philo->data->n_times_to_eat != -1 && philo->meals == philo->data->n_times_to_eat)
			return (NULL);
		sleep_and_think(philo);
		check_death(philo);
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]))
			return (-1);
	}
	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (-1);
	}
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