/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamibr <mohamibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:21:08 by mohamibr          #+#    #+#             */
/*   Updated: 2024/11/05 19:24:43 by mohamibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	destroy_mutex(int i, t_data *data, int x, int num_philo)
{
	if (x == 1)
	{
		while (i > 0)
		{
			i--;
			pthread_mutex_destroy(&data->forks[i]);
		}
		free(data->forks);
		exit(EXIT_FAILURE);
	}
	else
	{
		while (i < num_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		exit(EXIT_FAILURE);
	}
}

void	fill_data(t_data *data, char **av, int num_philo)
{
	data->num_philosophers = num_philo;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->required_meals = ft_atoi(av[5]);
	else
		data->required_meals = -1;
	data->all_alive = 1;
	data->forks = malloc(sizeof(pthread_mutex_t) * num_philo);
	if (!data->forks)
		exit(EXIT_FAILURE);
}

void	mutex_init(t_data *data, int num_philo, int i)
{
	if (pthread_mutex_init(&data->log_mutex, NULL) != 0)
	{
		ft_printf("log mutex initialization failed\n");
		destroy_mutex(i, data, 1, num_philo);
	}
	if (pthread_mutex_init(&data->alive_mutex, NULL) != 0)
	{
		ft_printf("alive mutex initialization failed\n");
		pthread_mutex_destroy(&data->log_mutex);
		i = 0;
		destroy_mutex(i, data, 0, num_philo);
	}
}

t_data	init_data(t_data data, char **av, int num_philo)
{
	int	i;

	fill_data(&data, av, num_philo);
	i = -1;
	while (++i < num_philo)
	{
		if (pthread_mutex_init(&data.forks[i], NULL) != 0)
		{
			ft_printf("Error initializing mutex for fork %d\n", i);
			destroy_mutex(i, &data, 1, num_philo);
		}
	}
	mutex_init(&data, num_philo, i);
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
		fill_philo(i, data, philos);
		if (pthread_mutex_init(&philos[i].state_mutex, NULL) != 0)
		{
			ft_printf("Error: Failed to initialize"
				"state_mutex for philosopher %d\n", philos[i].id);
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&philos[i].state_mutex);
			}
			free(philos);
			return (NULL);
		}
		i++;
	}
	return (philos);
}
