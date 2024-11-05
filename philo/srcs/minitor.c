/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamibr <mohamibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:49:03 by mohamibr          #+#    #+#             */
/*   Updated: 2024/11/05 19:27:23 by mohamibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	if_died(t_data *data, t_philo *philo, int i, long time_since_last_meal)
{
	if (time_since_last_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->log_mutex);
		ft_printf("%d %d died\n", (int)(current_time()
				- data->start_time), philo[i].id);
		pthread_mutex_unlock(&data->log_mutex);
		pthread_mutex_lock(&data->alive_mutex);
		data->all_alive = 0;
		pthread_mutex_unlock(&data->alive_mutex);
		pthread_mutex_unlock(&philo[i].state_mutex);
		return (1);
	}
	return (0);
}

int	if_they_all_eat(t_data *data, int all_ate)
{
	if (data->required_meals != -1 && all_ate)
	{
		pthread_mutex_lock(&data->log_mutex);
		ft_printf("All philosophers have eaten required meals\n");
		pthread_mutex_unlock(&data->log_mutex);
		pthread_mutex_lock(&data->alive_mutex);
		data->all_alive = 0;
		pthread_mutex_unlock(&data->alive_mutex);
		return (1);
	}
	return (0);
}

int	the_loop(t_data *data, t_philo *philo)
{
	int		i;
	int		all_ate;
	long	time_since_last_meal;

	i = -1;
	all_ate = 1;
	while (++i < data->num_philosophers)
	{
		pthread_mutex_lock(&philo[i].state_mutex);
		time_since_last_meal = current_time() - philo[i].last_meal_time;
		if (if_died(data, philo, i, time_since_last_meal))
			return (1);
		if (data->required_meals != -1
			&& philo[i].eat_count < data->required_meals)
			all_ate = 0;
		pthread_mutex_unlock(&philo[i].state_mutex);
	}
	if (if_they_all_eat(data, all_ate))
		return (1);
	usleep(100);
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	data = (t_data *)arg;
	philo = data->philo;
	while (1)
	{
		if (the_loop(data, philo))
			return (NULL);
	}
	return (NULL);
}
