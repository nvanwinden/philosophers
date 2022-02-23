/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 10:39:49 by nvan-win      #+#    #+#                 */
/*   Updated: 2022/02/07 09:04:04 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	free_and_return(t_data **data)
{
	free(*data);
	*data = NULL;
	return (ERROR);
}

int	write_error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return (ERROR);
}

int	destroy_forks(t_data *data, int i)
{
	while (i > 0)
	{
		i--;
		if (pthread_mutex_destroy(&data->forks[i]))
		{
			free(data->forks);
			return (write_error("pthread_mutex_destroy failed\n"));
		}
	}
	free(data->forks);
	return (0);
}

int	destroy_locks(t_data *data)
{
	if (pthread_mutex_destroy(&data->status_lock))
	{
		if (pthread_mutex_destroy(&data->full_lock))
			return (write_error("pthread_mutex_destroy failed\n"));
		return (write_error("pthread_mutex_destroy failed\n"));
	}
	if (pthread_mutex_destroy(&data->full_lock))
		return (write_error("pthread_mutex_destroy failed\n"));
	return (0);
}

int	destroy_philos(t_philo *philo, int i)
{
	while (i > 0)
	{
		i--;
		if (pthread_join(philo[i].id, NULL))
			return (write_error("pthread_join failed\n"));
	}
	return (0);
}
