/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonniss <abonniss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:19:13 by abonniss          #+#    #+#             */
/*   Updated: 2022/03/15 17:10:30 by abonniss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define EXIT_SUCCESS				0
# define EXIT_FAILURE				1

# define MIN_INPUT					5
# define MAX_INPUT					6
# define SKIP_PROG_NAME				1

# define MALLOC_ERROR				20

# define PHILO_ARG					1
# define TIME_TO_DIE_ARG			2
# define TIME_TO_EAT_ARG			3
# define TIME_TO_SLEEP_ARG			4
# define MUST_EAT_INPUT				5

# define ALL_THREADS_CREATED		0

# define TAKEN_FORK					"has taken a fork"
# define EATING						"is eating"
# define SLEEPING					"is sleeping"
# define THINKING					"is thinking"
# define DIED						"died"

# define STOP						1
# define EVEN_NUMBER_OF_PHILO		0
# define STARTING_AT_ONE			1
# define ADDING_ONE_MEAL			1
# define ONE_PHILO_EAT_EVERY_MEAL	1
# define TWO_PHILOSOPHES			2
# define MS_DELAY_OF_200			200

typedef struct s_prog
{
	struct s_philo		*philo;
	struct s_cyclelist	*fork;
	size_t				nbr_philosophes;
	size_t				min_meal;
	size_t				nbr_philo_finished_all_meals;
	useconds_t			time_to_sleep;
	useconds_t			time_to_die;
	useconds_t			time_to_eat;
	int					finish;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		dead_mutex;
	struct timeval		launched_time;
}						t_prog;

typedef struct s_cyclelist
{
	struct s_cyclelist	*next;
	pthread_mutex_t		fork;
	char				pad[4];
}						t_cyclelist;

typedef struct s_philo
{
	pthread_t		thread;
	size_t			philo_ref;
	size_t			meals_eaten;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	struct timeval	last_time_eat;
	void			*next;
	t_prog			*prog;
}					t_philo;

/*#######################LIB_FUNCTIONS########################*/
bool		ft_isnegative(int nbr);
bool		ft_isnumber(const char *str);
long		ft_atol(const char *str);
void		ft_bzero(void *ptr, size_t size);

/*#######################CREATE_RESSOURCES####################*/
int			create_ressources(t_prog *prog);
t_cyclelist	*create_fork_list(size_t nbr_of_nodes);
t_philo		*create_philo_list(size_t nbr_of_nodes, t_prog *prog);

/*#######################FREE_RESSOURCES#######################*/
void		free_philo(t_philo *head);
void		free_fork(t_cyclelist *fork_head);
void		free_all(t_prog *prog);

/*#######################THREADS###############################*/
void		launch_diner(t_prog *prog);
void		*routine(void *node);
int			join_threads(t_prog *prog);
void		*monitor_health(void *ptr);
void		*monitor_meals(void *ptr);

/*#######################UTILS_FUNCTIONS#######################*/
void		message_manager(t_philo *philo, char *message);
long long	convert_time(struct timeval now);
void		sleeper(useconds_t time_to_wait, t_prog *prog);

#endif
