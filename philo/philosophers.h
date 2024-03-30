/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:14:58 by abablil           #+#    #+#             */
/*   Updated: 2024/03/30 06:28:16 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

#define FORK	1
#define EAT		2
#define SLEEP	3
#define THINK	4
#define DEAD	5

typedef struct s_data
{
	int				n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				n_times_to_eat;
	int				is_over;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	time_lock;
	pthread_t		monitor_thread;
	struct s_philo	*philos;
} t_data;

typedef struct s_philo
{
	int				id;
	long			meals_count;
	int				is_full;
	int				is_eating;
	long long		death_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	philo_lock;
	struct s_data	*data;
} t_philo;

void		end_simulation(t_data *data);

// Utils
long long	get_time(void);
int			get_number(char *str);
int			exit_program(char *message);
void		custom_usleep(long time);
void		print(t_philo *philo, int message);
long long	get_simul_start(t_data *data);

// Routine
int		not_over_yet(t_data *data);
void	*routine(t_philo *philo);

// Init
int		init_data(t_data *data, char **args);
int		init_philos(t_data *data);
int		init_checker(t_data *data);
void	*one_philo(void *input);

// Checker
int		checker_monitor(t_data *data);