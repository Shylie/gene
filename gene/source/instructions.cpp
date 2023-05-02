#include "instructions.h"

#include "indiv.h"
#include "grid.h"

#include <stack>

std::vector<genelang::instruction>& setupList()
{
	static std::vector<genelang::instruction> list;
	list.clear();

	list.emplace_back("no operation", 0, 0, [](std::stack<int>&, void*, const void*) {});

	list.emplace_back("distance to nearest object", 0, 1,
		[](std::stack<int>& s, void* _i, const void* _g)
		{
			indiv* const i = static_cast<indiv*>(_i);
			const grid* const g = static_cast<const grid*>(_g);

			int dist = 0;
			for (coordinate pos = i->front(); g->inside(pos) && (*g)[pos] == -1; pos = pos + i->direction())
			{
				dist++;
			}

			s.push(dist);
		});

	list.emplace_back("distance to left wall", 0, 1,
		[](std::stack<int>& s, void* _i, const void* _g)
		{
			indiv* const i = static_cast<indiv*>(_i);
			const grid* const g = static_cast<const grid*>(_g);

			int dist = 0;
			for (coordinate pos = i->position(); g->inside(pos); pos = pos + coordinate{ -1, 0 })
			{
				dist++;
			}

			s.push(dist);
		});

	list.emplace_back("distance to right wall", 0, 1,
		[](std::stack<int>& s, void* _i, const void* _g)
		{
			indiv* const i = static_cast<indiv*>(_i);
			const grid* const g = static_cast<const grid*>(_g);

			int dist = 0;
			for (coordinate pos = i->position(); g->inside(pos); pos = pos + coordinate{ 1, 0 })
			{
				dist++;
			}

			s.push(dist);
		});

	list.emplace_back("distance to up wall", 0, 1,
		[](std::stack<int>& s, void* _i, const void* _g)
		{
			indiv* const i = static_cast<indiv*>(_i);
			const grid* const g = static_cast<const grid*>(_g);

			int dist = 0;
			for (coordinate pos = i->position(); g->inside(pos); pos = pos + coordinate{ 0, -1 })
			{
				dist++;
			}

			s.push(dist);
		});

	list.emplace_back("distance to down wall", 0, 1,
		[](std::stack<int>& s, void* _i, const void* _g)
		{
			indiv* const i = static_cast<indiv*>(_i);
			const grid* const g = static_cast<const grid*>(_g);

			int dist = 0;
			for (coordinate pos = i->position(); g->inside(pos); pos = pos + coordinate{ 0, 1 })
			{
				dist++;
			}

			s.push(dist);
		});

	list.emplace_back("logical negate", 1, 1,
		[](std::stack<int>& s, void*, const void*)
		{
			const bool a = s.top();
			s.pop();

			s.push(!a);
		});

	list.emplace_back("add", 2, 1,
		[](std::stack<int>& s, void*, const void*)
		{
			const int b = s.top();
			s.pop();
			const int a = s.top();
			s.pop();

			s.push(a + b);
		});

	list.emplace_back("subtract", 2, 1,
		[](std::stack<int>& s, void*, const void*)
		{
			const int b = s.top();
			s.pop();
			const int a = s.top();
			s.pop();

			s.push(a - b);
		});

	list.emplace_back("greater than", 2, 1,
		[](std::stack<int>& s, void*, const void*)
		{
			const int b = s.top();
			s.pop();
			const int a = s.top();
			s.pop();

			s.push(a > b);
		});

	list.emplace_back("less than", 2, 1,
		[](std::stack<int>& s, void*, const void*)
		{
			const int b = s.top();
			s.pop();
			const int a = s.top();
			s.pop();

			s.push(a < b);
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

	list.emplace_back("move", 0, 0,
		[](std::stack<int>& s, void* i, const void*)
		{
			static_cast<indiv*>(i)->move();
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