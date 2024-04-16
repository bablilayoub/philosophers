/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:33:02 by abablil           #+#    #+#             */
/*   Updated: 2024/04/16 19:31:06 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + (time.tv_usec / 1000));
}

void	custom_usleep(int time_ms)
{
	long long	time;

	time = get_time();
	while (get_time() - time < time_ms)
		usleep(100);
}
