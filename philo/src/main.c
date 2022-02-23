/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 10:10:21 by nvan-win      #+#    #+#                 */
/*   Updated: 2022/02/08 09:09:42 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_single_lock(t_data *data)
{
	if (pthread_mutex_init(&data->status_lock, NULL))
		return (write_error("pthread_mutex_init failed\n"));
	if (pthread_mutex_init(&data->full_lock, NULL))
	{
		if (pthread_mutex_destroy(&data->status_lock))
			return (write_error("pthread_mutex_destroy failed\n"));
		return (write_error("pthread_mutex_init failed\n"));
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = ft_calloc(data->num_philo, sizeof(pthread_mutex_t));
	if (data->forks == NULL)
		return (write_error("malloc error\n"));
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			if (destroy_forks(data, i))
				return (ERROR);
			return (write_error("pthread_mutex_init failed\n"));
		}
		i++;
	}
	if (init_single_lock(data))
	{
		if (destroy_forks(data, i))
			return (ERROR);
		return (ERROR);
	}
	return (0);
}

void	init_data(t_data *data, char **argv)
{
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data->num_times_to_eat = ft_atoi(argv[5]);
}

int	input_validation(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc != 5 && argc != 6)
		return (write_error("wrong number of arguments\n"));
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (write_error("incorrect argument type\n"));
			j++;
		}
		if (ft_atoi(argv[1]) == 0)
			return (write_error("invalid number of philosophers\n"));
		else if (ft_atoi(argv[i]) == 0)
			return (write_error("arguments must be greater than 0\n"));
		i++;
	}
	return (0);
}

/*
**	arg[0] = program name
**	arg[1] = num_philo
**	arg[2] = time_to_die
**	arg[3] = time_to_eat
**	arg[4] = time_to_sleep
**	arg[5] = [num_times_must_eat]
*/

int	main(int argc, char **argv)
{
	t_data	*data;
	int		res;

	if (input_validation(argc, argv))
		return (ERROR);
	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (write_error("malloc error\n"));
	res = 0;
	init_data(data, argv);
	if (init_mutexes(data))
		return (free_and_return(&data));
	res = start(data);
	if (destroy_forks(data, data->num_philo))
	{
		destroy_locks(data);
		free_and_return(&data);
	}
	if (destroy_locks(data))
		free_and_return(&data);
	free(data);
	return (res);
}
