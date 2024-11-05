/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamibr <mohamibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:18:56 by mohamibr          #+#    #+#             */
/*   Updated: 2024/11/05 20:56:30 by mohamibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../ft_printf/inc/ft_printf.h"
# include <fcntl.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
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
	pthread_mutex_t	state_mutex;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;
// state_mutex: Mutex to protect access to eat_count and last_meal_time.
// log_mutex: Mutex to protect console output.
// alive_mutex: Mutex to protect access to the all_alive flag.
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
	pthread_mutex_t	alive_mutex;
	int				all_alive;
	t_philo			*philo;
}					t_data;

void	check_input(char **av);
int		ft_atoi(const char *str);
t_philo	*init_philo(t_data *data);
void	lets_free(t_philo *philos, t_data *data);
void	*philosopher_routine(void *arg);
t_data	init_data(t_data data, char **av, int num_philo);
void	sleep_philo(t_philo *philo);
void	put_down_forks(t_philo *philo);
void	eat(t_philo *philo);
void	take_forks(t_philo *philo);
void	think(t_philo *philo);
long	current_time(void);
void	*monitor(void *arg);
void	fill_philo(int i, t_data *data, t_philo *philos);
void	start_simulation(t_data *data, t_philo *philo);
void	join_thread_and_cleanup(t_data *data, t_philo *philo);
void	continue_it(int num_philo, char **av);
void	log_action(t_philo *philo, char *action);
void	accurate_sleep(long time_in_ms);
void	log_action(t_philo *philo, char *action);
#endif
