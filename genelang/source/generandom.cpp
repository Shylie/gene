#include "generandom.h"

#include <ctime>

namespace genelang
{
	random::random() :
		random(time(nullptr))
	{ }

	random::random(uint64_t seed) :
		state(seed)
	{ }

	uint64_t random::rand()
	{
		state ^= state >> 12;
		state ^= state << 25;
		state ^= state >> 27;
		return state * 2685821657736338717u;
	}

	double random::rand01()
	{
		return rand() / 18446744073709551616.0;
	}
}