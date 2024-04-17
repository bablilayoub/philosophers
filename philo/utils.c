/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:59:53 by abablil           #+#    #+#             */
/*   Updated: 2024/04/17 12:35:49 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	end_simulation(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	data->is_over = 1;
	pthread_mutex_unlock(&data->death_lock);
}

int	exit_program(char *message, t_data *data, int free_data)
{
	if (message)
		printf("%s\n", message);
	if (free_data)
		delete_data(data, free_data);
	return (-1);
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

void	print(t_philo *philo, int message)
{
	long long	start_time;
	char		*str;

	start_time = get_start_time(philo->data);
	pthread_mutex_lock(&philo->data->print_lock);
	if (!not_over_yet(philo->data))
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		return ;
	}
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
	printf("%lld %d %s\n", get_time() - start_time, philo->id, str);
	if (message == DEAD)
		end_simulation(philo->data);
	pthread_mutex_unlock(&philo->data->print_lock);
}
