/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamibr <mohamibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:18:56 by mohamibr          #+#    #+#             */
/*   Updated: 2024/10/31 13:06:21 by mohamibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../ft_printf/ft_printf.h"
# include <fcntl.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	struct s_philo	*next;
}					t_philo;

void				check_input(char **av);
int					ft_atoi(const char *str);
t_philo				*init_philo(int num_philosophers, char **av);
void		lets_free(t_philo *philo);

#endif
