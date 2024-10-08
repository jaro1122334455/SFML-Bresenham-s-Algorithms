#include "../headers/Board.h"
#include "../headers/Block.h"
#include <iostream>
#include <cmath>

Board::Board(int x, int y, int blckSize)
{
    this->x = x;
    this->y = y;
    this->blckSize = blckSize;

    grid = new Block*[x];

    for (int i = 0; i < x; i = i + 1) 
    {
        grid[i] = new Block[y];
    }

    for(int i = 0; i < x; i = i + 1)
    {
        for(int j = 0; j < y; j = j + 1)
        {
            grid[i][j] = Block(i * blckSize , j * blckSize, blckSize, blckSize);
        }
    }

}

void Board::draw(sf::RenderTarget& target, sf::RenderStates state) const                         //target to przesłane okno do wyświetlania (tak jak window.draw())
{
    for(int i = 0; i < x; i = i + 1)
    {
        for(int j = 0; j < y; j = j + 1)
        {
            target.draw(grid[i][j]);
        }
    }
}

void Board::putPixel(int x, int y)
{
    std::cout << "putPixel on: " << x << " : " << y << std::endl;
    grid[x][y].getShape().setFillColor(sf::Color::Red);
}

void Board::drawCircle(int cx, int cy, int r)
{
    int x = 0;
    int y = -r;

    // putPixel(200, 200);

    while(x < -y)
    {
        int yMid = y + 0.5;

        if( (x*x) + (yMid * yMid) > (r * r))
        {
            y = y + 1;
        }

        putPixel(cx + x, cy + y);
        putPixel(cx - x, cy + y);
        putPixel(cx + x, cy - y);
        putPixel(cx - x, cy - y);

        putPixel(cx + y, cy + x);
        putPixel(cx + y, cy - x);
        putPixel(cx - y, cy + x);
        putPixel(cx - y, cy - x);
        x = x + 1;

    }

}

void Board::drawLine(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;                                       // obliczanie przesunięcia, czyli boków trójkąta który powstaje

    if(dx != 0)
    {
        float m = (float)dy / dx;                                  // obliczanie pochylenia linii (ile komórek y przesuwamy się w dół na każdą komórkę x)

        std::cout << "dx: " << dx << std::endl;
        std::cout << "dy: " << dy << std::endl;


        std::cout << "m: " << m << std::endl;

        for(int i = 0; i < dx; i = i + 1)        // iteracaj po całej długości linii 
        {
            putPixel(x0 + i, round(y0 + (i * m)));
            // putPixel(x0 + i, y0 + (i * m));
        }
    }

}

Board::~Board()
{
    std::cout << "Destruktor" << std::endl;

    // Usunięcie dynamicznie alokowanej pamięci dla grid
    for (int i = 0; i < x; ++i) {
        delete[] grid[i];  // usunięcie każdego wiersza (tablicy obiektów Block)
    }

    delete[] grid;  // usunięcie tablicy wskaźników

    grid = nullptr;  // ustawienie wskaźnika na null dla bezpieczeństwa
}