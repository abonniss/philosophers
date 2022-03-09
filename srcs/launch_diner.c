#include "philosophers.h"

void picking_up_fork(t_philo *philo)
{
    pthread_mutex_lock(philo->lfork);
    message_manager(philo, TAKEN_FORK);
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
	if (philo->prog->nbr_philosophes % 2 != EVEN_NUMBER_OF_PHILO)
		usleep(philo->prog->time_to_eat * 1000);
    while (philo->prog->finish != STOP)
    {
        picking_up_fork(node);
        eating(node);
        sleeping(node);
        thinking(node);
    }
    return(NULL);
}

int join_threads(t_prog *prog)
{
    t_philo     *philo;
    size_t         i;

    i = 0;
    philo = prog->philo;
    while (i != prog->nbr_philosophes)
    {
        if (pthread_join(philo->thread, NULL) != 0)
            return (EXIT_FAILURE);
        philo = philo->next;
        ++i;
    }

    return (EXIT_SUCCESS);
}

int launch_diner(t_prog *prog)
{
    size_t         i;
    t_philo     *philo;
    pthread_t   thread;

    philo = prog->philo;
    i = 0;
    pthread_mutex_init(prog->write_mutex, NULL);
    pthread_mutex_init(prog->dead_mutex, NULL);
    gettimeofday(&prog->launched_time, NULL);
    while (i != prog->nbr_philosophes)
    {
        philo->last_time_eat = prog->launched_time;
        if (pthread_create(&philo->thread, NULL, &routine, philo) != 0)
            return (EXIT_FAILURE);
        if (pthread_create(&thread, NULL, &monitor_health, philo) != 0)
            return (EXIT_FAILURE);
        pthread_detach(thread);
        philo = philo->next;
        ++i;
        usleep(100);
    }
    if (prog->min_meal != 0)
    {
        pthread_mutex_init(prog->meal_mutex, NULL);
        if (pthread_create(&thread, NULL, &monitor_meals, prog) != 0)
            return (EXIT_FAILURE);
        pthread_detach(thread);
    }
    join_threads(prog);
    return (EXIT_SUCCESS);
}

// curent time - lastmeal >= time_to_die = DEADPHILO
// Si un philo meurt tout les philos s'arretent
