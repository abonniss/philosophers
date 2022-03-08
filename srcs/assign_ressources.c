
#include "philosophers.h"

t_cyclelist *create_fork_node(void)
{
    t_cyclelist *fork_node;

    fork_node = malloc(sizeof(t_cyclelist));
    memset(fork_node, 0, sizeof(t_cyclelist));
    fork_node->fork = malloc(sizeof(pthread_mutex_t));
    if (fork_node == NULL || fork_node->fork == NULL)
        return (NULL);
    return (fork_node);
}


void add_fork_nodes(t_cyclelist **head)
{
    t_cyclelist *new_node;
    t_cyclelist *node;

    node        = *head;
    new_node    = create_fork_node();
    if (new_node != NULL)
    {
        if (*head != NULL)
        {
            while (node->next != *head)
                node = node->next;
            node->next = new_node;
        }
        else 
            *head = new_node;
        new_node->next = *head;
    }        
}

t_cyclelist *create_fork_list(size_t nbr_of_nodes)
{
    t_cyclelist *fork;
    size_t      i;

    i = 0;
    fork = NULL;
    while (i < nbr_of_nodes)
    {
        add_fork_nodes(&fork);
        ++i;
    }
    return (fork);
}

t_philo *create_philo_node(void)
{
    t_philo *philo_node;

    philo_node = malloc(sizeof(t_philo));
    if (philo_node == NULL)
        return (NULL);
    memset(philo_node, 0, sizeof(t_philo));
    return (philo_node);
}

t_philo *create_philo_list(size_t nbr_of_nodes, t_prog *prog)
{
    t_philo *head_philo;
    t_philo *philo;
    size_t i;

    philo = create_philo_node();
    head_philo = philo;
    i = 0;
    while (i < nbr_of_nodes)
    {
        philo->next = create_philo_node();
        philo->prog = prog;
        philo->philo_ref = i + 1;
        philo = philo->next;
        ++i;
    }
    return (head_philo);
}

void assign_ressources(t_prog *prog)
{
    t_cyclelist *fork;
    t_philo     *philo;
    int      i;

    fork = create_fork_list(prog->nbr_philosophes);
    philo = create_philo_list(prog->nbr_philosophes, prog);
    prog->philo = philo;
    i = 0;
    while (i < prog->nbr_philosophes)
    {
        pthread_mutex_init(fork->fork, NULL);
        philo->lfork = fork->fork;
        philo->rfork = fork->next->fork;
        fork = fork->next;
        philo = philo->next;
        ++i;
    }
}
