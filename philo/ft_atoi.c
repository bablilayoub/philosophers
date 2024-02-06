/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 22:51:57 by abablil           #+#    #+#             */
/*   Updated: 2024/02/06 14:58:57 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_whitespaces(char const *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int	ft_atoi(char const *str)
{
	int				i;
	int				sign;
	unsigned long	result;

	sign = 1;
	result = 0;
	if (!str || str[0] == '\0')
		return (result);
	i = ft_whitespaces(str);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result * 10 + (str[i] - '0') > 9223372036854775807)
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)result * sign);
}
