/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonniss <abonniss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:50:07 by abonniss          #+#    #+#             */
/*   Updated: 2022/03/14 15:04:09 by abonniss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_meals(void *ptr)
{
	t_prog	*prog;

	prog = ptr;
	while (prog->finish != STOP)
	{
		pthread_mutex_lock(&prog->dead_mutex);
		if (prog->nbr_philo_finished_all_meals >= prog->nbr_philosophes)
			prog->finish = STOP;
		pthread_mutex_unlock(&prog->dead_mutex);
	}
	return (NULL);
}

void	*monitor_health(void *ptr)
{
	t_philo			*philo;
	long long		time_limit;
	struct timeval	now;

	philo = ptr;
	while (philo->prog->finish != STOP)
	{
		pthread_mutex_lock(&philo->prog->dead_mutex);
		gettimeofday(&now, NULL);
		time_limit = convert_time(now) - convert_time(philo->last_time_eat);
		if (time_limit >= philo->prog->time_to_die
			&& philo->prog->finish != STOP)
		{
			gettimeofday(&now, NULL);
			printf("%lld\t%zu\t%s\n", (convert_time(now)
					- convert_time(philo->prog->launched_time)),
				philo->philo_ref, DIED);
			philo->prog->finish = STOP;
		}
		pthread_mutex_unlock(&philo->prog->dead_mutex);
	}
	return (NULL);
}
