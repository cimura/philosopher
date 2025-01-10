#include <stdio.h>
#include <stdlib.h>

typedef struct s_que
{
	int	que[201];
	int	head;
	int	tail;
}	t_que;

typedef struct s_table
{
	t_que	que;
}	t_table;

void	init(t_table *table)
{
	table->que.head = table->que.tail = 0;
}

void	enque(t_table *table, int id)
{
	if (table->que.head == (table->que.tail + 1) % 201)
	{
		printf("que max\n");
		return ;
	}
	table->que.que[table->que.tail++] = id;
	if (table->que.tail == 201)
		table->que.tail = 0;
}

int	deque(t_table *table)
{
	if (table->que.head == table->que.tail)
	{
		printf("que empty\n");
		return -1;
	}
	int res = table->que.que[table->que.head];
	table->que.head++;
	if (table->que.head == 201)
		table->que.head = 0;
	return (res);
}

int	main() {
	t_table *table;
	table = malloc(sizeof(t_table));
	init(table);
	enque(table, 1);
	enque(table, 2);
	int	res = deque(table);
	printf("res is %d\n", res);
	enque(table, 5);
	res = deque(table);
	res = deque(table);
	printf("res is %d\n", res);
}