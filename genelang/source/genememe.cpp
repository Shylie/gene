#include "genememe.h"

namespace genelang
{
	meme::meme(size_t max, random& rand, const std::vector<instruction>& list) :
		max(max)
	{
		do
		{
			clear();
			reserve(max);
			for (int i = 0; i < max; i++)
			{
				push_back(list[rand.rand() % list.size()]);
			}
		}
		while (!validate());
	}

	meme::meme(const meme& parent, unsigned int tries, random& rand, const std::vector<instruction>& list) :
		meme(parent)
	{
		mutate(tries, rand, list);
	}

	void meme::operator()(void* me, const void* world) const
	{
		std::stack<int> s;

		for (const instruction& instr : *this)
		{
			instr(s, me, world);
		}
	}

	void meme::mutate(unsigned int tries, random& rand, const std::vector<instruction>& list)
	{
		for (unsigned int i = 0; i < tries; i++)
		{
			mutate(rand, list);
		}
	}

	bool meme::validate() const
	{
		int stacksize = 0;

		for (const instruction& instr : *this)
		{
			stacksize -= instr.consume;

			if (stacksize < 0)
			{
				return false;
			}

			stacksize += instr.produce;
		}

		return true;
	}

	void meme::mutate(random& rand, const std::vector<instruction>& list)
	{
		meme temp(*this);

		switch (rand.rand() % 2)
		{
		case 0:
			temp.swap(rand);
			break;

		case 1:
			temp.select(rand, list);
			break;
		}

		if (temp.validate())
		{
			*this = std::move(temp);
		}
	}

	void meme::swap(random& rand)
	{
		std::swap((*this)[rand.rand() % max], (*this)[rand.rand() % max]);
	}

	void meme::select(random& rand, const std::vector<instruction>& list)
	{
		(*this)[rand.rand() % max] = list[rand.rand() % list.size()];
	}
}