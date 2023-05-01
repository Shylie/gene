#ifndef INDIV_H
#define INDIV_H

#include <genelang.h>

#include "grid.h"

class indiv
{
	friend grid;
public:
	indiv(grid*, coordinate, size_t max, const std::vector<genelang::instruction>& list);
	indiv(const indiv&, grid*, coordinate, unsigned int, const std::vector<genelang::instruction>& list);

	indiv(const indiv&) = default;

	bool move();
	void turnleft();
	void turnright();

	coordinate position() const;
	coordinate direction() const;
	coordinate front() const;
	coordinate back() const;
	coordinate left() const;
	coordinate right() const;

private:

	grid* grid;
	coordinate current;
	coordinate facing;

	genelang::meme genome;
};

#endif//INDIV_H