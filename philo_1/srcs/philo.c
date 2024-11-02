/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamibr <mohamibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:21:08 by mohamibr          #+#    #+#             */
/*   Updated: 2024/11/02 20:02:12 by mohamibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 100) + (tv.tv_usec / 1000));
}

void	*monitor_philos(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int		i;
	int		all_ate;

	data = (t_data *)arg;
	philo = data->philo;
	while (data->all_alive)
	{
		i = 0;
		all_ate = 1;
		while (i < data->num_philosophers)
		{
			if (current_time() - philo[i].last_meal_time > data->time_to_die)
			{
				pthread_mutex_lock(&data->log_mutex);
				ft_printf("philospher %d died\n", philo[i].id);
				pthread_mutex_unlock(&data->log_mutex);
				data->all_alive = 0;
				break ;
			}
			if (data->required_meals != -1 && philo[i].eat_count < data->required_meals)
				all_ate = 0;
			i++;
		}
		if (data->required_meals != -1 && all_ate)
		{
			pthread_mutex_lock(&data->log_mutex);
			ft_printf("All philosophers have eaten required meals\n");
			pthread_mutex_unlock(&data->log_mutex);
			data->all_alive = 0;
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (data->all_alive)
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philo(philo);
	}
	return (NULL);
}

void	start_simulation(t_data *data, t_philo *philo)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_create(&philo[i].thread, NULL, philosopher_routine, &philo[i]) != 0)
		{
			ft_printf("Error creating thread\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, (void *(*)(void *))monitor_philos, (void *)data) != 0)
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

	data = init_data(av, num_philo);
	philo = init_philo(&data);
	if (!philo)
	{
		ft_printf("Philosopher initialization failed\n");
        exit(EXIT_FAILURE);
	}
	data.philo = philo;
	data.start_time = current_time();
	start_simulation(&data, philo);
	join_thread_and_cleanup(&data, philo);
}

int	main(int ac, char **av)
{
	int	num_philo;

	if (ac == 6)
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
