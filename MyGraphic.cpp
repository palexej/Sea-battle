#include "MyGraphic.h"
#include "CellArray.h"

MyGraphic::MyGraphic()
{
}


MyGraphic::~MyGraphic()
{
}


void MyGraphic::DrawEmptyField(RenderWindow& window, int offsetX)
{
	int xPos = 0, yPos = 0;;

	int rectSize = 50;

	int offset = 20;


	Font font; //шрифт 
	font.loadFromFile("..\\fonts\\CyrilicOld.TTF"); //загрузка шрифта

	Text text("", font, rectSize);
	text.setFillColor(Color(0, 0, 0));
	text.setStyle(sf::Text::Bold);
	int betweenRectOffset = 2;
	int maxFieldLenght = Cell::CELL_COUNT - 1;
	Color lightColor = sf::Color(159, 144, 176);
	//отображение букв, цифр и пустых полей
	for (int i = 0; i < maxFieldLenght; i++)
	{
		for (int j = 0; j < maxFieldLenght; j++)
		{
			if (i == 0 && j < maxFieldLenght)
			{
				string letterArray = " јЅ¬√ƒ≈∆«» ";

				text.setString(letterArray[j]);
				text.setPosition(i * rectSize + offsetX, j * rectSize);
				window.draw(text);
				continue;
			}
			if (j == 0 && i < maxFieldLenght)
			{
				text.setString(to_string(i));
				text.setPosition(i * rectSize + offsetX, j * rectSize);
				window.draw(text);
				continue;
			}
			if (i > 0 && j > 0)
			{
				xPos = j * rectSize;
				yPos = i * rectSize;


				RectangleShape rectangle(Vector2f(rectSize, rectSize));

				rectangle.setOutlineColor(lightColor);


				rectangle.setOutlineThickness(3);
				rectangle.move(xPos + offsetX, yPos + 5);
				window.draw(rectangle);
			}
		}
	}
}

//в зависимости от значени€ массива €чеек происходит закрашивание соответствующих €чеек
void MyGraphic::setShipsAndShots(CellArray cellArray, RenderWindow& window, int offsetX, bool isShipsShow)
{
	int xPos = 0, yPos = 0;

	int rectSize = 50;


	int betweenRectOffset = 2;
	int maxFieldLenght = Cell::CELL_COUNT - 1;
	Color lightColor = sf::Color(159, 144, 176);
	Color emptyCellColor = Color(159, 144, 176);

	Color shotCellColor = Color(255, 0, 0);
	Color notShipColor = Color(0, 255, 255);

	for (int i = 0; i < CellArray::CELL_COUNT - 1; i++)
	{
		for (int j = 0; j < CellArray::CELL_COUNT - 1; j++)
		{
			if (i > 0 && j > 0)
			{
				xPos = j * rectSize;
				yPos = i * rectSize;


				RectangleShape rectangle(Vector2f(rectSize, rectSize));

				rectangle.setOutlineColor(lightColor);
				rectangle.setOutlineThickness(3);


				if (cellArray.GetCellByIndex(i, j).getCellType() == "*")
				{
					rectangle.setFillColor(Color::Red);
				}
				else if (cellArray.GetCellByIndex(i, j).getCellType() == "$")
				{
					rectangle.setFillColor(Color::Green);
				}
				else if (cellArray.GetCellByIndex(i, j).getCellType() == "#")
				{
					rectangle.setFillColor(Color::Red);
				}
				else if (cellArray.GetCellByIndex(i, j).getCellType() == "?")
				{
					rectangle.setFillColor(Color::White);
				}
				else if (isShipsShow)
				{
					rectangle.setFillColor(Color::Yellow);
				}


				rectangle.move(xPos + offsetX, yPos + 5);
				window.draw(rectangle);
			}
		}
	}
}

void MyGraphic::ShowFieldWindow(bool isWindowActive, int playerOffset, int botOffset, CellArray playerCellArray,
                                CellArray botCellArray)
{

	RenderWindow window(VideoMode(1920, 1080), "Sea battle");
	
	if (isWindowActive)
	{

		// √лавный цикл приложени€. ¬ыполн€етс€, пока открыто окно
		while (window.isOpen())
		{
			// ќбрабатываем очередь событий в цикле
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					// тогда закрываем его
					window.close();
				}
				if (event.type == Event::LostFocus)
				{
					window.close(); //каждый раз при сворачивании консоли открываетс€ окно
				}
			}
			window.clear(Color(250, 220, 100));


			//отображение полей и расставленных кораблей
			DrawEmptyField(window, playerOffset);
			setShipsAndShots(playerCellArray, window, playerOffset, true);

			DrawEmptyField(window, botOffset);
			setShipsAndShots(botCellArray, window, botOffset, false);

			// ќтрисовка окна	
			window.display();
		}
	}
}
