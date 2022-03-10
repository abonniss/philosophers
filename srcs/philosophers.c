/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonniss <abonniss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:51:24 by abonniss          #+#    #+#             */
/*   Updated: 2022/03/10 18:34:47 by abonniss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool control_args(char** parameters)
{
    size_t i;
    
    i = SKIP_PROG_NAME;
    while (i != MIN_INPUT)
    {
        if (ft_isnumber(parameters[i]) == false || 
            ft_isnegative(ft_atol(parameters[i])) == true)
            return (false);
        ++i;
    }
    if (parameters[MUST_EAT_INPUT])
    {
        if (ft_isnumber(parameters[MUST_EAT_INPUT]) == false || 
            ft_isnegative(ft_atol(parameters[MUST_EAT_INPUT])) == true)
            return (false);
    }
    return(true);
}

int fill_prog_info(char **inputs, t_prog *ptr_prog)
{
    memset(ptr_prog, 0, sizeof(t_cyclelist));
    ptr_prog->nbr_philosophes   = ft_atol(inputs[PHILO_ARG]);
    ptr_prog->time_to_die       = ft_atol(inputs[TIME_TO_DIE_ARG]);
    ptr_prog->time_to_eat       = ft_atol(inputs[TIME_TO_EAT_ARG]);
    ptr_prog->time_to_sleep     = ft_atol(inputs[TIME_TO_SLEEP_ARG]);
    ptr_prog->write_mutex       = malloc(sizeof(pthread_mutex_t));
    if (ptr_prog->write_mutex == NULL)
        return (MALLOC_ERROR);
    ptr_prog->dead_mutex        = malloc(sizeof(pthread_mutex_t));
    if (ptr_prog->dead_mutex == NULL)
    {
        free(ptr_prog->write_mutex);
        return (MALLOC_ERROR);
    }
    ptr_prog->meal_mutex        = malloc(sizeof(pthread_mutex_t));
    if (ptr_prog->meal_mutex == NULL)
    {
        free(ptr_prog->write_mutex);
        free(ptr_prog->dead_mutex);
        return (MALLOC_ERROR);
    }
    if (inputs[MUST_EAT_INPUT])
        ptr_prog->min_meal      = ft_atol(inputs[MUST_EAT_INPUT]);
    return (EXIT_SUCCESS);
}

int main (int ac, char** av)
{
    t_prog prog;

    if (ac != MIN_INPUT && ac != MAX_INPUT)
        return (EXIT_FAILURE);   
    if (control_args(av) != true)
        return (EXIT_FAILURE);
    if (fill_prog_info(av, &prog) == MALLOC_ERROR)
        return(EXIT_FAILURE);
    if (create_ressources(&prog) == MALLOC_ERROR)
    {
        free_prog_mutex(&prog);
        return (EXIT_FAILURE);
    }    
    launch_diner(&prog);
    join_threads(&prog);
    free_all(&prog);
    return (EXIT_SUCCESS);
}