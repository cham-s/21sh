
# include "ft_select.h"
# include "libft.h"

void log_line(char *filename, void *type)
{
	t_line  *line;
    FILE * fp;

    line = (t_line *)type;
    if (!(fp = fopen(filename, "w")))
    {
        perror("error while opening: ");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "line: %s\ncurrent index: %zu\ncurrent char: %c\nposition start: %zu\nposition end: %zu\n",
                 line->buffer, 
                 line->position.current, 
                 line->buffer[line->position.current],
                 line->position.start, 
                 line->position.end);

    fclose(fp);
}

void    to_str(t_line *line) 
{
    ft_putstr(line->buffer);
}

size_t    next(size_t position)
{
    return position += 1;
}

size_t    previous(size_t position)
{
    return position -= 1;
}

void    init_position(t_position *position, size_t start, size_t end)
{
    position->start = start;
    position->end  = end;
    position->current = 0;
    position->next = next;
    position->previous = previous;
}

void    init_level(t_level *level)
{
    level->current = 1;
    level->count = 1;
}

void    init_line(t_line *line, char* str)
{
    init_position(&line->position, ft_strlen("21sh> "), ft_strlen("21sh> "));
    init_level(&line->level);
    line->buffer = ft_strdup(str);
    line->tmp = NULL;
}


#include <stdlib.h>

int     main() 
{
    t_line line;
    init_line(&line, "ls -l we've added more, modified");
    output_log linelog = log_line;
    line.position.current += 1;    
    line.position.current += 1;    
    line.position.current += 1;    
    line.position.current += 1;    
    line.position.current += 1;    
    line.position.current += 1;    
    line.position.current += 1;    
    linelog("log", (void *)&line);
}