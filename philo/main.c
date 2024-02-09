/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:14:55 by abablil           #+#    #+#             */
/*   Updated: 2024/02/09 18:20:05 by abablil          ###   ########.fr       */
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
}	t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	long			meals;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				dead;
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

void	print(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id, message);
	pthread_mutex_unlock(&philo->data->print);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	philo->last_meal = get_time();
	print(philo, "is eating");
	philo->meals++;
	custom_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	print(philo, "is sleeping");
	custom_usleep(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print(philo, "is thinking");
}
#include <stdbool.h>

bool all_philosophers_dead(t_data *data)
{
    for (int i = 0; i < data->n_philos; i++)
    {
        if (!data->philos[i].dead)
            return false;
    }
    return true;
}
void 	*check_death(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    while (1)
    {
        if (get_time() - philo->last_meal > philo->data->time_to_die)
        {
            print(philo, "died");
			philo->dead = 1;
			break;
			
        }
        if (philo->data->n_times_to_eat != -1 && philo->meals >= philo->data->n_times_to_eat)
            break;
        if (all_philosophers_dead(philo->data))
            break;
    }
    return NULL;
}


void	*routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    pthread_t death;

    if (philo->id % 2)
        custom_usleep(philo->data->time_to_eat);
    if (pthread_create(&death, NULL, &check_death, philo))
        return NULL;
    while (!all_philosophers_dead(philo->data))
    {
        if (philo->data->n_times_to_eat != -1 && philo->meals >= philo->data->n_times_to_eat)
            break;
        take_forks(philo);
        eat(philo);
        sleeping(philo);
        thinking(philo);
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