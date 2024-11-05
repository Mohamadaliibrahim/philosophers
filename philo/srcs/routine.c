/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamibr <mohamibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:21:08 by mohamibr          #+#    #+#             */
/*   Updated: 2024/11/05 20:44:48 by mohamibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	think(t_philo *philo)
{
	log_action(philo, "is thinking");
	accurate_sleep(10);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	log_action(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	log_action(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	log_action(philo, "is eating");
	pthread_mutex_lock(&philo->state_mutex);
	philo->last_meal_time = current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->state_mutex);
	accurate_sleep(philo->data->time_to_eat);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	log_action(philo, "has put down the forks");
}

void	sleep_philo(t_philo *philo)
{
	log_action(philo, "is sleeping");
	accurate_sleep(philo->data->time_to_sleep);
}
