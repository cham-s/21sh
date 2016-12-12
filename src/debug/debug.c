#include "21sh.h"
#include <stdio.h>
// printf()

void display_debug_info(t_line *l)
{
	double	result;
	int		trunc;
	size_t	size;

	size = ft_strlen(l->buffer);
	result = (double)ft_strlen(l->buffer) / (double)l->term_width;
	trunc = size / l->term_width;
	printf("\npos: %ld\n", l->position);
	printf("width: %d\n", l->term_width);
	printf("buc: %d\n", l->level_bucket);
	printf("level: %d\n", l->level_count);
}
