/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonniss <abonniss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:31:47 by abonniss          #+#    #+#             */
/*   Updated: 2022/03/11 11:16:16 by abonniss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void free_philo(t_philo *head)
{
    t_philo *current_node;

    current_node = head;
    while (head->next != NULL)
    {
        head = head->next;
        free(current_node);
        current_node = head;
    }
}

void free_fork(t_cyclelist *fork_head)
{
    t_cyclelist *current_node;
    t_cyclelist *head;

    head = fork_head;
    current_node = fork_head;
    while (fork_head->next != head)
    {
        fork_head = fork_head->next;
        free(current_node->fork);
        free(current_node);
        current_node = fork_head;
    }
    if (fork_head->next == head)
    {
        free(fork_head->fork);
        free(fork_head);
    }
}

void free_all(t_prog *prog)
{
    free_fork(prog->fork);
    free_philo(prog->philo);
}