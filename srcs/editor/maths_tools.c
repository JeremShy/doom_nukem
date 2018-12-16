#include <editor.h>

t_ivec2		find_middle_edge(t_edge *edge)
{
	return ((t_ivec2){(edge->p1->x + edge->p2->x) / 2, (edge->p1->y + edge->p2->y) / 2});
}
