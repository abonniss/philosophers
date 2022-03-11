/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonniss <abonniss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:32:09 by abonniss          #+#    #+#             */
/*   Updated: 2022/03/11 11:12:35 by abonniss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int join_threads(t_prog *prog)
{
    t_philo     *philo;
    size_t         i;

    i = 0;
    philo = prog->philo;
    while (i != prog->nbr_philosophes)
    {
        pthread_join(philo->thread, NULL);
        pthread_mutex_destroy(philo->lfork);
        pthread_mutex_destroy(philo->rfork);
        philo = philo->next;
        ++i;
    }
    pthread_mutex_destroy(&prog->write_mutex);
    pthread_mutex_destroy(&prog->dead_mutex);
    if (prog->min_meal != 0)
        pthread_mutex_destroy(&prog->meal_mutex);
    return (EXIT_SUCCESS);
}

void launch_diner(t_prog *prog)
{
    size_t         i;
    t_philo     *philo;
    pthread_t   thread;

    philo = prog->philo;
    i = 0;
    pthread_mutex_init(&prog->write_mutex, NULL);
    pthread_mutex_init(&prog->dead_mutex, NULL);
    gettimeofday(&prog->launched_time, NULL);
    while (i != prog->nbr_philosophes)
    {
        philo->last_time_eat = prog->launched_time;
        pthread_create(&philo->thread, NULL, &routine, philo);
        pthread_create(&thread, NULL, &monitor_health, philo);
        pthread_detach(thread);
        philo = philo->next;
        ++i;
        usleep(200);
    }
    if (prog->min_meal != 0)
    {
        pthread_mutex_init(&prog->meal_mutex, NULL);
        pthread_create(&thread, NULL, &monitor_meals, prog);
        pthread_detach(thread);
    }
}