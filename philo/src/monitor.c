/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 08:01:46 by nvan-win      #+#    #+#                 */
/*   Updated: 2022/02/11 10:53:30 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo, int i)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->data->status_lock);
	time = get_time();
	if (time == 0)
		return (ERROR);
	if (time >= (philo[i].time_start_eating + philo->data->time_to_die))
	{
		pthread_mutex_unlock(&philo->data->status_lock);
		if (status_lock(&philo[i], "died\n", 0) == ERROR)
			return (ERROR);
		pthread_mutex_lock(&philo->data->status_lock);
		philo->data->philo_died = 1;
		pthread_mutex_unlock(&philo->data->status_lock);
		return (STOP_SIMULATION);
	}
	pthread_mutex_unlock(&philo->data->status_lock);
	return (0);
}

int	all_philos_full(t_philo *philo)
{
	if (philo->data->num_times_to_eat != 0)
	{
		if (pthread_mutex_lock(&philo->data->full_lock))
			return (write_error("pthread_mutex_lock failed\n"));
		if (philo->data->philos_full == philo->data->num_philo)
		{
			if (pthread_mutex_unlock(&philo->data->full_lock))
				return (write_error("pthread_mutex_unlock failed\n"));
			return (STOP_SIMULATION);
		}
		if (pthread_mutex_unlock(&philo->data->full_lock))
			return (write_error("pthread_mutex_unlock failed\n"));
	}
	return (0);
}

int	single_philo(t_philo *philo)
{
	unsigned long	time;

	if (timer(philo->data->time_to_die))
		return (ERROR);
	time = get_time();
	if (time == 0)
		return (ERROR);
	if (printf("%lu %d %s", (time - philo->data->start_time), \
		philo->num, "died\n") == ERROR)
		return (write_error("printf failed\n"));
	return (STOP_SIMULATION);
}

int	monitor(t_philo *philo)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (philo->data->num_philo == 1)
		return (single_philo(philo));
	while (i < philo->data->num_philo)
	{
		res = all_philos_full(philo);
		if (res == ERROR || res == STOP_SIMULATION)
			return (res);
		res = check_death(philo, i);
		if (res == ERROR || res == STOP_SIMULATION)
			return (res);
		i++;
	}
	if (usleep(1500) == ERROR)
		return (write_error("usleep failed\n"));
	return (0);
}
