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
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define MIN_INPUT 5
# define SKIP_PROG_NAME 2
# define PHILO_ARG 1
# define TIME_TO_DIE_ARG 2
# define TIME_TO_EAT_ARG 3
# define TIME_TO_SLEEP_ARG 4
# define MUST_EAT_INPUT 5
# define ALL_THREADS_CREATED 0

typedef struct  s_prog
{
    int             nbr_philosophes;
    int             time_to_sleep;
    int             time_to_die;
    int             time_to_eat;
    struct s_philo  *philo;
    int             nbr_meal;
    struct timeval	launched_time;
}               t_prog;

typedef struct s_cyclelist
{
    int                 data;
    pthread_mutex_t     *fork;
    struct s_cyclelist  *next;
}               t_cyclelist;

typedef struct s_philo
{
    pthread_t       thread;
    size_t          philo_ref;
    size_t          meals_eaten;
    pthread_mutex_t *lfork;
    pthread_mutex_t *rfork;
    struct timeval	last_time_eat;
    void            *next;
    t_prog          *prog;
}               t_philo;


bool	ft_isnegative(int nbr);
int	    ft_isdigit(int c);
bool	ft_isnumber(const char *str);
long	ft_atol(const char *str);
void    assign_ressources(t_prog *prog);
int    launch_diner(t_prog *prog);



#endif