/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonniss <abonniss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:31:47 by abonniss          #+#    #+#             */
/*   Updated: 2022/03/11 14:39:28 by abonniss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philo(t_philo *head)
{
	if (head != NULL)
	{
		free_philo(head->next);
		free(head);
	}
}

void	free_fork(t_cyclelist *fork_head)
{
	t_cyclelist	*head;
	t_cyclelist	*current_node;

	head = fork_head;
	current_node = fork_head;
	while (fork_head->next != head)
	{
		free(current_node);
		current_node = fork_head->next;
		fork_head = fork_head->next;
	}
	free(current_node);
}

void	free_all(t_prog *prog)
{
	free_fork(prog->fork);
	free_philo(prog->philo);
}
