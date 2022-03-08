
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

void fill_prog_info(char **inputs, t_prog *ptr_prog)
{
    ptr_prog->nbr_philosophes   = ft_atol(inputs[PHILO_ARG]);
    ptr_prog->time_to_die       = ft_atol(inputs[TIME_TO_DIE_ARG]);
    ptr_prog->time_to_eat       = ft_atol(inputs[TIME_TO_EAT_ARG]);
    ptr_prog->time_to_sleep     = ft_atol(inputs[TIME_TO_SLEEP_ARG]);
    if (inputs[MUST_EAT_INPUT])
        ptr_prog->nbr_meal      = ft_atol(inputs[MUST_EAT_INPUT]);
}


int main (int ac, char** av)
{
    t_prog prog;

    if (ac != MIN_INPUT || control_args(av) != true)
        return (EXIT_FAILURE);
    fill_prog_info(av, &prog);
    printf("Nbr Philo (%d) - Time_to_die (%d) - Time_to_eat (%d) - Time_to_sleep (%d)\n", prog.nbr_philosophes, prog.time_to_die, prog.time_to_eat, prog.time_to_sleep);
    assign_ressources(&prog);
    launch_diner(&prog);

    return (EXIT_SUCCESS);
}