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
	static t_cyclelist	*head = NULL;

	if (head == NULL)
		head = fork_head;
	if (fork_head != head)
	{
		free_fork(fork_head->next);
		free(fork_head);
	}
}

void	free_all(t_prog *prog)
{
	free_fork(prog->fork);
	free_philo(prog->philo);
}
