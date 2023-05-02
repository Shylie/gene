#include "indiv.h"
#include "grid.h"

indiv::indiv(grid* g, coordinate c, size_t max, const std::vector<genelang::instruction>& list) :
	gridref(g),
	current(c),
	facing(g->random()),
	genome(max, g->random(), list)
{ }

indiv::indiv(const indiv& i, grid* g, coordinate c, unsigned int tries, const std::vector<genelang::instruction>& list) :
	gridref(g),
	current(c),
	facing(g->random()),
	genome(i.genome, tries, g->random(), list)
{ }

void indiv::move()
{
	gridref->queue(this, move);
}

void indiv::turnleft()
{
	gridref->queue(this, turnleft);
}

void indiv::turnright()
{
	gridref->queue(this, turnright);
}

coordinate indiv::position() const
{
	return current;
}

coordinate indiv::direction() const
{
	return facing;
}

coordinate indiv::front() const
{
	return current + facing;
}

coordinate indiv::left() const
{
	return current + facing.left();
}

coordinate indiv::right() const
{
	return current + facing.right();
}

coordinate indiv::back() const
{
	return current + facing.reverse();
}

void indiv::move(grid* g, indiv* i)
{
	const coordinate dest = i->current + i->facing;
	if ((*g).inside(dest) && (*g)[dest] == -1)
	{
		(*g)[dest] = (*g)[i->current];
		(*g)[i->current] = -1;

		i->current = i->current + i->facing;
	}
}

void indiv::turnleft(grid* g, indiv* i)
{
	i->facing = i->facing.left();
}

void indiv::turnright(grid* g, indiv* i)
{
	i->facing = i->facing.right();
}