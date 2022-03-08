#include "philosophers.h"

void pick_up_fork(t_philo *philo)
{
    pthread_mutex_lock(philo->lfork);
    printf("Philo[%zu] - has taken a fork\n", philo->philo_ref);
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
    int i;
    t_philo *head;
    t_philo *node;

    head = prog->philo;
    node = head;
    i = 0;
    gettimeofday(&prog->launched_time, NULL);
    while (i != prog->nbr_philosophes)
    {
        if (pthread_create(&node->thread, NULL, &routine, node) != 0)
            return (EXIT_FAILURE);
        node = node->next;
        ++i;
    }
    i = 0;
    node = head; 
    while (i != prog->nbr_philosophes)
    {
        if (pthread_join(node->thread, NULL) != 0)
            return (EXIT_FAILURE);
        node = node->next;
        ++i;
    }
    return (EXIT_SUCCESS);
    
}