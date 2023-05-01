#ifndef GENELANG_INSTRUCTION_H
#define GENELANG_INSTRUCTION_H

#include <cstdint>
#include <stack>
#include <string>

#include "geneexcept.h"

namespace genelang
{
	class instruction
	{
		friend class meme;
	public:
		class error : public gene_error
		{
			friend class instruction;
		public:
			virtual ~error() = default;

		private:
			error(const instruction* i, const std::string error) :
				gene_error(error)
			{ }
		};

		using operation = void (*)(std::stack<int>& data, void* me, const void* world);

		inline instruction(const char* name, size_t in, size_t out, operation op) :
			consume(in),
			produce(out),
			name(name),
			op(op)
		{ }

		instruction(const instruction&) = default;
		instruction(instruction&&) = default;
		instruction& operator=(const instruction&) = default;
		instruction& operator=(instruction&&) = default;

		inline void operator()(std::stack<int>& data, void* me, const void* world) const
		{
			const size_t sizeIn = data.size();

			// check if there are enough items on the stack to call this instruction
			if (sizeIn < consume)
			{
				throw merror("stack underflow");
			}

			op(data, me, world);

			// check if the amount of items on the stack is equal to the expected size
			if (data.size() != sizeIn + produce - consume)
			{
				throw merror("unexpected stack size");
			}
		}

		inline error merror(const std::string emsg) const
		{
			return error(this, emsg);
		}

	private:
		size_t consume;
		size_t produce;
		std::string name;
		operation op;
	};
}

#endif//GENELANG_INSTRUCTION_H