/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:14:58 by abablil           #+#    #+#             */
/*   Updated: 2024/02/12 18:02:32 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

typedef struct s_data
{
	int n_philos;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int n_times_to_eat;
	long start_time;
	struct s_philo *philos;
	pthread_mutex_t *forks;
	pthread_mutex_t print;
} t_data;

typedef struct s_philo
{
	int id;
	long last_meal;
	long meals;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	int dead;
	struct s_data *data;
} t_philo;

// Utils
long	get_time(void);
int		get_number(char *str);
int		exit_program(char *message);
void	custom_usleep(long time);
void	print(t_philo *philo, char *message);

// Routine
void take_forks(t_philo *philo);
void eat(t_philo *philo);
void sleeping(t_philo *philo);
void thinking(t_philo *philo);
void *routine(t_philo *philo);

// Init
int init_data(t_data *data, char **args);
int init_philos(t_data *data);
int init_simulation(t_data *data);

// Checks
int	all_full(int *track, t_data *data);
int	all_alive(t_data *data);
void check_death(t_data *data);