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

void indiv::operator()(grid* g)
{
	genome(this, g);
}

void indiv::move()
{
	const coordinate dest = current + facing;
	if ((*gridref).inside(dest) && (*gridref)[dest] == -1)
	{
		(*gridref)[dest] = (*gridref)[current];
		(*gridref)[current] = -1;

		current = current + facing;
	}
}

void indiv::turnleft()
{
	facing = facing.left();
}

void indiv::turnright()
{
	facing = facing.right();
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