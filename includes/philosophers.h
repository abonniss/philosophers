/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonniss <abonniss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:19:13 by abonniss          #+#    #+#             */
/*   Updated: 2022/03/11 11:11:31 by abonniss         ###   ########.fr       */
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

# define EXIT_SUCCESS           0
# define EXIT_FAILURE           1

# define MIN_INPUT              5
# define MAX_INPUT              6
# define SKIP_PROG_NAME         2

# define MALLOC_ERROR           20

# define PHILO_ARG              1
# define TIME_TO_DIE_ARG        2
# define TIME_TO_EAT_ARG        3
# define TIME_TO_SLEEP_ARG      4
# define MUST_EAT_INPUT         5

# define ALL_THREADS_CREATED    0

# define TAKEN_FORK             "has taken a fork"
# define EATING                 "is eating"
# define SLEEPING               "is sleeping"
# define THINKING               "is thinking"
# define DIED                   "died"

# define STOP                   1
# define EVEN_NUMBER_OF_PHILO   0

typedef struct  s_prog
{
    size_t              nbr_philosophes;
    int                 time_to_sleep;
    int                 time_to_die;
    int                 time_to_eat;
    struct s_philo      *philo;
    pthread_mutex_t     write_mutex;
    pthread_mutex_t     dead_mutex;
    pthread_mutex_t     meal_mutex;
    int                 finish;
    size_t              min_meal;
    size_t              nbr_philo_finished_all_meals;
    struct timeval	    launched_time;
    struct s_cyclelist  *fork;

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


bool	    ft_isnegative(int nbr);
int	        ft_isdigit(int c);
bool	    ft_isnumber(const char *str);
long	    ft_atol(const char *str);

int         create_ressources(t_prog *prog);
t_cyclelist *create_fork_list(size_t nbr_of_nodes);
t_philo     *create_philo_node(void);
t_philo     *create_philo_list(size_t nbr_of_nodes, t_prog *prog);


void        free_philo(t_philo *head);
void        free_fork(t_cyclelist *fork_head);
void        free_prog_mutex(t_prog *prog);
void        free_all(t_prog *prog);

void        launch_diner(t_prog *prog);
void        *routine(void *node);
int         join_threads(t_prog *prog);
void        *monitor_health(void *ptr);
void        *monitor_meals(void *ptr);

void        message_manager(t_philo *philo, char *message);
long long   convert_time(struct timeval	now);

#endif