/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonniss <abonniss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:51:50 by abonniss          #+#    #+#             */
/*   Updated: 2022/03/14 15:35:57 by abonniss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	picking_up_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	message_manager(philo, TAKEN_FORK);
	if (philo->prog->nbr_philosophes < TWO_PHILOSOPHES)
	{
		pthread_mutex_unlock(philo->rfork);
		usleep(philo->prog->time_to_die);
	}
	pthread_mutex_lock(philo->lfork);
	message_manager(philo, TAKEN_FORK);
}

static void	eating(t_philo *philo)
{
	if (philo->prog->finish != STOP)
		message_manager(philo, EATING);
	gettimeofday(&philo->last_time_eat, NULL);
	philo->meals_eaten += ADDING_ONE_MEAL;
	if (philo->meals_eaten == philo->prog->min_meal)
		philo->prog->nbr_philo_finished_all_meals += ONE_PHILO_EAT_EVERY_MEAL;
	usleep(philo->prog->time_to_eat);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

static void	sleeping(t_philo *philo)
{
	message_manager(philo, SLEEPING);
	usleep(philo->prog->time_to_sleep);
}

static void	thinking(t_philo *philo)
{
	message_manager(philo, THINKING);
}

void	*routine(void *node)
{
	t_philo	*philo;

	philo = node;
	while (philo->prog->finish != STOP)
	{
		picking_up_fork(node);
		eating(node);
		sleeping(node);
		thinking(node);
	}
	return (NULL);
}
