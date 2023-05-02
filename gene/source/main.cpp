#include "instructions.h"
#include "grid.h"
#include "indiv.h"

#include <raylib.h>

constexpr int N = 100;
constexpr int PIXEL = 7;
constexpr int LIMIT = 125;
constexpr int LARGE_FPS = 9999;

int main()
{
	int target = LARGE_FPS;

	InitWindow(PIXEL * N, PIXEL * N, "gene");
	SetTargetFPS(target);

	grid g(N, N, 500, 128, setupList());

	int frame = 0;
	int generation = 0;

	const auto& selection = [](const indiv& i, void* ud) -> bool
	{
		return i.position().x % 2;
	};

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			if (target > 10)
			{
				target = 10;
			}
			else
			{
				target = LARGE_FPS;
			}

			SetTargetFPS(target);
		}

		g.update();

		BeginDrawing();
		ClearBackground(WHITE);

		g.draw(PIXEL);

		DrawText(TextFormat("%d %d", generation, frame), 20, 20, 20, GREEN);

		EndDrawing();

		frame++;
		if (frame >= LIMIT - 1)
		{
			grid tmp(g, (g.random().rand() % 25) == 0, nullptr, selection);
			g = tmp;

			frame = 0;

			generation++;
		}
	}

	CloseWindow();

	return 0;
}