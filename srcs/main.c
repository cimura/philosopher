#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (5 == argc || 6 == argc)
	{
		parse_input(&table, argv);
		data_init(&table);
		party(&table);
		clean(&table);
	}
	else
		error_exit("Wrong input:\n"
			GREEN"example// ./philo 5 800 200 200 [5]"RESET);
	return (0);
}
