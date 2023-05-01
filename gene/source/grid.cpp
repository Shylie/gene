#include "grid.h"
#include "indiv.h"

#include <raylib.h>

grid::grid(unsigned int w, unsigned int h, unsigned int cnt, size_t max, std::vector<genelang::instruction>& list) :
	indices(w * h),
	width(w),
	height(h),
	cnt(cnt),
	max(max),
	list(list),
	rand()
{
	std::fill(indices.begin(), indices.end(), -1);
	indivs.reserve(cnt);

	for (unsigned int i = 0; i < cnt; i++)
	{
		create(max);
	}
}

grid::grid(grid& pg, unsigned int tries, bool (*selector)(const indiv&)) :
	indices(pg.width * pg.height),
	width(pg.width),
	height(pg.height),
	cnt(pg.cnt),
	max(pg.max),
	list(pg.list),
	rand(pg.rand)
{
	std::fill(indices.begin(), indices.end(), -1);
	indivs.reserve(cnt);

	std::vector<size_t> survived;
	for (unsigned int i = 0; i < cnt; i++)
	{
		if (selector(pg.indivs[i]))
		{
			survived.push_back(i);
		}
	}

	while (indivs.size() < cnt)
	{
		for (size_t i = 0; i < survived.size() && indivs.size() < cnt; i++)
		{
			create(tries, pg.indivs[survived[i]]);
		}
	}
}

grid& grid::operator=(const grid& g)
{
	width = g.width;
	height = g.height;
	cnt = g.cnt;
	indices = g.indices;
	indivs = g.indivs;

	max = g.max;
	list = g.list;

	rand = g.rand;

	for (indiv& i : indivs)
	{
		i.grid = this;
	}

	return *this;
}

int& grid::operator[](coordinate c)
{
	return indices[c.x + width * c.y];
}

int grid::operator[](coordinate c) const
{
	return indices[c.x + width * c.y];
}

bool grid::inside(coordinate c) const
{
	return c.x >= 0 && c.x < width && c.y >= 0 && c.y < height;
}

genelang::random& grid::random()
{
	return rand;
}

void grid::update()
{
	for (indiv& i : indivs)
	{
		i.genome(&i, this);
	}
}

void grid::draw(unsigned int pixels) const
{
	for (size_t i = 0; i < indivs.size(); i++)
	{
		DrawRectangle(indivs[i].current.x * pixels, indivs[i].current.y * pixels, pixels, pixels, RED);
	}
}

void grid::create(size_t max)
{
	coordinate c{ rand.rand() % width, rand.rand() % height };

	while ((*this)[c] != -1)
	{
		c = { rand.rand() % width, rand.rand() % height };
	}

	const size_t idx = indivs.size();
	indivs.emplace_back(this, c, max, list);
	(*this)[c] = idx;
}

void grid::create(unsigned int tries, indiv& i)
{
	coordinate c{ rand.rand() % width, rand.rand() % height };

	while ((*this)[c] != -1)
	{
		c = coordinate{ rand.rand() % width, rand.rand() % height };
	}

	const size_t idx = indivs.size();
	indivs.emplace_back(i, this, c, tries, list);
	(*this)[c] = idx;
}