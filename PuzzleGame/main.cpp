#include <SFML/Graphics.hpp>

using namespace sf;

int main(void)
{
	RenderWindow app(VideoMode(256, 256), "PuzzleGame");
	app.setFramerateLimit(60);

	Texture t;
	t.loadFromFile("images/15.png");

	int grid[6][6] = { 0, };	// 1~15:해당숫자, 16:빈공간, 0:벽

	int w = 64;	// 퍼즐 하나의 폭

	Sprite sprite[17];

	int number = 1;
	// 그림을 쪼개고 논리적으로 매칭(좌표와 행렬, 그림과 숫자)
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sprite[number].setTexture(t);
			sprite[number].setTextureRect(IntRect(j * w, i * w, w, w));
			grid[i + 1][j + 1] = number;
			number++;
		}
	}

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				app.close();
			}

			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					Vector2i pos = Mouse::getPosition(app);
					int x = pos.x / w + 1;
					int y = pos.y / w + 1;

					int dx = 0, dy = 0;
					if (grid[y + 1][x] == 16) { dx = 0; dy = 1; }
					if (grid[y - 1][x] == 16) { dx = 0; dy = -1; }
					if (grid[y][x + 1] == 16) { dx = 1; dy = 0; }
					if (grid[y][x - 1] == 16) { dx = -1; dy = 0; }

					int temp = grid[y][x];
					grid[y][x] = 16;
					grid[y + dy][x + dx] = temp;

				}
			}
		}

		app.clear(Color::White);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				int n = grid[i + 1][j + 1];
				sprite[n].setPosition(j * w, i * w);
				app.draw(sprite[n]);
			}
		}
		app.display();
	}

	return 0;
}