#include <time.h>
#include<iostream>
#include<stdlib.h>
#include <SFML/Graphics.hpp>//""
#include"Meniu.h"
#include"Joc.h"


using namespace sf;


void setupMenu(Fereastra& menu, int n, int m, int nr_bombe)
{
	menu.background.setSize(Vector2f(400, 300));
	menu.background.setFillColor(Color::White);
	menu.background.setOutlineColor(Color::Black);
	menu.background.setOutlineThickness(2);
	menu.background.setPosition(100, 50);

	menu.title.setFont(menu.font_text);
	menu.title.setString("Minesweeper");
	menu.title.setCharacterSize(40);
	menu.title.setFillColor(Color::Black);
	menu.title.setPosition(180, 80);

	menu.matrice = AlocareMemorieMatrice(n, m, nr_bombe);
	Initializare(menu.matrice);
}

void Functie_pentru_tot(Fereastra& fereastra, Sprite s)
{
	int numarJocuriCastigateConsecutiv = 0;
	Event e;
	e.type = Event::EventType::MouseButtonPressed;
	int  w = 32;
	while (fereastra.app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(fereastra.app);
		int x = (abs(pos.x) - 64) / w;
		int y = (abs(pos.y) - 64) / w;

		Font font = ShowMenu(fereastra.app,fereastra.matrice, e, numarJocuriCastigateConsecutiv);
		int ok = 1;
		while (fereastra.app.pollEvent(e))
		{
			if (e.type == Event::Closed)

			{
				ElibereazaMemorieMatrice(fereastra.matrice);
				fereastra.app.close();
				ok = 2;
				break;
			}
			Click(fereastra.matrice, x, y, e);
		}
		if (ok == 2)
			break;

		if (x > 0 && y > 0 && y <=fereastra.matrice->m&&x <= fereastra.matrice->n&&fereastra.matrice->sgrid[x][y] == 9)
			ok = 0;

		Deseneaza(fereastra.app, fereastra.matrice, ok, w, s);
		fereastra.app.display();

		if (!ok)
		{
			char mesaj[] = "Ai pierdut!  :0";
			AfiseazaMesaj(fereastra.app, mesaj, e, font, fereastra.matrice);
			numarJocuriCastigateConsecutiv = 0;
		}

		if (aiCastigat(fereastra.matrice))
		{
			ok = 0;
			char mesaj[] = "Ai Castigat! Felicitari!  :0";
			Deseneaza(fereastra.app, fereastra.matrice, ok, w, s);
			AfiseazaMesaj(fereastra.app, mesaj, e, font, fereastra.matrice);
			numarJocuriCastigateConsecutiv++;
		}
	}

}

/*
void Functie_pentru_tot(RenderWindow &app, TOT*matrici, Sprite s)
{
	int numarJocuriCastigateConsecutiv = 0;
	Event e;
	e.type = Event::EventType::MouseButtonPressed;
	int  w = 32;
	while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app);
		int x = (abs(pos.x) -64)/ w;
		int y = (abs(pos.y) -64)/ w;
		
		Font font = ShowMenu(app, matrici,e, numarJocuriCastigateConsecutiv);
		int ok = 1;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)

			{
				ElibereazaMemorieMatrice(matrici);
				app.close();
				ok = 2;
				break;
			}
			Click(matrici, x, y, e);
		}
		if (ok == 2)
			break;

		if (x > 0 && y > 0 && y <= matrici->m&&x <= matrici->n&&matrici->sgrid[x][y] == 9)
			ok = 0;

		Deseneaza(app, matrici, ok, w, s);
		app.display();

		if (!ok)
		{
			char mesaj[] = "Ai pierdut!  :0";
			AfiseazaMesaj(app, mesaj, e,font,matrici);
			numarJocuriCastigateConsecutiv = 0;
		}

		if (aiCastigat(matrici))
		{
			ok = 0;
			char mesaj[] = "Ai Castigat! Felicitari!  :0";
			Deseneaza(app, matrici, ok, w, s);
			AfiseazaMesaj(app, mesaj, e,font,matrici);
			numarJocuriCastigateConsecutiv++;
			//break;
		}
	}
	
}
*/
/*
int main()
{
	int n = 10, m = 10, nr_bombe = 20;//m=25 maxim
	srand(time(0));
	RenderWindow app(VideoMode(40 * n, 40 * m), "Minesweeper!",sf::Style::Close);//, sf::Style::Close);
	//View view(sf::FloatRect(0.f, 0.f, 40*n, 40*m));
	//app.setView(view);

	TOT *matrici = AlocareMemorieMatrice(n, m, nr_bombe);//sgrid se vede si    grid nu se vede

	Texture t;
	t.loadFromFile("images/tiles.jpg");
	Sprite s(t);
	Initializare(matrici);
	//Test(grid, t);
	Functie_pentru_tot(app,matrici,s);
	//ElibereazaMemorieMatrice(matrici);
	
	return 0;
}*/

int main()
{
	int n = 11, m = 11, nr_bombe = 20;//m=25 maxim
	srand(time(0));
	Fereastra menu;
	menu.app.create(VideoMode(40 * n, 40 * m), "Minesweeper!", sf::Style::Close);

	
	menu.font_text = LoadFont();
	menu.texture_matrice.loadFromFile("images/tiles.jpg");
	

	setupMenu(menu, n, m, nr_bombe);
	Sprite s(menu.texture_matrice);
	//Test(grid, t);




	Functie_pentru_tot(menu, s);
	//ElibereazaMemorieMatrice(menu.matrice);

	return 0;
}