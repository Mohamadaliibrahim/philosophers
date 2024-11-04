/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamibr <mohamibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:21:08 by mohamibr          #+#    #+#             */
/*   Updated: 2024/11/04 19:40:31 by mohamibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	accurate_sleep(long time_in_ms)
{
	long	start_time;
	long	current;

	start_time = current_time();
	while (1)
	{
		current = current_time();
		if ((current - start_time) >= time_in_ms)
			break ;
		usleep(500);
	}
}

void *monitor_philos(void *arg)
{
    t_data  *data = (t_data *)arg;
    t_philo *philo = data->philo;
    int     i;
    int     all_ate;

    while (1)
    {
        i = 0;
        all_ate = 1;
        while (i < data->num_philosophers)
        {
            pthread_mutex_lock(&philo[i].state_mutex);
            long time_since_last_meal = current_time() - philo[i].last_meal_time;

            if (time_since_last_meal > data->time_to_die)
            {
                pthread_mutex_lock(&data->log_mutex);
                ft_printf("%d %d died\n", (int)(current_time() - data->start_time), philo[i].id);
                pthread_mutex_unlock(&data->log_mutex);

                pthread_mutex_lock(&data->alive_mutex);
                data->all_alive = 0;
                pthread_mutex_unlock(&data->alive_mutex);

                pthread_mutex_unlock(&philo[i].state_mutex);
                return (NULL);
            }

            if (data->required_meals != -1 && philo[i].eat_count < data->required_meals)
                all_ate = 0;

            pthread_mutex_unlock(&philo[i].state_mutex);
            i++;
        }

        if (data->required_meals != -1 && all_ate)
        {
            pthread_mutex_lock(&data->log_mutex);
            ft_printf("All philosophers have eaten required meals\n");
            pthread_mutex_unlock(&data->log_mutex);

            pthread_mutex_lock(&data->alive_mutex);
            data->all_alive = 0;
            pthread_mutex_unlock(&data->alive_mutex);

            return (NULL);
        }
        usleep(100);
    }
    return (NULL);
}


void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_data  *data = philo->data;

    while (1)
    {
        pthread_mutex_lock(&data->alive_mutex);
        int all_alive = data->all_alive;
        pthread_mutex_unlock(&data->alive_mutex);

        if (!all_alive)
            return (NULL);

        think(philo);
        take_forks(philo);
        eat(philo);
        put_down_forks(philo);
        sleep_philo(philo);

        pthread_mutex_lock(&philo->state_mutex);
        int meals_eaten = philo->eat_count;
        pthread_mutex_unlock(&philo->state_mutex);

        if (data->required_meals != -1 && meals_eaten >= data->required_meals)
            return (NULL);
    }
    return (NULL);
}


void start_simulation(t_data *data, t_philo *philo)
{
    int         i;
    pthread_t   monitor_thread;

    data->start_time = current_time();  // Record start time before threads are created

    // Initialize last meal time for each philosopher before starting threads
    i = 0;
    while (i < data->num_philosophers)
    {
        philo[i].last_meal_time = data->start_time;
        i++;
    }

    // Create philosopher threads
    i = 0;
    while (i < data->num_philosophers)
    {
        if (pthread_create(&philo[i].thread, NULL, philosopher_routine, &philo[i]) != 0)
        {
            ft_printf("Error creating thread for philosopher %d\n", philo[i].id);
            exit(EXIT_FAILURE);
        }
        usleep(100);  // Small delay to stagger philosopher starts
        i++;
    }

    // Create monitor thread
    if (pthread_create(&monitor_thread, NULL, monitor_philos, (void *)data) != 0)
    {
        ft_printf("Error creating monitor thread\n");
        exit(EXIT_FAILURE);
    }

    // Wait for monitor thread to finish
    pthread_join(monitor_thread, NULL);

    // Do not join philosopher threads here
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
		lets_free(philo, &data);
		exit(EXIT_FAILURE);
	}
	data.philo = philo;
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
		ft_printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [required_meals]\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
