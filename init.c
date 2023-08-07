/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:36:30 by nferre            #+#    #+#             */
/*   Updated: 2021/11/29 09:49:44 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

t_list	*init(t_rules *rules, int i)
{
	t_list	*philo;

	philo = malloc(sizeof(t_list));
	philo->rules = rules;
	philo->id = i + 1;
	philo->time_last_meal = get_current_time();
	philo->next = NULL;
	philo->first = NULL;
	philo->nb_time_eat = 0;
	pthread_mutex_init(&philo->mutex, NULL);
	pthread_mutex_init(&philo->current_fork, NULL);
	return (philo);
}

t_rules	*get_args(int argc, char **argv)
{
	t_rules	*arg;

	arg = malloc(sizeof(t_rules));
	pthread_mutex_init(&arg->write, NULL);
	arg->nb_philo = ft_atoi(argv[1]);
	arg->t_die = ft_atoi(argv[2]);
	arg->t_eat = ft_atoi(argv[3]);
	arg->t_sleep = ft_atoi(argv[4]);
	arg->time = get_current_time();
	arg->must_eat = -1;
	arg->is_dead = 0;
	arg->everybody_ate = 0;
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) <= 0)
			exit (0);
		arg->must_eat = ft_atoi(argv[5]);
	}
	arg->is_dead = 0;
	return (arg);
}
