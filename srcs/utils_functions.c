/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonniss <abonniss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:51:05 by abonniss          #+#    #+#             */
/*   Updated: 2022/03/11 11:17:35 by abonniss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long convert_time(struct timeval now)
{
    long long		micro_second;

	micro_second = now.tv_sec * 1000;
	micro_second += now.tv_usec / 1000;
	return (micro_second);
}

void    message_manager(t_philo *philo, char *message)
{
    long long       current_time_from_start;
    struct timeval  now;

    pthread_mutex_lock(&philo->prog->write_mutex);
    gettimeofday(&now, NULL);
    current_time_from_start = convert_time(now) - convert_time(philo->prog->launched_time);
    if (philo->prog->finish != STOP)
        printf("%lld\t%zu\t%s\n", current_time_from_start, philo->philo_ref, message);
    pthread_mutex_unlock(&philo->prog->write_mutex);
}