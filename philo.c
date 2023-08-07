/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:32:41 by nferre            #+#    #+#             */
/*   Updated: 2021/11/29 09:48:27 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	verif_params(int argc, char **argv)
{
	int	i;
	int	j;

	j = 0;
	if (argc != 5 && argc != 6)
		return (-1);
	while (argv[++j])
	{
		i = -1;
		while (argv[j][++i])
			if (argv[j][i] < '0' || argv[j][i] > '9')
				return (-1);
	}
	return (0);
}

int	verif_rules(t_rules *rules, int argc, char **argv)
{
	int		i;
	int		j;
	char	*max_int;

	max_int = "2147483647";
	j = 0;
	if (rules->nb_philo <= 0)
		return (-1);
	while (++j != argc)
	{
		i = 0;
		while (argv[j][i] == max_int[i] && argv[j][i])
		{
			if (i == 9 && argv[j][i] >= 8 && argv[j][i] <= 9)
				return (-1);
			i++;
		}
		if (argv[j][i] >= '0' && argv[j][i] <= '9' && i >= 9)
			return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	*rules;

	if (verif_params(argc, argv) == -1)
		return (0);
	rules = get_args(argc, argv);
	if (verif_rules(rules, argc, argv) == -1)
		return (0);
	run_threads(rules);
	return (0);
}
