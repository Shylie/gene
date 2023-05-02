#include "instructions.h"
#include "grid.h"
#include "indiv.h"

#include <raylib.h>

constexpr int N = 100;
constexpr int PIXEL = 10;
constexpr int LIMIT = 100;

int main()
{
	InitWindow(PIXEL * N, PIXEL * N, "gene");
	//SetTargetFPS(60);

	grid g(N, N, 1000, 32, setupList());

	int frame = 0;
	int generation = 0;

	const auto& selection = [](const indiv& i, void* ud) -> bool
	{
		return i.position().x % 2;
	};
	//const auto& selection = [](const indiv& i, void* ud) { return i.position().x >= N - 2; };

	for (; generation < 0; generation++)
	{
		for (frame = 0; frame < LIMIT; frame++)
		{
			g.update();
		}
		grid tmp(g, (g.random().rand() % 10) == 0, nullptr, selection);
		g = tmp;
	}

	while (!WindowShouldClose())
	{
		g.update();

		BeginDrawing();
		ClearBackground(WHITE);

		g.draw(PIXEL);

		DrawText(TextFormat("%d %d", generation, frame++), 20, 20, 20, GREEN);

		EndDrawing();

		if (frame >= LIMIT - 1)
		{
			grid tmp(g, (g.random().rand() % 10) == 0, nullptr, selection);
			g = tmp;

			frame = 0;

			generation++;
		}
	}

	CloseWindow();

	return 0;
}