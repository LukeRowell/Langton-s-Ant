#include <SFML/Graphics.hpp>
#include <windows.h>
#include <chrono>
#include <thread>

const int GRID_SIZE = 5000;
int** heatmapValues = new int*[GRID_SIZE];
bool showHeatmap = false;
bool slowdown = true;
sf::RenderWindow window(sf::VideoMode(1000, 1000), "Langton's Ant");
sf::Image grid;
sf::Texture gridTexture;
sf::Sprite gridSprite;
sf::Image heatmapGrid;
sf::Texture heatmapGridTexture;
sf::Sprite heatmapGridSprite;

DWORD WINAPI moveAnt(LPVOID lpParameter)
{
	int antX = GRID_SIZE / 2;
	int antY = GRID_SIZE / 2;
	int antOrientation = 1;
	float heatmapValue = 0.0f;
	sf::Color red(255, 0, 0, 255);
	sf::Color yellow(255, 255, 0, 255);
	sf::Color green(0, 255, 0, 255);
	sf::Color cyan(0, 255, 255, 255);
	sf::Color blue(0, 0, 255, 255);

	while (window.isOpen())
	{
		//Wrap the ant back around if it runs into the edge of the grid
		if (antX < 0)
		{
			antX = GRID_SIZE - 1;
		}

		if (antY < 0)
		{
			antY = GRID_SIZE - 1;
		}

		if (antX > GRID_SIZE - 1)
		{
			antX = 0;
		}

		if (antY > GRID_SIZE - 1)
		{
			antY = 0;
		}

		//Normalize the heat map value between 0 and 1
		heatmapValues[antX][antY]++;
		heatmapValue = (float)heatmapValues[antX][antY] / 100.0f;

		if (heatmapValue > 1)
		{
			//If the cell has exceeded 100 visits, don't update it's color anymore
		}

		else
		{
			//Interpolate the color between the correct ranges
			if (heatmapValue <= 0.2)	//Blue -> Cyan
			{
				heatmapGrid.setPixel(antX, antY, sf::Color((cyan.r - blue.r) * heatmapValue + blue.r, (cyan.g - blue.g) * heatmapValue + blue.g, (cyan.b - blue.b) * heatmapValue + blue.b, 255));
			}

			else if (heatmapValue > 0.2 && heatmapValue <= 0.4)		//Cyan -> Green
			{
				heatmapGrid.setPixel(antX, antY, sf::Color((green.r - cyan.r) * heatmapValue + cyan.r, (green.g - cyan.g) * heatmapValue + cyan.g, (green.b - cyan.b) * heatmapValue + cyan.b, 255));
			}

			else if (heatmapValue > 0.4 && heatmapValue <= 0.6)		//Green -> Yellow
			{
				heatmapGrid.setPixel(antX, antY, sf::Color((yellow.r - green.r) * heatmapValue + green.r, (yellow.g - green.g) * heatmapValue + green.g, (yellow.b - green.b) * heatmapValue + green.b, 255));
			}

			else if (heatmapValue > 0.6 && heatmapValue <= 0.8)		//Yellow -> Red
			{
				heatmapGrid.setPixel(antX, antY, sf::Color((red.r - yellow.r) * heatmapValue + yellow.r, (red.g - yellow.g) * heatmapValue + yellow.g, (red.b - yellow.b) * heatmapValue + yellow.b, 255));
			}

			else if (heatmapValue > 0.8)		//Red
			{
				heatmapGrid.setPixel(antX, antY, red);
			}
		}

		if ((grid.getPixel(antX, antY)) == sf::Color::Black)		//If the ant is on a black square
		{
			switch (antOrientation)
			{
				case 0:		//Left
					grid.setPixel(antX, antY, sf::Color::White);
					antX += 1;
					antOrientation = 3;
					break;

				case 1:		//Up
					grid.setPixel(antX, antY, sf::Color::White);
					antY -= 1;
					antOrientation--;
					break;

				case 2:		//Right
					grid.setPixel(antX, antY, sf::Color::White);
					antX -= 1;
					antOrientation--;
					break;

				case 3:		//Down
					grid.setPixel(antX, antY, sf::Color::White);
					antY += 1;
					antOrientation--;
					break;

				default:
					break;
			};
		}

		else	//If the ant is on a white square
		{
			switch (antOrientation)
			{
				case 0:		//Left
					grid.setPixel(antX, antY, sf::Color::Black);
					antX -= 1;
					antOrientation++;
					break;

				case 1:		//Up
					grid.setPixel(antX, antY, sf::Color::Black);
					antY += 1;
					antOrientation++;
					break;

				case 2:		//Right
					grid.setPixel(antX, antY, sf::Color::Black);
					antX += 1;
					antOrientation++;
					break;

				case 3:		//Down
					grid.setPixel(antX, antY, sf::Color::Black);
					antY -= 1;
					antOrientation = 0;
					break;

				default:
					break;
			};
		}

		if (slowdown)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
	}

	return 0;
}

int main()
{
	//Create and initialize the 2D array of heat map values
	for (int i = 0; i < GRID_SIZE; i++)
	{
		heatmapValues[i] = new int[GRID_SIZE];
	}

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			heatmapValues[i][j] = 0;
		}
	}

	//Initialize the grid size, color, texture, and sprite texture for the regular and heat map grids
	grid.create(GRID_SIZE, GRID_SIZE, sf::Color::White);
	gridTexture.loadFromImage(grid);
	gridSprite.setTexture(gridTexture);

	heatmapGrid.create(GRID_SIZE, GRID_SIZE, sf::Color::Blue);
	heatmapGridTexture.loadFromImage(heatmapGrid);
	heatmapGridSprite.setTexture(heatmapGridTexture);

	//Scale the sprites down 1000x1000 so the whole image is shown on the screen
	gridSprite.scale(sf::Vector2f(0.2, 0.2));
	heatmapGridSprite.scale(sf::Vector2f(0.2, 0.2));

	HANDLE threadHandle = CreateThread(NULL, 0, moveAnt, NULL, 0, NULL);		//Start up the thread using the function moveAnt()

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			//Toggle heat map
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::H)
			{
				showHeatmap = showHeatmap ? false : true;
			}

			//Toggle speed
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
			{
				slowdown = slowdown ? false : true;
			}
		}
		
		window.clear();

		//Draw the appropriate grid
		if (showHeatmap)
		{
			heatmapGridTexture.loadFromImage(heatmapGrid);
			window.draw(heatmapGridSprite);
		}

		else if (!showHeatmap)
		{
			gridTexture.loadFromImage(grid);
			window.draw(gridSprite);
		}

		window.display();
	}

	delete heatmapValues;			//Delete the array of heat map values
	CloseHandle(threadHandle);		//Kill the thread

	return 0;
}
