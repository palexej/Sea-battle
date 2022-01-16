#include "MyGraphic.h"
#include "CellArray.h"

MyGraphic::MyGraphic()
{
}


MyGraphic::~MyGraphic()
{
}


void MyGraphic::DrawEmptyField(RenderWindow& window,int offsetX)
{
	int xPos = 0, yPos = 0;;

	int rectSize = 50;

	int offset = 20;


	Font font; //шрифт 
	font.loadFromFile("..\\fonts\\CyrilicOld.TTF"); //передаем нашему шрифту файл шрифта

	Text text("", font, rectSize);
	text.setFillColor(Color(0, 0, 0));
	text.setStyle(sf::Text::Bold);
	int betweenRectOffset = 2;
	int maxFieldLenght = Cell::CELL_COUNT - 1;
	Color lightColor = sf::Color(159, 144, 176);
	for (int i = 0; i < maxFieldLenght; i++)
	{
		for (int j = 0; j < maxFieldLenght; j++)
		{
			if (i == 0 && j < maxFieldLenght)
			{
				string letterArray = " АБВГДЕЖЗИК";

				text.setString(letterArray[j]);
				text.setPosition(i * rectSize+ offsetX, j * rectSize);
				window.draw(text);
				continue;
			}
			if (j == 0 && i < maxFieldLenght)
			{
				text.setString(to_string(i));
				text.setPosition(i * rectSize+ offsetX, j * rectSize);
				window.draw(text);
				continue;
			}
			if (i > 0 && j > 0)
			{
				xPos = j * rectSize;
				yPos = i * rectSize;


				RectangleShape rectangle(Vector2f(rectSize, rectSize));

				rectangle.setOutlineColor(lightColor);

				//rectangle.setFillColor()

				rectangle.setOutlineThickness(3);
				rectangle.move(xPos+ offsetX, yPos + 5);
				window.draw(rectangle);
			}
		}
	}
}


void MyGraphic::setShipsAndShots(CellArray cellArray, RenderWindow& window,int offsetX)
{
	int xPos = 0, yPos = 0;

	int rectSize = 50;


	int betweenRectOffset = 2;
	int maxFieldLenght = Cell::CELL_COUNT - 1;
	Color lightColor = sf::Color(159, 144, 176);
	Color emptyCellColor = Color(159, 144, 176);

	Color shotCellColor = Color(255, 0, 0);
	Color notShipColor = Color(0, 255, 255);

	for (int i = 0; i < CellArray::CELL_COUNT-1; i++)
	{
		for (int j = 0; j < CellArray::CELL_COUNT-1; j++)
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
				else
				{
					rectangle.setFillColor(Color::White);
				}


				rectangle.move(xPos+ offsetX, yPos + 5);
				window.draw(rectangle);
			}
		}
	}
}

void MyGraphic::ShowFieldWindow(bool isWindowActive,int playerOffset,int botOffset, CellArray playerCellArray,CellArray botCellArray)
{
	RenderWindow window(VideoMode(1920, 1080), "Морской бой");
	//RenderWindow window(VideoMode(1000, 1000), "SFML Works!");
	if (isWindowActive)
	{
		// Объект, который, собственно, является главным окном приложения


		// Главный цикл приложения. Выполняется, пока открыто окно
		while (window.isOpen())
		{
			// Обрабатываем очередь событий в цикле
			Event event;
			while (window.pollEvent(event))
			{
				// Пользователь нажал на «крестик» и хочет закрыть окно?
				if (event.type == Event::Closed)
				{
					// тогда закрываем его
					window.close();
				}
				if (event.type == Event::LostFocus)
				{
					window.close(); //каждый раз при сворачивании консоли открывается окно
					//window.setActive(false);
					//window.setVisible(false);
				}
			}
			window.clear(Color(250, 220, 100));

			DrawEmptyField(window,playerOffset);
			setShipsAndShots(playerCellArray, window,playerOffset);

			DrawEmptyField(window, botOffset);
			setShipsAndShots(botCellArray, window, botOffset);

			// Отрисовка окна	
			window.display();
			//window.close();
		}
	}
}
