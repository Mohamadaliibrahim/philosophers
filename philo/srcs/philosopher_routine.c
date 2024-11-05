/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamibr <mohamibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:21:08 by mohamibr          #+#    #+#             */
/*   Updated: 2024/11/05 20:45:10 by mohamibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

void	careing(t_philo *philo)
{
	think(philo);
	take_forks(philo);
	eat(philo);
	put_down_forks(philo);
	sleep_philo(philo);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		all_alive;
	int		meals_eaten;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&data->alive_mutex);
		all_alive = data->all_alive;
		pthread_mutex_unlock(&data->alive_mutex);
		if (!all_alive)
			return (NULL);
		careing(philo);
		pthread_mutex_lock(&philo->state_mutex);
		meals_eaten = philo->eat_count;
		pthread_mutex_unlock(&philo->state_mutex);
		if (data->required_meals != -1 && meals_eaten >= data->required_meals)
			return (NULL);
	}
	return (NULL);
}
