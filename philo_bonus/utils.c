/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:59:53 by abablil           #+#    #+#             */
/*   Updated: 2024/05/14 19:38:00 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	delete_data(t_data *data, int free_philos)
{
	int		i;
	int		status;

	i = -1;
	while (++i < data->n_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < data->n_philos)
				kill(data->philos[i], SIGKILL);
			break ;
		}
	}
	sem_close(data->print);
	sem_close(data->forks);
	sem_unlink("/print");
	sem_unlink("/forks");
	if (free_philos)
		free(data->philos);
}

void	exit_program(char *message, int free, t_data *data)
{
	if (message)
		printf("%s\n", message);
	delete_data(data, free);
	exit(1);
}

int	get_number(char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] == '0' && str[i + 1] != '\0')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	print(t_data *data, int message)
{
	char		*str;
	long long	current_time;

	current_time = get_time();
	sem_wait(data->print);
	if (message == FORK)
		str = "has taken a fork";
	else if (message == EAT)
		str = "is eating";
	else if (message == SLEEP)
		str = "is sleeping";
	else if (message == THINK)
		str = "is thinking";
	else
		str = "died";
	printf("%lld %ld %s\n", current_time - data->start_time,
		data->philo_id, str);
	sem_post(data->print);
}
