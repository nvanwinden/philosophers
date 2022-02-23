/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 10:37:43 by nvan-win      #+#    #+#                 */
/*   Updated: 2022/02/11 11:38:25 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
	{
		write_error("gettimeofday failed\n");
		return (0);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	timer(unsigned long ms)
{
	unsigned long	time;

	time = get_time();
	if (time == 0)
		return (write_error("get_time failed\n"));
	while ((get_time() - time) < ms)
	{
		if (usleep(100))
			return (write_error("usleep failed\n"));
	}
	return (0);
}
