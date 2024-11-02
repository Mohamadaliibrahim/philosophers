/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamibr <mohamibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:21:08 by mohamibr          #+#    #+#             */
/*   Updated: 2024/11/02 19:57:20 by mohamibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_data	init_data(char **av, int num_philo)
{
	t_data	data;
	int		i;

	data.num_philosophers = num_philo;
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	data.philo = NULL;
	if (av[5])
		data.required_meals = ft_atoi (av[5]);
	else
		data.required_meals = -1;
	data.all_alive = 1;
	data.forks = malloc(sizeof(pthread_mutex_t) * num_philo);
	if (!data.forks)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < num_philo)
	{
		if (pthread_mutex_init(&data.forks[i], NULL) != 0)
		{
			ft_printf("mutex initialization failed\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (pthread_mutex_init(&data.log_mutex, NULL) != 0)
	{
		ft_printf("log mutex initialization failed\n");
		exit(EXIT_FAILURE);
	}
	return (data);
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->num_philosophers);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->num_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].eat_count = 0;
		philos[i].last_meal_time = data->start_time;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
		philos[i].data = data;
		i++;
	}
	return (philos);
}
