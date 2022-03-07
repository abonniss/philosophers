
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
            return (false)
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
        ptr_prog->must_eat      = ft_atol(inputs[TIME_TO_SLEEP_ARG]);
}

void *routine()
{
    printf("test\n");
    return (NULL);
}

int launch_diner(t_prog prog)
{
    pthread_t philo_th[prog.nbr_philosophes];
    int i;

    i = 0;
    while (i != prog.nbr_philosophes)
    {
        if (pthread_create(&philo_th[i], NULL, &routine, NULL) != 0)
            return (EXIT_FAILURE);
        ++i;
    }
    i = 0;
    while (i != prog.nbr_philosophes)
    {
        if (pthread_join(philo_th[i], NULL) != 0)
            return (EXIT_FAILURE);
        ++i;
    }
    return (EXIT_SUCCESS);
    
}

int main (int ac, char** av)
{
    t_prog prog;

    if (ac != NECESSARY_INPUT || control_args(av) != true)
        return (EXIT_FAILURE);
    fill_prog_info(av, &prog);
    launch_diner(prog);

    return (EXIT_SUCCESS);
}