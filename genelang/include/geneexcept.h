#ifndef GENELANG_EXCEPT_H
#define GENELANG_EXCEPT_H

#include <stdexcept>
#include <string>

namespace genelang
{
	class gene_error : public std::logic_error
	{
	public:
		virtual ~gene_error() = default;

	protected:
		using logic_error::logic_error;
	};

	class labeled_logic_error : public gene_error
	{
	public:
		virtual ~labeled_logic_error() = default;

	protected:
		labeled_logic_error(const std::string origin, const std::string error) :
			gene_error('[' + origin + "]: " + error)
		{ }
	};
}

#endif//GENELANG_EXCEPT_H