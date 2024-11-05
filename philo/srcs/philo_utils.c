/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamibr <mohamibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:49:03 by mohamibr          #+#    #+#             */
/*   Updated: 2024/11/05 19:25:42 by mohamibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// Checks if a string consists solely of digits
int	is_a_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

// Validates all input arguments
void	check_input(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (is_a_number(av[i]) == 0)
		{
			ft_printf("Error: All inputs must be numbers.\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

// Frees allocated resources and destroys mutexes
void	lets_free(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&philos[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->log_mutex);
	pthread_mutex_destroy(&data->alive_mutex);
	free(data->forks);
	free(philos);
}

void	fill_philo(int i, t_data *data, t_philo *philos)
{
	philos[i].id = i + 1;
	philos[i].eat_count = 0;
	philos[i].left_fork = &data->forks[i];
	philos[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
	philos[i].data = data;
}

void	log_action(t_philo *philo, char *action)
{
	int	all_alive;

	pthread_mutex_lock(&philo->data->alive_mutex);
	all_alive = philo->data->all_alive;
	pthread_mutex_unlock(&philo->data->alive_mutex);
	pthread_mutex_lock(&philo->data->log_mutex);
	if (all_alive)
		ft_printf("%d %d %s\n", (int)(current_time() - philo->data->start_time),
			philo->id, action);
	pthread_mutex_unlock(&philo->data->log_mutex);
}
//stop!