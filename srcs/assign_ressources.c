/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_ressources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonniss <abonniss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:51:34 by abonniss          #+#    #+#             */
/*   Updated: 2022/03/11 14:53:17 by abonniss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	assign_fork_to_philo(t_prog *prog, t_cyclelist *list_fork)
{
	t_philo	*philo;
	size_t	i;

	philo = prog->philo;
	i = 0;
	while (i < prog->nbr_philosophes)
	{
		pthread_mutex_init(&list_fork->fork, NULL);
		philo->rfork = &list_fork->fork;
		philo->lfork = &list_fork->next->fork;
		list_fork = list_fork->next;
		philo = philo->next;
		++i;
	}
}

int	create_ressources(t_prog *prog)
{
	t_cyclelist	*list_fork;
	t_philo		*philo;

	list_fork = create_fork_list(prog->nbr_philosophes);
	if (list_fork == NULL)
		return (MALLOC_ERROR);
	philo = create_philo_list(prog->nbr_philosophes, prog);
	if (philo == NULL)
	{
		free_fork(list_fork);
		return (MALLOC_ERROR);
	}
	prog->philo = philo;
	prog->fork = list_fork;
	assign_fork_to_philo(prog, list_fork);
	return (EXIT_SUCCESS);
}
