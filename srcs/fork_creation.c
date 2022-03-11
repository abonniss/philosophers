/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonniss <abonniss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:02:08 by abonniss          #+#    #+#             */
/*   Updated: 2022/03/11 14:38:09 by abonniss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_cyclelist	*create_fork_node(void)
{
	t_cyclelist	*fork_node;

	fork_node = malloc(sizeof(t_cyclelist));
	if (fork_node != NULL)
		ft_bzero(fork_node, sizeof(t_cyclelist));
	return (fork_node);
}

int	add_fork_nodes(t_cyclelist **head)
{
	t_cyclelist	*new_node;
	t_cyclelist	*node;

	node = *head;
	new_node = create_fork_node();
	if (new_node == NULL)
		return (MALLOC_ERROR);
	if (*head != NULL)
	{
		while (node->next != *head)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	new_node->next = *head;
	return (EXIT_SUCCESS);
}

t_cyclelist	*create_fork_list(size_t nbr_of_nodes)
{
	t_cyclelist	*fork;
	size_t		i;

	i = 0;
	fork = NULL;
	while (i < nbr_of_nodes)
	{
		if (add_fork_nodes(&fork) == MALLOC_ERROR)
		{
			free_fork(fork);
			return (NULL);
		}
		++i;
	}
	return (fork);
}
