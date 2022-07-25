#include "philosophers.h"

int	check_overflow(char **av)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (ft_strlen(OVERFLOW_MAX) == ft_strlen(av[i]))
			if (!ft_strncmp(OVERFLOW_MAX, av[i], ft_strlen(OVERFLOW_MAX)))
				return (1);
		i++;
	}
	return (0);
}
int check_chars(char **av)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (av[i])
	{
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

int	parse_args(int ac, char **av, t_all *var)
{
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Error it must be 5 arguments\n", 2);
		free(var);
		return (0);
	}
	if (check_chars(&av[1]) || check_overflow(&av[1]))
	{
		ft_putstr_fd("Arguments not valid please input only numbers and", 2);
		ft_putstr_fd(" not over the overflow plz :)\n", 2);
		return (0);
	}
	if (ac == 5)
		init_rules(var, av, 0);
	else if (ac == 6)
		init_rules(var, av, 1);
	return (1);
}