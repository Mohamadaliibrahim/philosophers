/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamibr <mohamibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:21:08 by mohamibr          #+#    #+#             */
/*   Updated: 2024/10/31 11:53:12 by mohamibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	*init_philo(int num_philosophers, char **av)
{
	t_philo	*head;
	t_philo	*current;
	t_philo	*new_node;
	int		i;

	head = NULL;
	i = 1;
	while (i <= num_philosophers)
	{
		new_node = malloc(sizeof(t_philo));
		if (!new_node)
			return (NULL);
		new_node->id = i;
		new_node->time_to_die = ft_atoi(av[2]);
		new_node->time_to_eat = ft_atoi(av[3]);
		new_node->time_to_sleep = ft_atoi(av[4]);
		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}