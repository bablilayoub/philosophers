/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abablil <abablil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:14:55 by abablil           #+#    #+#             */
/*   Updated: 2024/05/16 15:07:02 by abablil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int total, char **args)
{
	t_data	data;

	if (total < 5 || total > 6)
		exit_program("Invalid number of arguments", 0, &data, 0);
	if (init_data(&data, args) == -1)
		exit_program("Failed to init data", 0, &data, 0);
	if (init_process(&data) == -1)
		exit_program("Failed to init process", 1, &data, 0);
	delete_data(&data, 1, 1);
	return (0);
}
