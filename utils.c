/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nferre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 09:26:51 by nferre            #+#    #+#             */
/*   Updated: 2021/11/23 09:14:08 by nferre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	numb;

	if (!str)
		return (0);
	numb = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	else
		sign = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		numb = numb * 10 + (str[i++] - '0');
	return (numb * sign);
}

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

void	special_case(int *nb)
{
	write(1, "-2", 2);
	*nb = (*nb + 2000000000) * -1;
}

void	ft_putnbr(int nb)
{
	char	b;

	b = 0;
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		b = (nb % 10) + '0';
		write(1, &b, 1);
	}
	else if (nb == -2147483648)
	{
		special_case(&nb);
		ft_putnbr(nb);
	}
	else if (nb < 0)
	{
		write(1, "-", 1);
		nb = nb * -1;
		ft_putnbr(nb);
	}
	else
	{
		b = nb + '0';
		write(1, &b, 1);
	}
}

void	smart_sleep(long int time)
{
	long int	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < time)
		usleep(time / 10);
}
