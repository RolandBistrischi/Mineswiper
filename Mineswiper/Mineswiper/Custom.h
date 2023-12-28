#pragma once
#include <string>
#include <time.h>
#include<iostream>
#include<stdlib.h>
#include <SFML/Graphics.hpp>//""
#include"Meniu.h"
#include"Joc.h"


/*
void CustomButtonPressed(RenderWindow& window, RectangleShape& Button, Text text, TOT*& matrici, Event e, int& castigate)
{
	Vector2f clickPos = Vector2f(-1, -1);
	clickPos = HandleEvents(window, Button, text, matrici, e);
	if (text.getGlobalBounds().contains(clickPos) || Button.getGlobalBounds().contains(clickPos))
	{
		// Deschidem o fereastră separată pentru a permite utilizatorului să introducă dimensiunile matricei
		RenderWindow customWindow(VideoMode(300, 150), "Custom");

		Font font = LoadFont();

		Text title = CreateOption(font, "Introdu dimensiunile matricei:", 20);
		title.setPosition(20, 20);

		Text nLabel = CreateOption(font, "N: ", 16);
		nLabel.setPosition(20, 60);

		Text mLabel = CreateOption(font, "M: ", 16);
		mLabel.setPosition(20, 90);

		Text errorLabel = CreateOption(font, "", 16);
		errorLabel.setPosition(20, 120);

		Text nText = CreateOption(font, "9", 16);
		nText.setPosition(50, 60);

		Text mText = CreateOption(font, "9", 16);
		mText.setPosition(50, 90);

		Text bLabel = CreateOption(font, "Bombe: ", 16);
		bLabel.setPosition(20, 120);

		Text bText = CreateOption(font, "10", 16);
		bText.setPosition(80, 120);


		RectangleShape okButton = CreateMenuBackground(45, 30, 2);
		Text okButtonText = CreateOption(font, "OK", 15);
		okButtonText.setPosition(okButton.getPosition().x + 10, okButton.getPosition().y + 5);

		UpdateWindowSize(1, okButton, okButtonText, 15, 0, 0);
		okButton.setPosition(250 - okButton.getSize().x, 120);

		while (customWindow.isOpen())
		{
			Event customEvent;
			while (customWindow.pollEvent(customEvent))
			{
				if (customEvent.type == Event::Closed)
					customWindow.close();
				if (customEvent.type == Event::KeyPressed && customEvent.key.code == Keyboard::Escape)
					customWindow.close();
				if (customEvent.type == Event::MouseButtonPressed && customEvent.key.code == Mouse::Left)
				{
					Vector2f mousePos = customWindow.mapPixelToCoords(Mouse::getPosition(customWindow));
					if (okButtonText.getGlobalBounds().contains(mousePos) || okButton.getGlobalBounds().contains(mousePos))
					{
						// Verificăm dacă dimensiunile introduse sunt valabile
						try {
							int n = stoi(nText.getString());
							int m = stoi(mText.getString());
							int nr_bombe = stoi(bText.getString());

							if (n < 5 || m < 5)
								errorLabel.setString("Dimensiunile trebuie sa fie mai mari sau egale cu 5.");
							else if (n * m <= 10)
								errorLabel.setString("Numarul total de celule trebuie sa fie mai mare decat 10.");
							else 
							{
								// Închidem fereastra și actualizăm dimensiunile matricei
								customWindow.close();
								matrici = RedimensionareMatrice(matrici, n, m, nr_bombe);
								if (matrici->n < 10 || matrici->m < 10)
									window.create(VideoMode(40 * 10, 40 * 10), "Minesweeper!", sf::Style::Close);
								else
									window.create(VideoMode(40 * matrici->n, 40 * matrici->m), "Minesweeper!", sf::Style::Close);
								Initializare(matrici);
								castigate = 0;
							}
						}
						catch (invalid_argument)
						{
							// Dacă conversia la int a eșuat, afișăm un mesaj de eroare
							errorLabel.setString("Introdu dimensiuni valide!");
						}
					}
				}
				if (customEvent.type == Event::TextEntered)
				{
					if (customEvent.text.unicode >= '0' && customEvent.text.unicode <= '9')
					{
						if (nText.getGlobalBounds().contains(clickPos))
						{
							nText.setString(nText.getString() + static_cast<char>(customEvent.text.unicode));
						}
						else if (mText.getGlobalBounds().contains(clickPos))
						{
							mText.setString(mText.getString() + static_cast<char>(customEvent.text.unicode));
						}
						else
							if (bText.getGlobalBounds().contains(clickPos))
							{
								bText.setString(bText.getString() + static_cast<char>(customEvent.text.unicode));
							}
					}
					else if (customEvent.text.unicode == 8) // BACKSPACE
					{
						if (nText.getGlobalBounds().contains(clickPos))
						{
							string str = nText.getString();
							if (str.length() > 0)
							{
								str.pop_back();
								nText.setString(str);
							}
						}
						else if (mText.getGlobalBounds().contains(clickPos))
						{
							string str = mText.getString();
							if (str.length() > 0)
							{
								str.pop_back();
								mText.setString(str);
							}
						}
						else
							if (bText.getGlobalBounds().contains(clickPos))
							{
								string str = bText.getString();
								if (str.length() > 0)
								{
									str.pop_back();
									bText.setString(str);
								}
							}
					}
				}
			}

			customWindow.clear(Color(192, 192, 192, 255));
			customWindow.draw(title);
			customWindow.draw(nLabel);
			customWindow.draw(mLabel);
			customWindow.draw(bLabel);
			customWindow.draw(errorLabel);
			customWindow.draw(nText);
			customWindow.draw(mText);
			customWindow.draw(bText);
			customWindow.draw(okButton);
			customWindow.draw(okButtonText);
			customWindow.display();
		}
	}
}
*/


