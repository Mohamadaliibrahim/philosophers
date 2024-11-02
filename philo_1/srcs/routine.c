/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamibr <mohamibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:21:08 by mohamibr          #+#    #+#             */
/*   Updated: 2024/11/02 19:10:58 by mohamibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->log_mutex);
	ft_printf("philosopher %d is thinking\n", philo->id);
	pthread_mutex_unlock(&philo->data->log_mutex);
	usleep(1000);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->data->log_mutex);
	ft_printf("philosopher %d has taken the left fork\n", philo->id);
	pthread_mutex_unlock(&philo->data->log_mutex);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->data->log_mutex);
	ft_printf("philosopher %d has taken the right fork\n", philo->id);
	pthread_mutex_unlock(&philo->data->log_mutex);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->log_mutex);
	ft_printf("philosopher %d is eating\n", philo->id);
	pthread_mutex_unlock(&philo->data->log_mutex);
	philo->last_meal_time = current_time();
	philo->eat_count++;
	usleep(philo->data->time_to_eat * 1000);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->data->log_mutex);
	ft_printf("philosopher %d has put down the forks\n", philo->id);
	pthread_mutex_unlock(&philo->data->log_mutex);
}

void	sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->log_mutex);
	ft_printf("philosopher %d is sleeping\n", philo->id);
	pthread_mutex_unlock(&philo->data->log_mutex);
	usleep(philo->data->time_to_sleep * 1000);
}
//stop!!