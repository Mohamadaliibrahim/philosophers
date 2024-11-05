/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamibr <mohamibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:21:08 by mohamibr          #+#    #+#             */
/*   Updated: 2024/11/05 20:45:29 by mohamibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	start_simulation(t_data *data, t_philo *philo)
{
	int			i;
	pthread_t	monitor_thread;

	data->start_time = current_time();
	i = -1;
	while (++i < data->num_philosophers)
		philo[i].last_meal_time = data->start_time;
	i = -1;
	while (++i < data->num_philosophers)
	{
		if (pthread_create(&philo[i].thread, NULL, philosopher_routine,
				&philo[i]) != 0)
		{
			ft_printf("Error creating thread for philosopher %d\n",
				philo[i].id);
			exit(EXIT_FAILURE);
		}
		usleep(100);
	}
	if (pthread_create(&monitor_thread, NULL, monitor, (void *)data) != 0)
	{
		ft_printf("Error creating monitor thread\n");
		exit(EXIT_FAILURE);
	}
	pthread_join(monitor_thread, NULL);
}

void	join_thread_and_cleanup(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	lets_free(philo, data);
}

void	continue_it(int num_philo, char **av)
{
	t_philo	*philo;
	t_data	data;

	data = init_data(data, av, num_philo);
	philo = init_philo(&data);
	if (!philo)
	{
		ft_printf("Philosopher initialization failed\n");
		lets_free(philo, &data);
		exit(EXIT_FAILURE);
	}
	data.philo = philo;
	data.start_time = current_time();
	if (num_philo == 1)
	{
		log_action(&philo[0], "has taken a fork");
		accurate_sleep(data.time_to_die);
		log_action(&philo[0], "died");
		lets_free(philo, &data);
		exit(EXIT_SUCCESS);
	}
	start_simulation(&data, philo);
	join_thread_and_cleanup(&data, philo);
}

int	main(int ac, char **av)
{
	int	num_philo;

	if (ac == 6 || ac == 5)
	{
		check_input(av);
		num_philo = ft_atoi(av[1]);
		if (num_philo <= 0)
		{
			ft_printf("Number of philosophers must be greater than 0\n");
			exit(EXIT_FAILURE);
		}
		if (ac == 6 && ft_atoi(av[5]) <= 0)
		{
			ft_printf("Error: required_meals must be greater than 0.\n");
			exit(EXIT_FAILURE);
		}
		continue_it(num_philo, av);
	}
	else
	{
		ft_printf("Wrong number of inputs\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
//stop!