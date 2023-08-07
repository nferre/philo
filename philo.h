/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:09:31 by nferre            #+#    #+#             */
/*   Updated: 2021/11/29 09:46:48 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_rules
{	
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				everybody_ate;
	int				time;
	int				is_dead;
	pthread_mutex_t	write;
}	t_rules;

typedef struct s_list
{
	t_rules			*rules;
	int				id;
	int				time_last_meal;
	int				nb_time_eat;
	pthread_mutex_t	current_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	mutex;
	pthread_t		thread;
	struct s_list	*next;
	struct s_list	*first;
}	t_list;

void	check_philo(t_list *philo);
void	*death_checker(void **list);
void	death(t_list *list);
void	*live(void *arg);
int		eat(t_list *philo);
void	better_sleep(long int time);
t_list	*init(t_rules *rules, int i);
void	smart_sleep(long int time);
void	print_state(char c, t_list *list);
int		ft_atoi(const char *str);
void	ft_putstr(char *str);
int		get_current_time(void);
char	*ft_itoa(int n);
void	ft_putnbr(int nb);
t_list	**run_threads(t_rules *rules);
t_rules	*get_args(int argc, char **argv);

#endif
