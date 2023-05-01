#ifndef GENELANG_RANDOM_H
#define GENELANG_RANDOM_H

#include <cstdint>

namespace genelang
{
	class random
	{
	public:
		random();
		random(uint64_t seed);

		uint64_t rand();
		double rand01();

	private:
		uint64_t state;
	};
}

#endif//GENELANG_RANDOM_H