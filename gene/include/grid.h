#ifndef GRID_H
#define GRID_H

#include <atomic>
#include <vector>

#include <genelang.h>

class indiv;

struct coordinate
{
	int x;
	int y;

	inline coordinate() :
		coordinate(0, 0)
	{ }

	inline coordinate(int x, int y) :
		x(x),
		y(y)
	{ }

	inline coordinate(size_t x, size_t y) :
		x(x),
		y(y)
	{ }

	inline coordinate(genelang::random& rand) :
		x(rand.rand() % 3 - 1),
		y(rand.rand() % 3 - 1)
	{
		while (x == 0 && y == 0)
		{
			x = rand.rand() % 3 - 1;
			y = rand.rand() % 3 - 1;
		}

		if (x != 0 && y != 0)
		{
			if (rand.rand() % 2 == 0)
			{
				x = 0;
			}
			else
			{
				y = 0;
			}
		}
	}

	inline coordinate reverse() const
	{
		return coordinate{ -x, -y };
	}

	inline coordinate left() const
	{
		return coordinate{ y, x };
	}

	inline coordinate right() const
	{
		return coordinate{ y, -x };
	}
};

inline static coordinate operator+(coordinate a, coordinate b)
{
	return coordinate{ a.x + b.x, a.y + b.y };
}

inline static bool operator==(coordinate a, coordinate b)
{
	return a.x == b.x && a.y == b.y;
}

class atomic_int_ext : public std::atomic_int
{
public:
	inline atomic_int_ext() :
		std::atomic_int()
	{ }

	inline atomic_int_ext(const int o) :
		std::atomic_int(o)
	{ }

	inline atomic_int_ext(const atomic_int_ext& o) :
		atomic_int_ext(o.load())
	{ }

	inline atomic_int_ext& operator=(const atomic_int_ext& o)
	{
		store(o.load());

		return *this;
	}
};

class grid
{
public:
	grid(unsigned int width, unsigned int height, unsigned int cnt, size_t max, std::vector<genelang::instruction>& list);
	grid(grid& previousGeneration, unsigned int tries, void* ud, bool (*)(const indiv&, void*));

	grid& operator=(const grid&);

	atomic_int_ext& operator[](coordinate);
	const atomic_int_ext& operator[](coordinate) const;

	bool inside(coordinate) const;

	genelang::random& random();

	void update();
	void draw(unsigned int scale) const;

	inline unsigned int getWidth() const { return width; }
	inline unsigned int getHeight() const { return height; }

private:
	unsigned int width;
	unsigned int height;
	unsigned int cnt;

	std::vector<atomic_int_ext> indices;
	std::vector<indiv> indivs;

	size_t max;
	std::vector<genelang::instruction> list;

	genelang::random rand;

	void create(size_t max);
	void create(unsigned int tries, indiv&);
};

#endif//GRID_H