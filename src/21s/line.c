
# include "../../include/ft_select.h"
# include "../../libft/includes/libft.h"

void    to_str(t_line *line) 
{
    ft_putstr(line->buffer);
}

void    init_position(t_position *position)
{
    position->start = ft_strlen("21sh ");
    position->end  = ft_strlen("21sh ");
}

void    init_level(t_level *level)
{
    level->current = 1;
    level->count = 1;
}

void    init_line(t_line *line, char* str)
{
    init_position(&line->position);
    init_level(&line->level);
    line->buffer = ft_strdup(str);
    line->tmp = NULL;
    line->current_index = 0;
    line->to_str = to_str;
}


#include <stdlib.h>

int     main() 
{
    t_line line;
    init_line(&line, "ls -l\n");
    line.to_str(&line);    
}