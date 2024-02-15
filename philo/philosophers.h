/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:14:58 by abablil           #+#    #+#             */
/*   Updated: 2024/02/15 12:44:12 by abablil          ###   ########.fr       */
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
	int				n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				n_times_to_eat;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	lock;
	struct s_philo	*philos;
} t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	long			meals;
	int				dead;
	int				is_eating;
	int				is_full;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
} t_philo;

// Utils
long	get_time(void);
int		get_number(char *str);
int		exit_program(char *message);
void	custom_usleep(long time);
void	print(t_philo *philo, char *message);

// Routine
void	*routine(t_philo *philo);

// Init
int	init_data(t_data *data, char **args);
int	init_philos(t_data *data);
int	init_simulation(t_data *data);

// Checks
int		all_full(int *track, t_data *data);
void	monitor(t_data *data);