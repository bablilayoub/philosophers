/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:14:58 by abablil           #+#    #+#             */
/*   Updated: 2024/05/16 15:12:11 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

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
	long			n_times_to_eat;
	int				*philos;
	long			philo_id;
	long			meals_count;
	long long		start_time;
	long long		last_meal;
	sem_t			*print;
	sem_t			*forks;
	sem_t			*lock;
	pthread_t		monitor_thread;
}	t_data;

// Utils
void		exit_program(char *message, int free, t_data *data,
				int should_kill);
int			get_number(char *str);
void		print(t_data *philo, int message);
void		delete_data(t_data *data, int free_philos, int should_kill);

// Time
long long	get_time(void);
void		custom_usleep(int time_ms);

// Routine
void		*routine(t_data *data);

// Init
int			init_data(t_data *data, char **args);
int			init_process(t_data *data);

// Checker
void		*checker(void *args);