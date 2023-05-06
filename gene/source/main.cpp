#include "instructions.h"
#include "grid.h"
#include "indiv.h"

#include <raylib.h>

constexpr int N = 100;
constexpr int PIXEL = 10;
constexpr int LIMIT = 50;
constexpr int LARGE_FPS = 9999;
constexpr int SMALL_FPS = 30;

int main()
{
	int target = LARGE_FPS;
	bool draw = true;

	InitWindow(PIXEL * N, PIXEL * N, "gene");
	SetTargetFPS(target);

	grid g(N, N, 1500, 128, setupList());

	int frame = 0;
	int generation = 0;

	const auto& selection = [](const indiv& i, void* ud) -> bool
	{
		grid* g = static_cast<grid*>(ud);

		for (int x = i.position().x - 1; x <= i.position().x + 1; x++)
		{
			for (int y = i.position().y - 1; y <= i.position().y + 1; y++)
			{
				if (x != 0 && y != 0)
				{
					if (!g->inside({ x, y }) || (*g)[{ x, y }] != -1)
					{
						return false;
					}
				}
			}
		}

		return true;
	};

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			if (target > SMALL_FPS)
			{
				target = SMALL_FPS;
			}
			else
			{
				target = LARGE_FPS;
			}

			SetTargetFPS(target);
		}

		if (IsKeyPressed(KEY_D))
		{
			draw = !draw;
		}

		g.update();

		BeginDrawing();
		ClearBackground(WHITE);

		if (draw)
		{
			g.draw(PIXEL);
		}

		DrawText(TextFormat("%d %d", generation, frame), 20, 20, 20, GREEN);
		DrawFPS(20, 40);

		EndDrawing();

		frame++;
		if (frame >= LIMIT - 1)
		{
			grid tmp(g, (g.random().rand() % 35) == 0, &g, selection);
			g = tmp;

			frame = 0;

			generation++;
		}
	}

	CloseWindow();

	return 0;
}