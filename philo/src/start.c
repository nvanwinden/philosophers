/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 10:28:14 by nvan-win      #+#    #+#                 */
/*   Updated: 2022/02/08 09:12:25 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	status_lock(t_philo *philo, char *status, int activity)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->data->status_lock);
	if (philo->data->philo_died == 1)
	{
		pthread_mutex_unlock(&philo->data->status_lock);
		return (ERROR);
	}
	else
	{
		time = get_time();
		if (time == 0)
			return (ERROR);
		if (printf("%lu %d %s", (time - philo->data->start_time), \
			philo->num, status) == ERROR)
			return (write_error("printf failed\n"));
		if (activity == EATING)
			philo->time_start_eating = time;
		pthread_mutex_unlock(&philo->data->status_lock);
	}
	return (0);
}

int	start_simulation(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	if (data->start_time == 0)
		return (ERROR);
	while (i < data->num_philo)
	{
		philo[i].time_start_eating = data->start_time;
		if (pthread_create(&philo[i].id, NULL, &simulation, &philo[i]))
		{
			pthread_mutex_lock(&philo->data->status_lock);
			data->error = 1;
			pthread_mutex_unlock(&philo->data->status_lock);
			if (destroy_philos(philo, i))
				return (ERROR);
			return (write_error("pthread_create failed\n"));
		}
		i++;
	}
	return (0);
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*philo;
	int		i;
	int		num;

	philo = ft_calloc(data->num_philo, sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	i = 0;
	num = 1;
	while (i < data->num_philo)
	{
		philo[i].num = num;
		philo[i].data = data;
		philo[i].left_fork = &philo->data->forks[philo[i].num - 1];
		philo[i].right_fork = &philo->data->forks[philo[i].num % \
		philo[i].data->num_philo];
		num++;
		i++;
	}
	return (philo);
}

int	start(t_data *data)
{
	t_philo	*philo;
	int		res;

	philo = init_philos(data);
	if (philo == NULL)
		return (write_error("malloc error\n"));
	res = 0;
	if (start_simulation(data, philo) == ERROR)
	{
		free(philo);
		return (ERROR);
	}
	while (res != ERROR && res != STOP_SIMULATION)
		res = monitor(philo);
	if (res == ERROR)
	{
		pthread_mutex_lock(&philo->data->status_lock);
		data->error = 1;
		pthread_mutex_unlock(&philo->data->status_lock);
	}
	res = destroy_philos(philo, data->num_philo);
	free(philo);
	return (res);
}
