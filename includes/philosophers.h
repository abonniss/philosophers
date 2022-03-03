/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonniss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:19:13 by abonniss          #+#    #+#             */
/*   Updated: 2022/03/03 16:19:16 by abonniss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define NECESSARY_INPUT 5
# define SKIP_PROG_NAME 2
# define PHILO_ARG 1
# define TIME_TO_DIE_ARG 2
# define TIME_TO_EAT_ARG 3
# define TIME_TO_SLEEP_ARG 4
# define ALL_THREADS_CREATED 0

typedef struct  s_prog
{
    int nbr_philosophes;
    int time_to_sleep;
    int time_to_die;
    int time_to_eat;
}               t_prog;

bool	ft_isnegative(int nbr);
int	    ft_isdigit(int c);
bool	ft_isnumber(const char *str);
long	ft_atol(const char *str);


#endif