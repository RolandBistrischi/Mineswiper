#pragma once
#include <time.h>
#include <string>
#include<iostream>
#include<stdlib.h>
#include <SFML/Graphics.hpp>//""
#include"Joc.h"
#include "Custom.h"

using namespace sf;
using namespace std;


Font LoadFont()
{
	Font font;
	if (!font.loadFromFile("images/ArianaVioleta-dz2K.ttf"))
	{
		return font;
	}
	return font;
}

RectangleShape CreateMenuBackground(int n, int m, float thickness)
{
	RectangleShape menuBackground(Vector2f(n, m));
	menuBackground.setFillColor(Color::White);
	menuBackground.setOutlineColor(Color::Blue);
	menuBackground.setOutlineThickness(thickness);
	return menuBackground;
}

Text CreateOption(Font& font, const std::string& text, int n)
{
	Text option(text, font, n);
	option.setFillColor(Color::Black);
	return option;
}
/*
void UpdateWindowSize(RenderWindow& window, RectangleShape& menuBackground, Text& title, Text& option1, Text& option2, Text& option3, Text& option4,  RectangleShape& resetButton, Text& resetButtonText)
{
	Vector2u windowSize = window.getSize();
	menuBackground.setScale(Vector2f(windowSize.x / 150.0f, windowSize.y / 300.0f));
	float ratio = windowSize.x / 150.0f;

	title.setCharacterSize(20 + ratio);
	option1.setCharacterSize(15 + ratio);
	option2.setCharacterSize(15 + ratio);
	option3.setCharacterSize(15 + ratio);
	option4.setCharacterSize(15 + ratio);

	title.setPosition(0, 0);
	option1.setPosition(ratio, 30 + ratio);
	option2.setPosition(ratio, 60 + ratio);
	option3.setPosition(ratio, 90 + ratio);
	option4.setPosition(ratio, 120 + ratio);


	resetButton.setPosition(60+ratio, ratio);
	resetButtonText.setCharacterSize(15 + ratio);
	resetButtonText.setPosition(resetButton.getPosition() + Vector2f(1, 1));

}*/


void UpdateWindowSize(float ratio, RectangleShape& Button, Text& text, int size, int pozitionx, int pozitiony)
{
	Button.setPosition(pozitionx + ratio, pozitiony + ratio);
	text.setCharacterSize(size + ratio);
	text.setPosition(Button.getPosition() + Vector2f(10, 5));
}

/*void RenderContent(RenderWindow& window, RectangleShape& menuBackground, Text& title, Text& option1, Text& option2, Text& option3, Text& option4, RectangleShape& resetButton, Text& resetButtonText)
{

	window.clear(Color::White);
	window.draw(menuBackground);
	window.draw(title);
	window.draw(option1);
	window.draw(option2);
	window.draw(option3);
	window.draw(option4);
	window.draw(resetButton);
	window.draw(resetButtonText);
	//window.display();
}*/

void RenderContent(RenderWindow& window, RectangleShape& Button, Text& text)
{
	window.draw(Button);
	window.draw(text);
}

void RenderStatistics(RenderWindow& window, Text &text, Font& font, int numarCastigate)
{
	text.setFont(font);
	text.setCharacterSize(20);
	text.setString("Numarul de jocuri castigate consecutiv  " + to_string(numarCastigate));
	text.setPosition(140, 0);
	text.setFillColor(Color::White);
	text.setOutlineColor(Color::Black);
	text.setOutlineThickness(3);
}

Vector2f HandleEvents(RenderWindow& window, RectangleShape& resetButton, Text& resetText, TOT* matrici, Event event)
{
	if (event.type == Event::Closed)
		window.close();

	Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

	if (event.type == Event::MouseButtonPressed&&event.key.code == Mouse::Left)
	{
		//std::cout << "Clicked position mousePos: (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
		if (resetText.getGlobalBounds().contains(mousePos) || resetButton.getGlobalBounds().contains(mousePos))
		{
			return mousePos;//false				
			//window.clear();
		}
	}
	return Vector2f(-1, -1);//true
}

void AfiseazaMesaj(RenderWindow &app, char mesaj[], Event e, Font font, TOT*matrici)
{
	RenderWindow pierdut(VideoMode(500, 150), mesaj);

	RectangleShape resetButton = CreateMenuBackground(60, 50, 2);///60 latime, 50 inaltime 
	resetButton.setPosition(Vector2f(200, 50));
	Text resetButtonText = CreateOption(font, "Reset", 20);
	resetButtonText.setPosition(resetButton.getPosition() + Vector2f(10, 10));

	Vector2f clickPos;

	while (pierdut.isOpen())
	{
		Event pier;
		while (pierdut.pollEvent(pier))
		{

			if (pier.type == Event::Closed || e.type == Event::Closed)
			{
				Initializare(matrici);
				pierdut.close();
				break;
			}

			clickPos = HandleEvents(pierdut, resetButton, resetButtonText, matrici, pier);
			if (clickPos.x != -1)
			{
				Initializare(matrici);
				pierdut.close();
				return;
			}
		}
		pierdut.clear();
		pierdut.draw(resetButton);
		pierdut.draw(resetButtonText);
		pierdut.display();
		//std::cout << "Clicked position: (" << clickPos.x << ", " << clickPos.y << ")" << std::endl;

	}
}





/*
void OpenCustomWindow(RenderWindow& customWindow, Font& font, Text& nLabel, Text& mLabel, Text& errorLabel, Text& nText, Text& mText, Text& bLabel, Text& bText, RectangleShape& okButton, Text& okButtonText) {
	customWindow.create(VideoMode(300, 150), "Custom");

	Text title = CreateOption(font, "Introdu dimensiunile matricei:", 20);
	title.setPosition(20, 20);

	nLabel.setPosition(20, 60);
	mLabel.setPosition(20, 90);
	errorLabel.setPosition(20, 120);

	nText.setPosition(50, 60);
	mText.setPosition(50, 90);
	bText.setPosition(80, 120);

	bLabel.setPosition(20, 120);

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
					customWindow.close();
				}
			}
		}
	}
}

void CustomButtonPressed(RenderWindow& window, RectangleShape& Button, Text text, TOT*& matrici, Event e, int& castigate)
{
	Vector2f clickPos = Vector2f(-1, -1);
	clickPos = HandleEvents(window, Button, text, matrici, e);
	if (text.getGlobalBounds().contains(clickPos) || Button.getGlobalBounds().contains(clickPos))
	{
		// Deschidem o fereastră separată pentru a permite utilizatorului să introducă dimensiunile matricei
		RenderWindow customWindow;
		Font font = LoadFont();

		Text nLabel = CreateOption(font, "N: ", 16);
		Text mLabel = CreateOption(font, "M: ", 16);
		Text errorLabel = CreateOption(font, "", 16);
		Text nText = CreateOption(font, "9", 16);
		Text mText = CreateOption(font, "9", 16);
		Text bLabel = CreateOption(font, "Bombe: ", 16);
		Text bText = CreateOption(font, "10", 16);

		RectangleShape okButton = CreateMenuBackground(45, 30, 2);
		Text okButtonText = CreateOption(font, "OK", 15);

		OpenCustomWindow(customWindow, font, nLabel, mLabel, errorLabel, nText, mText, bLabel, bText, okButton, okButtonText);



			// Obținem valorile introduse în fereastră
			int n = stoi(nText.getString());
		int m = stoi(mText.getString());
		int b = stoi(bText.getString());

		// Validăm valorile introduse
		if (n <= 0 || m <= 0)
		{
			errorLabel.setString("Dimensiunile trebuie sa fie pozitive!");
			return;
		}
		if (b >= n * m)
		{
			errorLabel.setString("Prea multe bombe!");
			return;
		}

		// Cream matricea cu valorile introduse
		TOT* newMatrix = new TOT[n * m];
		for (int i = 0; i < n * m; i++)
		{
			newMatrix[i].val = '0';
			newMatrix[i].descoperit = false;
			newMatrix[i].flag = false;
			newMatrix[i].bomba = false;
			newMatrix[i].expus = false;
			newMatrix[i].bombeVecine = 0;
		}
		for (int i = 0; i < b; i++)
		{
			int x = rand() % (n * m);
			if (newMatrix[x].bomba)
			{
				i--;
				continue;
			}
			newMatrix[x].bomba = true;
			// Incrementăm bombele vecine pentru fiecare celulă vecină a celulei cu bombă
			for (int j = 0; j < 8; j++)
			{
				int vecin = x + dx[j] * m + dy[j];
				if (vecin < 0 || vecin >= n * m) continue;
				if (x % m == 0 && vecin % m == m - 1) continue;
				if (x % m == m - 1 && vecin % m == 0) continue;
				if (newMatrix[vecin].bomba) continue;
				newMatrix[vecin].bombeVecine++;
			}
		}

		// Adăugăm noua matrice la lista de matrici și resetăm scorul
		AddMatrix(matrici, newMatrix, n, m, b);
		castigate = 0;
	}

}

void MainMenu(RenderWindow& window, TOT*& matrici, int& castigate)
{
	Font font = LoadFont();
	Text title = CreateOption(font, "Minesweeper", 50);
	title.setPosition(250 - title.getGlobalBounds().width / 2, 40);


	RectangleShape customButton = CreateMenuBackground(200, 50);
	Text customButtonText = CreateOption(font, "Personalizat", 25);
	customButtonText.setPosition(customButton.getPosition().x + 10, customButton.getPosition().y + 5);
	customButton.setPosition(250 - customButton.getSize().x / 2, 200);

	RectangleShape easyButton = CreateMenuBackground(200, 50);
	Text easyButtonText = CreateOption(font, "Usor", 25);
	easyButtonText.setPosition(easyButton.getPosition().x + 50, easyButton.getPosition().y + 5);
	easyButton.setPosition(250 - easyButton.getSize().x / 2, 300);

	RectangleShape mediumButton = CreateMenuBackground(200, 50);
	Text mediumButtonText = CreateOption(font, "Mediu", 25);
	mediumButtonText.setPosition(mediumButton.getPosition().x + 40, mediumButton.getPosition().y +



}*/






void CustomButtonPressed(RenderWindow& window, RectangleShape& Button, Text text, TOT*& matrici, Event e, int& castigate)
{
	// Deschidem o fereastră separată pentru a permite utilizatorului să introducă dimensiunile matricei
	RenderWindow customWindow(VideoMode(400, 400), "Custom");
	Font font = LoadFont();

	Text title = CreateOption(font, "Introdu dimensiunile matricei:", 30);
	title.setPosition(20, 20);

	Text nLabel = CreateOption(font, "N: ", 25);
	nLabel.setPosition(20, 60);

	Text mLabel = CreateOption(font, "M: ", 25);
	mLabel.setPosition(20, 90);

	Text errorLabel = CreateOption(font, "", 25);
	errorLabel.setPosition(20, 120);

	Text nText = CreateOption(font, "9", 25);
	nText.setPosition(50, 60);

	Text mText = CreateOption(font, "9", 25);
	mText.setPosition(50, 90);

	Text bLabel = CreateOption(font, "Bombe: ", 25);
	bLabel.setPosition(20, 120);

	Text bText = CreateOption(font, "10", 25);
	bText.setPosition(80, 120);

	RectangleShape okButton = CreateMenuBackground(70, 50, 2);
	Text okButtonText = CreateOption(font, "OK", 1);

	UpdateWindowSize(1, okButton, okButtonText, 30, 250 - okButton.getSize().x, 120);

	while (customWindow.isOpen())
	{
		Vector2f clickPos = Vector2f(-1, -1);
		clickPos = HandleEvents(window, Button, text, matrici, e);
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
						/*int n = stoi(nText.getString());
						int m = stoi(mText.getString());
						int nr_bombe = stoi(bText.getString());*/
						int n = std::stoi(nText.getString().toAnsiString());
						int m = std::stoi(mText.getString().toAnsiString());
						int nr_bombe = std::stoi(bText.getString().toAnsiString());

						if (n < 5 || m < 5)
							errorLabel.setString("Dimensiunile trebuie sa fie mai mari sau egale cu 5.");
						else if (n * m <= 10)
							errorLabel.setString("Numarul total de celule trebuie sa fie mai mare decat 10.");
						else
						{
							// Închidem fereastra și actualizăm dimensiunile matricei
							matrici = RedimensionareMatrice(matrici, n, m, nr_bombe);
							if (matrici->n < 10 || matrici->m < 10)
								window.create(VideoMode(40 * 10, 40 * 10), "Minesweeper!", sf::Style::Close);
							else
								window.create(VideoMode(40 * matrici->n, 40 * matrici->m), "Minesweeper!", sf::Style::Close);
							Initializare(matrici);
							castigate = 0;
							customWindow.close();
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



void ButtonPressed(RenderWindow& window, RectangleShape &Button, Text text, TOT*& matrici, Event e, int &castigate, int n, int m, int nr_bombe)
{
	Vector2f clickPos = Vector2f(-1, -1);
	clickPos = HandleEvents(window, Button, text, matrici, e);
	if (text.getGlobalBounds().contains(clickPos) || Button.getGlobalBounds().contains(clickPos))
	{
		if (text.getString() == "Custom")
		{
			//CustomButtonPressed(window, matrici, n, m, nr_bombe);
			CustomButtonPressed(window, Button, text, matrici, e, castigate);

		}
		else
		{
			matrici = RedimensionareMatrice(matrici, n, m, nr_bombe);
			if (matrici->n < 10 || matrici->m < 10)

				window.create(VideoMode(40 * 10, 40 * 10), "Minesweeper!", sf::Style::Close);
			else
				window.create(VideoMode(40 * matrici->n, 40 * matrici->m), "Minesweeper!", sf::Style::Close);

			Initializare(matrici);
			//RedimensionareFereastra(window, 9, 9);
			//window.setSize(sf::Vector2u(40 * 9, 40 * 9));
			//window.setView();
			//window(VideoMode(40 * 9, 40 * 9), "Minesweeper!", sf::Style::Close);
			castigate = 0;
		}
	}
}
/*
void CustomButtonPressed(RenderWindow& window, RectangleShape& Button, Text text, TOT*& matrici, Event e, int& castigate)
{
	Vector2f clickPos = Vector2f(-1, -1);
	clickPos = HandleEvents(window, Button, text, matrici, e);
	if (text.getGlobalBounds().contains(clickPos) || Button.getGlobalBounds().contains(clickPos))
	{
		// Afisam un dialog pentru a citi dimensiunile matricii
		int n = 0, m = 0, nr_bombe = 0;
		bool valid = false;

		while (!valid) {
			std::string input_n = "", input_m = "", input_nr_bombe = "";
			n = 0; m = 0; nr_bombe = 0;
			input_n = InputDialog("Introduceti numarul de linii:", "Custom", "10");
			input_m = InputDialog("Introduceti numarul de coloane:", "Custom", "10");
			input_nr_bombe = InputDialog("Introduceti numarul de bombe:", "Custom", "10");

			try {
				n = std::stoi(input_n);
				m = std::stoi(input_m);
				nr_bombe = std::stoi(input_nr_bombe);
			}
			catch (std::exception& e) {
				// daca conversia a esuat, afisam un mesaj si reluam citirea
				MessageBox(NULL, "Introduceti un numar valid!", "Eroare", MB_ICONERROR | MB_OK);
				continue;
			}

			if (n < 5 || m < 5 || nr_bombe < 1 || nr_bombe > n * m / 2) {
				MessageBox(NULL, "Introduceti dimensiuni si numar de bombe valide!", "Eroare", MB_ICONERROR | MB_OK);
			}
			else {
				valid = true;
			}
		}

		// Redimensionam matricea si afisam jocul
		matrici = RedimensionareMatrice(matrici, n, m, nr_bombe);
		if (matrici->n < 10 || matrici->m < 10) {
			window.create(VideoMode(40 * 10, 40 * 10), "Minesweeper!", sf::Style::Close);
		}
		else {
			window.create(VideoMode(40 * matrici->n, 40 * matrici->m), "Minesweeper!", sf::Style::Close);
		}

		Initializare(matrici);
		castigate = 0;
	}
}
*/



Font ShowMenu(RenderWindow& window, TOT*& matrici, Event e, int &castigate)
{
	Font font = LoadFont();
	RectangleShape menuBackground = CreateMenuBackground(45, 30, 2);
	Text title = CreateOption(font, "Meniu", 10);


	Vector2u windowSize = window.getSize();
	float ratio = windowSize.x / 150.0f;


	RectangleShape Option1Button = CreateMenuBackground(45, 30, 2);
	Text option1 = CreateOption(font, "Usor", 16);

	RectangleShape Option2Button = CreateMenuBackground(45, 30, 2);
	Text option2 = CreateOption(font, "Mediu", 16);

	RectangleShape Option3Button = CreateMenuBackground(45, 30, 2);
	Text option3 = CreateOption(font, "Greu", 16);

	RectangleShape Option4Button = CreateMenuBackground(45, 30, 2);
	Text option4 = CreateOption(font, "Custom", 16);

	RectangleShape resetButton = CreateMenuBackground(45, 30, 2);
	Text resetButtonText = CreateOption(font, "Reset", 15);

	Text StatisticiText = CreateOption(font, "Statistici", 20);


	UpdateWindowSize(ratio, menuBackground, title, 20, 0, 0);
	UpdateWindowSize(ratio, Option1Button, option1, 15, 0, 30);
	UpdateWindowSize(ratio, Option2Button, option2, 15, 0, 60);
	UpdateWindowSize(ratio, Option3Button, option3, 15, 0, 90);
	UpdateWindowSize(ratio, Option4Button, option4, 15, 0, 120);
	UpdateWindowSize(ratio, resetButton, resetButtonText, 15, 60, 0);

	ButtonPressed(window, resetButton, resetButtonText, matrici, e, castigate, matrici->n, matrici->m, matrici->nr_bombe);
	ButtonPressed(window, Option1Button, option1, matrici, e, castigate, 9, 9, 10);
	ButtonPressed(window, Option2Button, option2, matrici, e, castigate, 16, 16, 40);
	ButtonPressed(window, Option3Button, option3, matrici, e, castigate, 30, 16, 99);
	ButtonPressed(window, Option4Button, option4, matrici, e, castigate, 30, 16, 99);

	RenderStatistics(window, StatisticiText, font, castigate);

	window.clear(Color::White);
	RenderContent(window, menuBackground, title);
	RenderContent(window, Option1Button, option1);
	RenderContent(window, Option2Button, option2);
	RenderContent(window, Option3Button, option3);
	RenderContent(window, Option4Button, option4);
	RenderContent(window, resetButton, resetButtonText);

	window.draw(StatisticiText);
	return font;
}
