#include "instructions.h"
#include "grid.h"
#include "indiv.h"

#include <raylib.h>

constexpr int N = 100;
constexpr int LIMIT = 100;

int main()
{
	InitWindow(800, 800, "gene");
	SetTargetFPS(120);

	grid g(N, N, 500, 16, setupList());

	int frame = 0;
	int generation = 0;

	for (; generation < 250; generation++)
	{
		for (frame = 0; frame < LIMIT; frame++)
		{
			g.update();
		}
		grid tmp(g, (g.random().rand() % 3) == 0, [](const indiv& i) { return i.position().x >= 94; });
		g = tmp;
	}

	while (!WindowShouldClose())
	{
		g.update();

		BeginDrawing();
		ClearBackground(WHITE);

		g.draw(800 / N);

		DrawText(TextFormat("%d %d", generation, frame++), 20, 20, 20, GREEN);

		EndDrawing();

		if (frame >= LIMIT - 1)
		{
			grid tmp(g, (g.random().rand() % 3) == 0, [](const indiv& i) { return i.position().x >= 94; });
			g = tmp;

			frame = 0;

			generation++;
		}
	}

	CloseWindow();

	return 0;
}