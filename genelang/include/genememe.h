#ifndef GENELANG_MEME_H
#define GENELANG_MEME_H

#include <vector>

#include "geneexcept.h"
#include "geneinstruction.h"
#include "generandom.h"

namespace genelang
{
	class meme : private std::vector<instruction>
	{
	public:
		meme() = default;
		meme(const meme&) = default;
		meme(meme&&) = default;
		meme& operator=(const meme&) = default;
		meme& operator=(meme&&) = default;

		meme(size_t max, random& rand, const std::vector<instruction>& list);
		meme(const meme& parent, unsigned int tries, random& rand, const std::vector<instruction>& list);

		void operator()(void* me, const void* world) const;

	private:
		size_t max;

		bool validate() const;

		void mutate(unsigned int tries, random& rand, const std::vector<instruction>& list);
		void mutate(random& rand, const std::vector<instruction>& list);

		void swap(random& rand);
		void select(random& rand, const std::vector<instruction>& list);
	};
}

#endif//GENELANG_MEME_H