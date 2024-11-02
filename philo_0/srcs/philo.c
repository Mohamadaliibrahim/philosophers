/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamibr <mohamibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:21:08 by mohamibr          #+#    #+#             */
/*   Updated: 2024/10/31 13:14:54 by mohamibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	careing(t_philo *philo)
{
}

void	continue_it(int num_philo, char **av)
{
	t_philo	*philo;

	philo = init_philo(num_philo, av);
	if (!philo)
	{
		ft_printf("Failed to initialize philosopher\n");
		exit(EXIT_FAILURE);
	}
	careing(philo);
	lets_free(philo);
}

int	main(int ac, char **av)
{
	int	num_philo;

	if (ac == 5)
	{
		check_input(av);
		num_philo = ft_atoi(av[1]);
		if (num_philo <= 0)
		{
			ft_printf("Number of philosophers must be greater than 0\n");
			exit(EXIT_FAILURE);
		}
		continue_it(num_philo, av);
	}
	else
		ft_printf("wrong number of inputs\n");
	return (0);
}
