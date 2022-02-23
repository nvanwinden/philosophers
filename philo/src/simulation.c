/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 10:36:30 by nvan-win      #+#    #+#                 */
/*   Updated: 2022/02/21 10:05:12 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->status_lock);
	if (philo->data->error == 1)
	{
		pthread_mutex_unlock(&philo->data->status_lock);
		return (ERROR);
	}
	if (philo->data->philo_died == 0)
	{
		pthread_mutex_unlock(&philo->data->status_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->status_lock);
	return (1);
}

int	unlock_forks(t_philo *philo, int left_fork, int right_fork, int error)
{
	if (left_fork == 1)
		pthread_mutex_unlock(philo->left_fork);
	if (right_fork == 1)
		pthread_mutex_unlock(philo->right_fork);
	if (error == 1)
		return (ERROR);
	return (0);
}

int	philo_full(t_philo *philo)
{
	if (philo->num_x_eaten == philo->data->num_times_to_eat)
	{
		pthread_mutex_lock(&philo->data->full_lock);
		philo->data->philos_full += 1;
		pthread_mutex_unlock(&philo->data->full_lock);
		return (1);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	int	res;

	res = 0;
	pthread_mutex_lock(philo->left_fork);
	if (status_lock(philo, "has taken a fork\n", 0) == ERROR)
		return (unlock_forks(philo, 1, 0, 1));
	if (philo->data->num_philo == 1)
		return (unlock_forks(philo, 1, 0, 1));
	pthread_mutex_lock(philo->right_fork);
	if (status_lock(philo, "has taken a fork\n", 0)
		|| status_lock(philo, "is eating\n", EATING)
		|| timer(philo->data->time_to_eat)
		|| is_alive(philo))
		return (unlock_forks(philo, 1, 1, 1));
	philo->num_x_eaten += 1;
	unlock_forks(philo, 1, 1, 0);
	return (0);
}

void	*simulation(void *philosopher)
{
	t_philo	*philo;
	int		res;

	philo = (t_philo *)philosopher;
	res = 0;
	if (!(philo->num % 2))
	{
		if (timer(philo->data->time_to_eat))
			return (0);
	}
	while (1)
	{
		if (eating(philo)
			|| philo_full(philo)
			|| status_lock(philo, "is sleeping\n", 0)
			|| timer(philo->data->time_to_sleep)
			|| status_lock(philo, "is thinking\n", 0)
			|| is_alive(philo)
			|| usleep(1500))
			return (0);
	}
	return (0);
}
