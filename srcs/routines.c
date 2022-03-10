/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonniss <abonniss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:51:50 by abonniss          #+#    #+#             */
/*   Updated: 2022/03/10 18:35:23 by abonniss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void picking_up_fork(t_philo *philo)
{
    pthread_mutex_lock(philo->lfork);
    message_manager(philo, TAKEN_FORK);
    if (philo->prog->nbr_philosophes < 2)
    {
        pthread_mutex_unlock(philo->lfork);
        usleep(philo->prog->time_to_die * 1000);
    }
    pthread_mutex_lock(philo->rfork);
    message_manager(philo, TAKEN_FORK);
}

void eating(t_philo *philo)
{
    gettimeofday(&philo->last_time_eat, NULL);
    philo->meals_eaten +=1;
    if (philo->meals_eaten == philo->prog->min_meal)
        philo->prog->nbr_philo_finished_all_meals += 1;
    if (philo->prog->finish != STOP)
        message_manager(philo, EATING);
    usleep(philo->prog->time_to_eat * 1000);
    pthread_mutex_unlock(philo->lfork);
    pthread_mutex_unlock(philo->rfork);
}

void sleeping(t_philo *philo)
{
    message_manager(philo, SLEEPING);
    usleep(philo->prog->time_to_sleep * 1000);
}

void thinking(t_philo *philo)
{
    message_manager(philo, THINKING);
}

void *routine(void *node)
{
    t_philo *philo;

    philo = node;
    while (philo->prog->finish != STOP)
    {
        picking_up_fork(node);
        eating(node);
        sleeping(node);
        thinking(node);
    }
    return(NULL);
}

	// if (philo->prog->nbr_philosophes % 2 != EVEN_NUMBER_OF_PHILO)
	// 	usleep(philo->prog->time_to_eat * 1000);