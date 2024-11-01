/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamibr <mohamibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:49:03 by mohamibr          #+#    #+#             */
/*   Updated: 2024/10/31 13:06:07 by mohamibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_a_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	check_input(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (is_a_number(av[i]) == 0)
		{
			ft_printf("input is not numbers\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	lets_free(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (philo)
	{
		tmp = philo;
		philo = philo->next;
		free(tmp);
	}
}
