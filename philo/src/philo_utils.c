/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 10:39:30 by nvan-win      #+#    #+#                 */
/*   Updated: 2022/02/11 10:55:16 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	memset(ptr, '\0', count * size);
	return (ptr);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int	n;
	int	flag;
	int	i;

	n = 0;
	flag = 1;
	i = 0;
	if (str[i] == '-')
	{
		flag = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	return (n * flag);
}
