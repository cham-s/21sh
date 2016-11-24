#include "21sh.h"
#include <stdio.h>
// printf()

void display_debug_info(t_line *l)
{
	printf("\n\t\t\tposition: %ld\n\
			position - start: %ld\n\
			level: %f\n\
			level count: %d\n\
			level bucket: %d\n\
			buffer size: %ld\n\
			term width: %d\n", l->position,
			   l->position - 6,
		   	   l->level, l->level_count,
			   l->level_bucket,
			   ft_strlen(l->buffer),
			   l->term_width);
}
