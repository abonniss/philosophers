#include "philosophers.h"

void pick_up_fork(t_philo *philo)
{
    pthread_mutex_lock(philo->lfork);
    message_manager();
    pthread_mutex_lock(philo->rfork);
    printf("Philo[%zu] - has taken a fork\n", philo->philo_ref);
}

void eat(t_philo *philo)
{
    printf("Philo eating (%zu)\n", philo->philo_ref);
    pthread_mutex_unlock(philo->lfork);
    pthread_mutex_unlock(philo->rfork);
    printf("Philo finish eating (%zu)\n", philo->philo_ref);
}


void *routine(void *node)
{
    pick_up_fork(node);
    eat(node);
    return (NULL);
}

int launch_diner(t_prog *prog)
{
    int         i;
    t_philo     *head;
    t_philo     *philo;
    pthread_t   thread;

    head = prog->philo;
    philo = head;
    i = 0;
    gettimeofday(&prog->launched_time, NULL);
    while (i != prog->nbr_philosophes)
    {
        philo->last_time_eat = prog->launch_time;
        if (pthread_create(&philo->thread, NULL, &routine, philo) != 0)
            return (EXIT_FAILURE);
        if (pthread_create(&thread, NULL, &monitor_health, philo) != 0)
            return (EXIT_FAILURE);
        pthread_detach(thread);
        philo = philo->next;
        ++i;
    }
    i = 0;
    philo = head; 
    while (i != prog->nbr_philosophes)
    {
        if (pthread_join(philo->thread, NULL) != 0)
            return (EXIT_FAILURE);
        philo = philo->next;
        ++i;
    }
    return (EXIT_SUCCESS);
    
}

// curent time - lastmeal >= time_to_die = DEADPHILO
// Si un philo meurt tout les philos s'arretent
