/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:59:53 by abablil           #+#    #+#             */
/*   Updated: 2024/04/15 23:43:05 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_program(char *message, int free, t_data *data)
{
	if (message)
		printf("%s\n", message);
	if (free)
		free_data(data);
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

void	print(t_data *philo, char *message)
{
	sem_wait(philo->print);
	printf("%lld %ld %s\n", get_time() - philo->start_time,
		philo->philo_id, message);
	sem_post(philo->print);
}
