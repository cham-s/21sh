#include "ft_select.h"

t_line_stack	*stack_create(void)
{
	int	init_size = 4;
	return(init_stack(init_size));
}

t_line_stack	*init_stack(int size)
{
	t_line_stack	*stack;
	int				i;

	i = 0;
	stack = (t_line_stack *)ft_memalloc(sizeof(t_line_stack));
	if (!stack)
		return (NULL);
	stack->size = size;
	stack->array = (char **)ft_memalloc(sizeof(char *) * stack->size); 
	while (i < size)
	{
		stack->array[i] = NULL;
		i++;
	}
	return (stack);
}

void	stack_destroy(t_line_stack *stack)
{
	int		i;

	i = 0;
	while (stack->array[i])
	{
		free(stack->array[i]);
		stack->array[i] = NULL;
		i++;
	}
	free(stack->array);
	free(stack);
}

void		stack_grow(t_line_stack *stack, int growth_factor, int index)
{
	t_line_stack	*new_stack;
	t_line_stack	swap;
	int				i;

	i = 0;
	new_stack = init_stack(stack->size * growth_factor);
	new_stack->index = index;
	if (!new_stack)
	{
		ft_putendl_fd("System does not have enough ressources", 2);
		exit(EXIT_FAILURE);
	}
	while (i < stack->size)
	{
		new_stack->array[i] = stack->array[i];
		i++;
	}
	swap = *stack;
	*stack = *new_stack;
	*new_stack = swap;
	//stack_destroy(new_stack);
}

void	push_stack(t_line_stack *stack, char *line)
{
	int i;
	i = 0;

	while (stack->array[i])
		i++;
	if (i < stack->size)
		stack->array[i] = ft_strdup(line);
	else
	{
#define	GROWTH 2
		stack_grow(stack, GROWTH, stack->index);
		push_stack(stack, line);
	}
}
