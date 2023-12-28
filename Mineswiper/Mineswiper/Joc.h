#pragma once
#include <time.h>
#include<iostream>
#include<stdlib.h>
#include <SFML/Graphics.hpp>//""
#include"Meniu.h"

using namespace std;
using namespace sf;
//int k = 1;


typedef struct structura
{
	int **sgrid;
	int **grid;
	int n, m, nr_bombe;
}TOT;

typedef struct  Button {
	RectangleShape shape;
	Text label;
	
	int inaltime, lungime;
	float x, y;

} Button;

typedef struct Fereastra {
	RenderWindow app;
	RectangleShape background;
	Text title;
	std::vector<Button> buttons;
	int inaltime, lungime;
	TOT *matrice;
	Font font_text;
	Texture texture_matrice;
}Fereastra;



/*
void modificare(int x, int y, TOT*matrice)
{
	matrice->sgrid[x][y] = matrice->grid[x][y];

	if (matrice->grid[x - 1][y] != 0)
		matrice->sgrid[x - 1][y] = matrice->grid[x - 1][y];

	if (matrice->grid[x + 1][y] != 0)
		matrice->sgrid[x + 1][y] = matrice->grid[x + 1][y];

	if (matrice->grid[x][y - 1] != 0)
		matrice->sgrid[x][y - 1] = matrice->grid[x][y - 1];

	if (matrice->grid[x][y + 1] != 0)
		matrice->sgrid[x][y + 1] = matrice->grid[x][y + 1];
}*/

void modificare(int x, int y, TOT*matrice)
{
	/*int dx[] = { -1, 1, 0, 0 };
	  int dy[] = { 0, 0, -1, 1 };*/

	int dx[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
	int dy[] = { 0, 0, -1, 1, -1, 1, -1, 1 };


	matrice->sgrid[x][y] = matrice->grid[x][y];
	for (int i = 0; i < 8; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx > 0 && nx <= matrice->n && ny > 0 && ny <= matrice->m && matrice->grid[nx][ny] != 0)
			matrice->sgrid[nx][ny] = matrice->grid[nx][ny];
	}
}

/*
int valid(int stx[100], int sty[100], int x, int y)
{
	for (int i = 1; i < k; i++)
		if (stx[i] == x && sty[i] == y)
			return 0;
	return 1;
}


//succesor bun
int succesor(int stx[100], int sty[100], int n, int m, int grid[12][12], int sgrid[12][12])
{
	int ok = 0, x, y;
	if (grid[stx[k] - 1][sty[k]] == 0 && stx[k] - 1 > 0 && grid[stx[k] - 1][sty[k]] != sgrid[stx[k] - 1][sty[k]])
	{
		x = stx[k] - 1;
		y = sty[k];
		if (valid(stx, sty, x, y))
		{
			ok = 1;
			k++;
			stx[k] = x;
			sty[k] = y;
		}
	}

	if (grid[stx[k]][sty[k] - 1] == 0 && sty[k] - 1 > 0 && grid[stx[k]][sty[k] - 1] != sgrid[stx[k]][sty[k] - 1])
	{
		x = stx[k];
		y = sty[k] - 1;
		if (valid(stx, sty, x, y))
		{
			ok = 1;
			k++;
			stx[k] = x;
			sty[k] = y;
		}
	}

	if (grid[stx[k] + 1][sty[k]] == 0 && stx[k] + 1 < n  && grid[stx[k] + 1][sty[k]] != sgrid[stx[k] + 1][sty[k]])
	{
		x = stx[k] + 1;
		y = sty[k];
		if (valid(stx, sty, x, y))
		{
			ok = 1;
			k++;
			stx[k] = x;
			sty[k] = y;
		}
	}

	if (grid[stx[k]][sty[k] + 1] == 0 && sty[k] + 1 < n  && grid[stx[k]][sty[k] + 1] != sgrid[stx[k]][sty[k] + 1])
	{
		x = stx[k];
		y = sty[k] + 1;
		if (valid(stx, sty, x, y))
		{
			ok = 1;
			k++;
			stx[k] = x;
			sty[k] = y;
		}
	}
	if (ok)
		return 1;
	else
		return 0;
}
//   varianta cu backtracking iterativa
void CautaGoale(int sgrid[12][12], int  grid[12][12], int  x, int  y,int n,int m)
{
	int stx[100], sty[100];
	k = 1;
	stx[k] = x;
	sty[k] = y;
	if (grid[x][y] != 0)
		k = -1;

	while (k > 0)
	{
		int as = 1;
		while (as)
		{
			as = succesor(stx, sty, n, m, grid, sgrid);
		}
		modificare(stx[k], sty[k], grid, sgrid);
		k--;
	}

}*/

void CautaGoale(int x, int y, TOT*matrice)
{
	if (x < 1 || x >= matrice->n || y < 1 || y >= matrice->m || matrice->grid[x][y] || matrice->sgrid[x][y] == matrice->grid[x][y])
		return;
	modificare(x, y, matrice);
	CautaGoale(x - 1, y, matrice);
	CautaGoale(x + 1, y, matrice);
	CautaGoale(x, y - 1, matrice);
	CautaGoale(x, y + 1, matrice);
}

void Test(int grid[12][12], Texture t)
{

	/*int grid[12][12] =
	{
	0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,1,0,0,0,0,0,0,
	0,0,0,2,9,2,0,1,1,1,0,0,
	0,1,1,2,9,3,1,2,9,1,0,0,
	0,9,2,1,2,3,9,3,2,2,1,0,
	0,9,2,0,1,9,3,9,1,1,9,0,
	0,1,1,0,1,1,2,1,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,1,1,1,1,0,0,0,0,
	0,0,1,9,2,3,9,2,0,0,0,0,
	0,0,1,1,2,9,9,2,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,
	};
	int sgrid[12][12];*/

	int w = 32;
	RenderWindow vazut(VideoMode(400, 400), "Minesweeper capcane");
	Sprite v(t);
	while (vazut.isOpen())
	{
		Event e;
		while (vazut.pollEvent(e))
		{
			if (e.type == Event::Closed)
				vazut.close();

		}
		vazut.clear(Color::White);
		int a[12][12];
		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++)
			{

				a[i][j] = grid[i][j];

				v.setTextureRect(IntRect(a[i][j] * w, 0, w, w));
				v.setPosition(i*w, j*w);
				vazut.draw(v);
			}
		vazut.display();
	}
}

bool aiCastigat(TOT*matrice)
{
	for (int i = 1; i <=matrice->n; i++)
		for (int j = 1; j <= matrice->m; j++)
			if (matrice->sgrid[i][j] == 9 || (matrice->grid[i][j] != matrice->sgrid[i][j] && matrice->grid[i][j] != 9))
				return false;

	return true;
}

void Click(TOT*matrici, int x, int y, Event e)
{
	if (x > 0 && y > 0 && y < matrici->m && x < matrici->n)
	{
		if (e.type == Event::MouseButtonPressed)
		{
			if (e.key.code == Mouse::Left)
			{
				if (matrici->grid[x][y] == 0)
					CautaGoale(x, y, matrici);
				else if (matrici->sgrid[x][y] != 11)
					matrici->sgrid[x][y] = matrici->grid[x][y];
			}
			else if (e.key.code == Mouse::Right)
			{
				if (matrici->sgrid[x][y] == 10)
					matrici->sgrid[x][y] = 11;
				else if (matrici->sgrid[x][y] == 11)
					matrici->sgrid[x][y] = 10;
			}
		}
	}
}

void Deseneaza(RenderWindow &app, TOT*matrice, int ok, int w, Sprite s)
{
	/*if(matrice->n<10||matrice->m<10)
		
		app.create(VideoMode(40 * 10, 40 * 10), "Minesweeper!", sf::Style::Close);
	else
		app.create(VideoMode(40 *matrice->n, 40 *matrice->m), "Minesweeper!", sf::Style::Close);*/

	if (!app.hasFocus()) {
		return;
	}
	int cell_size = (w / matrice->n);
	for (int i = 1; i < matrice->n; i++)
		for (int j = 1; j < matrice->m; j++)
		{
			if (ok == 0)
				matrice->sgrid[i][j] = matrice->grid[i][j];
			s.setTextureRect(IntRect(matrice->sgrid[i][j] * w, 0, w, w));
			s.setPosition(i*w+64, j*w+64);
			app.draw(s);
		}
	//app.display();
}


void Bombe(TOT*matrici)
{
	int i = 0,locuri=(matrici->m-1)*(matrici->n-1);
	int bombe = min(matrici->nr_bombe, locuri);
	while (i < bombe)
	{
		int a = rand() % (matrici->n - 1), b = rand() % (matrici->m - 1);
		if (matrici->grid[a + 1][b + 1] != 9)
		{
			matrici->grid[a + 1][b + 1] = 9;
			i++;
		}
	}
}

/*void Initializare(int grid[12][12], int sgrid[12][12], int n, int m)
{
	int nr = 10;
	Bombe(grid, n, m, nr);
	for (int i = 1; i < n; i++)
		for (int j = 1; j < m; j++)
		{
			sgrid[i][j] = 10;
			int n = 0;
			if (grid[i][j] == 9)
				continue;
			if (grid[i + 1][j] == 9)
				n++;
			if (grid[i][j + 1] == 9)
				n++;
			if (grid[i - 1][j] == 9)
				n++;
			if (grid[i][j - 1] == 9)
				n++;
			if (grid[i + 1][j + 1] == 9)
				n++;
			if (grid[i - 1][j - 1] == 9)
				n++;
			if (grid[i - 1][j + 1] == 9)
				n++;
			if (grid[i + 1][j - 1] == 9)
				n++;
			grid[i][j] = n;
		}
}*/

void Initializare(TOT*matrici)
{
	for (int i = 1; i < matrici->n; i++)
		for (int j = 1; j < matrici->m; j++)
		{
			matrici->grid[i][j] = 0;
			matrici->sgrid[i][j] = 10;
		}

	Bombe(matrici);
	for (int i = 1; i < matrici->n; i++)
		for (int j = 1; j < matrici->m; j++)
		{
			
			if (matrici->grid[i][j] == 9)
				continue;
			int n = 0;
			for (int x = -1; x <= 1; x++)
				for (int y = -1; y <= 1; y++)
					if (i + x >= 1 && i + x < matrici->n && j + y >= 1 && j + y < matrici->m && matrici->grid[i + x][j + y] == 9)
						n++;
			matrici->grid[i][j] = n;
		}
}


TOT* AlocareMemorieMatrice(int n, int m, int nr_bombe)
{
	TOT* tot = (TOT*)malloc(sizeof(TOT));
	tot->n = n;
	tot->m = m;
	tot->nr_bombe = nr_bombe;
	tot->sgrid = (int**)malloc(sizeof(int*) * (n + 1));
	tot->grid = (int**)malloc(sizeof(int*) * (n + 1));

	for (int i = 1; i <= n; i++)
	{
		tot->sgrid[i] = (int*)malloc(sizeof(int) * (m + 1));
		tot->grid[i] = (int*)malloc(sizeof(int) * (m + 1));
	}

	return tot;
}

void ElibereazaMemorieMatrice(TOT *matrici)
{
	for (int i = 1; i <= matrici->n; i++)
	{
		free(matrici->sgrid[i]);
		free(matrici->grid[i]);
	}
	free(matrici->sgrid);
	free(matrici->grid);
	free(matrici);
}

TOT* RedimensionareMatrice(TOT* matrici, int n, int m, int nr_bombe)
{
	TOT* nouaMatrice = AlocareMemorieMatrice(n, m, nr_bombe);
	ElibereazaMemorieMatrice(matrici);
	return nouaMatrice;
}
