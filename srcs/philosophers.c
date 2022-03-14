/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonniss <abonniss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:51:24 by abonniss          #+#    #+#             */
/*   Updated: 2022/03/14 18:53:44 by abonniss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	control_args(char **parameters)
{
	size_t	i;

	i = SKIP_PROG_NAME;
	while (i != MIN_INPUT)
	{
		if (ft_isnumber(parameters[i]) == false
			|| ft_isnegative((int)ft_atol(parameters[i])) == true)
			return (false);
		++i;
	}
	if (parameters[MUST_EAT_INPUT])
	{
		if (ft_isnumber(parameters[MUST_EAT_INPUT]) == false
			|| ft_isnegative((int)ft_atol(parameters[MUST_EAT_INPUT])) == true)
			return (false);
	}
	return (true);
}

static void	fill_prog_info(char **inputs, t_prog *ptr_prog)
{
	ft_bzero(ptr_prog, sizeof(t_prog));
	ptr_prog->nbr_philosophes = (size_t)ft_atol(inputs[PHILO_ARG]);
	ptr_prog->nbr_philo_finished_all_meals = 0;
	ptr_prog->time_to_die = (useconds_t)ft_atol(inputs[TIME_TO_DIE_ARG]);
	ptr_prog->time_to_eat = (useconds_t)ft_atol(inputs[TIME_TO_EAT_ARG]) * 1000;
	ptr_prog->time_to_sleep = (useconds_t)ft_atol(inputs[TIME_TO_SLEEP_ARG])
		* 1000;
	if (inputs[MUST_EAT_INPUT])
		ptr_prog->min_meal = (size_t)ft_atol(inputs[MUST_EAT_INPUT]);
}

int	main(int ac, char **av)
{
	t_prog	prog;

	if (ac != MIN_INPUT && ac != MAX_INPUT)
	{
		printf("Not the right number of args\n");
		return (EXIT_FAILURE);
	}
	if (control_args(av) != true)
	{
		printf("Arguments are not correct\n");
		return (EXIT_FAILURE);
	}
	fill_prog_info(av, &prog);
	if (create_ressources(&prog) == MALLOC_ERROR)
		return (EXIT_FAILURE);
	launch_diner(&prog);
	join_threads(&prog);
	free_all(&prog);
	return (EXIT_SUCCESS);
}
