/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamibr <mohamibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:18:56 by mohamibr          #+#    #+#             */
/*   Updated: 2024/11/02 19:42:37 by mohamibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../ft_printf/ft_printf.h"
# include <fcntl.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				required_meals;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_mutex;
	int				all_alive;
	t_philo			*philo;
}					t_data;

void	check_input(char **av);
int		ft_atoi(const char *str);
t_philo	*init_philo(t_data *data);
void	lets_free(t_philo *philos, t_data *data);
void	*philosopher_routine(void *arg);
t_data	init_data(char **av, int num_philo);
void	sleep_philo(t_philo *philo);
void	put_down_forks(t_philo *philo);
void	eat(t_philo *philo);
void	take_forks(t_philo *philo);
void	think(t_philo *philo);
long	current_time(void);

#endif
