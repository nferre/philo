/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:10:36 by nferre            #+#    #+#             */
/*   Updated: 2021/11/29 09:52:15 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	better_sleep(long int time)
{
	long int	starter_time;

	starter_time = get_current_time();
	while ((get_current_time() - starter_time) < time)
		usleep(time / 10);
}

static char	*create(int n, int *size)
{
	char	*str;

	*size = 0;
	if (n == 0)
		*size = 1;
	if (n < 0)
	{
		*size += 1;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		*size += 1;
	}
	str = malloc(sizeof(char) * *size + 1);
	if (!str)
		return (0);
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;
	long	num;

	num = (long)n;
	str = create(n, &size);
	if (!str)
		return (0);
	str[size] = 0;
	if (num == 0)
		str[0] = '0';
	if (num == 0)
		return (str);
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	size--;
	while (num)
	{
		str[size--] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}

void	check_philo(t_list *philo)
{
	if (philo->rules->nb_philo == 1)
		better_sleep(philo->rules->t_die);
	pthread_mutex_lock(&philo->rules->write);
	if (philo->rules->is_dead != 1 && (get_current_time())
		- philo->time_last_meal >= philo->rules->t_die
		&& philo->nb_time_eat != philo->rules->must_eat)
	{
		printf("%d %d died\n", get_current_time()
			- philo->rules->time, philo->id);
		philo->rules->is_dead = 1;
	}
	if (philo->rules->nb_philo == 1)
		return ;
	pthread_mutex_unlock(&philo->rules->write);
}
