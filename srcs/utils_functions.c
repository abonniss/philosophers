/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonniss <abonniss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:51:05 by abonniss          #+#    #+#             */
/*   Updated: 2022/03/14 18:46:00 by abonniss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_bzero(void *ptr, size_t size)
{
	memset(ptr, 0, sizeof(size));
}

void	sleeper(useconds_t time_to_wait, t_philo *philo)
{
	useconds_t	i;

	i = 0;
	while (i < time_to_wait)
	{
		usleep(10);
		if (philo->prog->finish == STOP)
			break ;
		++i;
	}
}

long long	convert_time(struct timeval now)
{
	long long	micro_second;

	micro_second = now.tv_sec * 1000;
	micro_second += now.tv_usec / 1000;
	return (micro_second);
}

void	message_manager(t_philo *philo, char *message)
{
	long long		current_time_from_start;
	struct timeval	now;

	pthread_mutex_lock(&philo->prog->write_mutex);
	gettimeofday(&now, NULL);
	current_time_from_start = convert_time(now)
		- convert_time(philo->prog->launched_time);
	if (philo->prog->finish != STOP)
		printf("%lld\t%zu\t%s\n", current_time_from_start, philo->philo_ref,
			message);
	pthread_mutex_unlock(&philo->prog->write_mutex);
}
