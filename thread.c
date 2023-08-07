/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:07:45 by nferre            #+#    #+#             */
/*   Updated: 2021/11/29 09:45:29 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	detach_all(t_rules *rules, t_list **philo)
{
	int	i;

	i = -1;
	while (++i != rules->nb_philo)
		pthread_detach(philo[i]->thread);
}

t_list	**run_threads(t_rules *rules)
{
	int			i;
	t_list		**philo;
	pthread_t	death;

	i = -1;
	philo = malloc(sizeof(t_list *) * (rules->nb_philo + 1));
	while (++i != rules->nb_philo)
		philo[i] = init(rules, i);
	i = -1;
	while (++i != rules->nb_philo)
	{
		philo[i]->first = philo[0];
		if (i != rules->nb_philo - 1)
			philo[i]->next = philo[i + 1];
		if (i == rules->nb_philo - 1)
			philo[i]->right_fork = &(philo[0])->current_fork;
		else
			philo[i]->right_fork = &(philo[i + 1])->current_fork;
		pthread_create(&(philo[i])->thread, NULL, (void *)live, philo[i]);
	}
	pthread_create(&death, NULL, (void *)death_checker, philo);
	pthread_join(death, NULL);
	detach_all(rules, philo);
	return (philo);
}
