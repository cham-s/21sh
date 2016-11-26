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
	printf("\n\t\t\tposition: %ld\n\
			position - start: %ld\n\
			level: %f\n\
			level count: %d\n\
			level bucket: %d\n\
			buffer size: %ld\n\
			term width: %d\n\
			float result: %f\n\
			int resut: %d\n\
			cast double result: %f\n\
			buffer len + 6 (+ len(21sh> )): %d\n", l->position,
			   l->position - 6,
		   	   l->level, l->level_count,
			   l->level_bucket,
			   ft_strlen(l->buffer),
			   l->term_width, result, trunc, (double)trunc, (int)size + 6);
}
