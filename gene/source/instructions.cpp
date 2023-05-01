#include "instructions.h"

#include "indiv.h"
#include "grid.h"

#include <stack>

std::vector<genelang::instruction>& setupList()
{
	static std::vector<genelang::instruction> list;
	list.clear();

	list.emplace_back("no operation", 0, 0, [](std::stack<int>&, void*, const void*) {});

	list.emplace_back("my position", 0, 2,
		[](std::stack<int>& s, void* i, const void*)
		{
			const coordinate c = static_cast<indiv*>(i)->position();
			s.push(c.x);
			s.push(c.y);
		});

	list.emplace_back("my facing", 0, 2,
		[](std::stack<int>& s, void* i, const void*)
		{
			const coordinate c = static_cast<indiv*>(i)->direction();
			s.push(c.x);
			s.push(c.y);
		});

	list.emplace_back("is facing left", 0, 1,
		[](std::stack<int>& s, void* i, const void*)
		{
			if (static_cast<indiv*>(i)->direction() == coordinate{ -1, 0 })
			{
				s.push(1);
			}
			else
			{
				s.push(0);
			}
		});

	list.emplace_back("is facing right", 0, 1,
		[](std::stack<int>& s, void* i, const void*)
		{
			if (static_cast<indiv*>(i)->direction() == coordinate{ 1, 0 })
			{
				s.push(1);
			}
			else
			{
				s.push(0);
			}
		});

	list.emplace_back("is facing up", 0, 1,
		[](std::stack<int>& s, void* i, const void*)
		{
			if (static_cast<indiv*>(i)->direction() == coordinate{ 0, -1 })
			{
				s.push(1);
			}
			else
			{
				s.push(0);
			}
		});

	list.emplace_back("is facing down", 0, 1,
		[](std::stack<int>& s, void* i, const void*)
		{
			if (static_cast<indiv*>(i)->direction() == coordinate{ 0, 1 })
			{
				s.push(1);
			}
			else
			{
				s.push(0);
			}
		});

	list.emplace_back("turn left", 0, 0,
		[](std::stack<int>& s, void* i, const void*)
		{
			static_cast<indiv*>(i)->turnleft();
		});

	list.emplace_back("turn right", 0, 0,
		[](std::stack<int>& s, void* i, const void*)
		{
			static_cast<indiv*>(i)->turnright();
		});

	list.emplace_back("move", 0, 1,
		[](std::stack<int>& s, void* i, const void*)
		{
			const bool result = static_cast<indiv*>(i)->move();
			s.push(result);
		});

	list.emplace_back("turn left if", 1, 0,
		[](std::stack<int>& s, void* i, const void*)
		{
			if (s.top())
			{
				static_cast<indiv*>(i)->turnleft();
			}

			s.pop();
		});

	list.emplace_back("turn right if", 1, 0,
		[](std::stack<int>& s, void* i, const void*)
		{
			if (s.top())
			{
				static_cast<indiv*>(i)->turnright();
			}

			s.pop();
		});

	list.emplace_back("move if", 1, 0,
		[](std::stack<int>& s, void* i, const void*)
		{
			if (s.top())
			{
				static_cast<indiv*>(i)->move();
			}

			s.pop();
		});

	return list;
}