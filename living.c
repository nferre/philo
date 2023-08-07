/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:15:28 by nferre            #+#    #+#             */
/*   Updated: 2021/11/29 09:42:48 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	print_state(char c, t_list *philo)
{	
	char	*str;

	pthread_mutex_lock(&philo->rules->write);
	if (philo->rules->is_dead == 1)
	{	
		pthread_mutex_unlock(&philo->rules->write);
		return ;
	}
	pthread_mutex_unlock(&philo->rules->write);
	str = NULL;
	if (c == 's')
		str = "is sleeping";
	else if (c == 'e')
		str = "is eating";
	else if (c == 't')
		str = "is thinking";
	else if (c == 'f')
		str = "has taken a fork";
	else if (c == 'd')
		str = "died";
	printf("%d %d %s\n", get_current_time() - philo->rules->time,
		philo->id, str);
}

int	eat(t_list *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_state('f', philo);
	pthread_mutex_lock(&philo->current_fork);
	print_state('f', philo);
	print_state('e', philo);
	better_sleep(philo->rules->t_eat);
	pthread_mutex_lock(&philo->rules->write);
	philo->time_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->rules->write);
	pthread_mutex_lock(&philo->rules->write);
	philo->nb_time_eat++;
	if (philo->nb_time_eat == philo->rules->must_eat)
		philo->rules->everybody_ate++;
	pthread_mutex_unlock(&philo->rules->write);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->current_fork);
	return (0);
}

int	eat_2(t_list *philo)
{
	pthread_mutex_lock(&philo->current_fork);
	print_state('f', philo);
	pthread_mutex_lock(philo->right_fork);
	print_state('f', philo);
	print_state('e', philo);
	better_sleep(philo->rules->t_eat);
	pthread_mutex_lock(&philo->rules->write);
	philo->time_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->rules->write);
	pthread_mutex_lock(&philo->rules->write);
	philo->nb_time_eat++;
	if (philo->nb_time_eat == philo->rules->must_eat)
		philo->rules->everybody_ate++;
	pthread_mutex_unlock(&philo->rules->write);
	pthread_mutex_unlock(&philo->current_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	*live(void *arg)
{
	t_list		*philo;

	philo = (t_list *)arg;
	if (philo->id % 2 && philo->rules->nb_philo < 50)
		better_sleep(10);
	while (philo->rules->everybody_ate != philo->rules->nb_philo)
	{
		pthread_mutex_lock(&philo->rules->write);
		if (philo->rules->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->rules->write);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->write);
		if (philo->id % 2 && philo->rules->nb_philo >= 50)
			eat_2(philo);
		else
			eat(philo);
		print_state('s', philo);
		better_sleep(philo->rules->t_sleep);
		print_state('t', philo);
	}
	return (NULL);
}

void	*death_checker(void	**list)
{
	int		i;
	t_list	**philo;

	i = 0;
	philo = (t_list **)list;
	while (philo[i]->rules->is_dead != 1 && philo[i]->rules->everybody_ate
		!= philo[i]->rules->nb_philo)
	{
		while (philo[i]->rules->everybody_ate
			!= philo[i]->rules->nb_philo && philo[i]->rules->is_dead != 1)
			check_philo(philo[i]);
		if (philo[i]->rules->nb_philo == 1)
			return (NULL);
		if (philo[i]->rules->nb_philo == i)
			i = -1;
		i++;
	}
	return (NULL);
}
