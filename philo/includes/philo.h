/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 10:40:33 by nvan-win      #+#    #+#                 */
/*   Updated: 2022/02/11 11:44:14 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

# define ERROR -1
# define STOP_SIMULATION 2
# define EATING 5

/* Shared data between philosophers */

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	status_lock;
	pthread_mutex_t	full_lock;
	unsigned long	start_time;
	int				philos_full;
	int				philo_died;
	int				error;
}					t_data;

typedef struct s_philo
{
	pthread_t		id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				num;
	unsigned long	time_start_eating;
	int				num_x_eaten;
	t_data			*data;
}					t_philo;

/* cleanup.c */
int				destroy_forks(t_data *data, int i);
int				destroy_locks(t_data *data);
int				write_error(char *str);
int				free_and_return(t_data **data);
int				destroy_philos(t_philo *philo, int num_philos);

/* monitor.c */
int				monitor(t_philo *philo);

/* philo_utils.c */
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
void			*ft_calloc(size_t count, size_t size);
size_t			ft_strlen(const char *s);

/* start.c */
int				start(t_data *data);
int				status_lock(t_philo *philo, char *status, int activity);

/* simulation.c */
void			*simulation(void *philo_thread);

/*time.c */
unsigned long	get_time(void);
int				timer(unsigned long ms);

#endif