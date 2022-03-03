
#include "philosophers.h"

bool	ft_isnegative(int nbr)
{
	return (nbr < 0);
}

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

bool	ft_isnumber(const char *str)
{
	size_t	i;

	i = 0;
	if (*str == '-')
		str++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (false);
		i++;
	}
	return (i != 0);
}

static int	ft_isspace(char c)
{
	if ((c == '\t') || (c == '\n') || (c == '\r')
		|| (c == '\v') || (c == '\f') || (c == ' '))
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	int		signe;
	long	number;

	while (ft_isspace(*str))
		str++;
	signe = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			signe *= -1;
		str++;
	}
	number = 0;
	while (*str >= '0' && *str <= '9')
	{
		number *= 10;
		number += *str - '0';
		str++;
	}
	return (number *= signe);
}