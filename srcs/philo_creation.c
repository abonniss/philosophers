/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonniss <abonniss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:48:37 by abonniss          #+#    #+#             */
/*   Updated: 2022/03/10 18:35:11 by abonniss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo *create_philo_node(void)
{
    t_philo *philo_node;

    philo_node = malloc(sizeof(t_philo));
    if (philo_node == NULL)
        return (NULL);
    memset(philo_node, 0, sizeof(t_cyclelist));
    philo_node->lfork = malloc(sizeof(pthread_mutex_t));
    if (philo_node->lfork == NULL)
    {
        free(philo_node);
        return (NULL);
    }
    philo_node->rfork = malloc(sizeof(pthread_mutex_t));
    if (philo_node->rfork == NULL)
    {
        free(philo_node->lfork);
        free(philo_node);
        return(NULL);
    }
    philo_node->meals_eaten = 0;
    philo_node->next = NULL;
    return (philo_node);
}

t_philo *create_philo_list(size_t nbr_of_nodes, t_prog *prog)
{
    t_philo *new_node;
    t_philo *current_node;
    size_t i;

    i = 1;
    current_node = create_philo_node();
    if (current_node == NULL)
        return (NULL);
    prog->philo = current_node;
    current_node->philo_ref = i;
    current_node->prog = prog;
    while (i < nbr_of_nodes)
    {
        new_node = create_philo_node();
        if (new_node == NULL)
        {
            free_philo(prog->philo);
            return (NULL);
        }
        new_node->philo_ref = i + 1;
        new_node->prog = prog;
        current_node->next = new_node;
        current_node = new_node;
        ++i;
    }
    return (prog->philo);
}