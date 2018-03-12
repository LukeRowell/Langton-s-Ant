/***************************************************************
AUTHOR: Luke Rowell
LAST MODIFIED: 3/12/2018
DESCRIPTION: Simulation of Langton's Ant.

CONTROLS:		h	-	activates heat map view
				n	-	activates black and white view
				o	-	turns off rendering (increases speed)
***************************************************************/
#include <SFML/Graphics.hpp>

int main()
{
	const int GRID_SIZE = 800;
	int ITERATIONS_PER_FRAME = 100;
	int antX = GRID_SIZE / 2;
	int antY = GRID_SIZE / 2;
	int antOrientation = 1;
	float heatmapValue = 0.0f;
	bool showHeatmap = false;
	bool renderVisuals = true;
	sf::RenderWindow window(sf::VideoMode(GRID_SIZE, GRID_SIZE), "Langton's Ant");
	sf::Image grid;
	sf::Texture gridTexture;
	sf::Sprite gridSprite;
	sf::Image heatmapGrid;
	sf::Texture heatmapGridTexture;
	sf::Sprite heatmapGridSprite;
	sf::Color red(255, 0, 0, 255);
	sf::Color yellow(255, 255, 0, 255);
	sf::Color green(0, 255, 0, 255);
	sf::Color cyan(0, 255, 255, 255);
	sf::Color blue(0, 0, 255, 255);

	int** heatmapValues = new int* [GRID_SIZE];

	for (int i = 0; i < GRID_SIZE; i++)
	{
		heatmapValues[i] = new int[GRID_SIZE];
	}

	grid.create(GRID_SIZE, GRID_SIZE, sf::Color::White);
	gridTexture.loadFromImage(grid);
	gridSprite.setTexture(gridTexture);

	heatmapGrid.create(GRID_SIZE, GRID_SIZE, blue);
	heatmapGridTexture.loadFromImage(heatmapGrid);
	heatmapGridSprite.setTexture(heatmapGridTexture);

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			heatmapValues[i][j] = 0;
		}
	}

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
			{
				showHeatmap = true;
				renderVisuals = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
			{
				showHeatmap = false;
				renderVisuals = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
			{
				renderVisuals = false;
			}
		}

		window.clear();
		
		for (int i = 0; i < ITERATIONS_PER_FRAME; i++)
		{
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

			heatmapValues[antX][antY]++;
			heatmapValue = (float)heatmapValues[antX][antY] / 100.0f;

			if (heatmapValue > 1)
			{

			}

			else
			{
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

				else if(heatmapValue > 0.8 && heatmapValue <= 0.4)		//Red
				{
					heatmapGrid.setPixel(antX, antY, red);
				}
			}

			if (showHeatmap && renderVisuals)
			{
				heatmapGridTexture.loadFromImage(heatmapGrid);
				window.draw(heatmapGridSprite);
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

			if (!showHeatmap && renderVisuals)
			{
				gridTexture.loadFromImage(grid);
				window.draw(gridSprite);
			}
		}

		window.display();
	}

	delete heatmapValues;

	return 0;
}