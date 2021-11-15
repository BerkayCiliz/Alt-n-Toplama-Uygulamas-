#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    int width = 600;
    int height = 600;
    int block = 20;
    int order = 0;

    sf::RenderWindow window(sf::VideoMode(width, height+40), "Altin Toplama");

    sf::RectangleShape shapeList[block][block];
    sf::Text textList[block][block];

    int pointList[4]= {200,200,200,200};
    sf::Text pointText[4];
    sf::Font font;
    font.loadFromFile("arial.ttf");
    int charactersPosition [4][2] = {
        {0,0},
        {0,height - (height / block)},
        {width - (width / block),0},
        {width - (width / block),height - (height / block)}
    };
    sf::RectangleShape characterList[4];
    sf::Texture texture[4];

    for(int i = 0; i < 4 ; i++) {
        sf::RectangleShape character(sf::Vector2f(width/block, height/block));

        texture[i].loadFromFile("images/character" + to_string(i + 1) +".png");
        character.setTexture(&texture[i]);
        character.setPosition(charactersPosition[i][0],charactersPosition[i][1]);
        characterList[i] = character;
        pointText[i].setFont(font);
        pointText[i].setString("Puan "+ to_string(i + 1) +" : " + to_string(pointList[i]));
        pointText[i].setCharacterSize(20);
        pointText[i].setFillColor(sf::Color::White);
        pointText[i].setPosition(i * (width/5),height);
    }

    sf::Text orderText;
    orderText.setFont(font);
    orderText.setString("Sira : " + to_string(order % 4 + 1));
    orderText.setCharacterSize(20);
    orderText.setFillColor(sf::Color::White);
    orderText.setPosition(4*(width/5),height);


    for(int i = 0; i < block; i++) {
        for(int y = 0; y < block ; y++) {
            sf::RectangleShape rectangle(sf::Vector2f(width/block, height/block));
            if(i % 2 == 0) {
                if(y % 2 == 0) {
                    rectangle.setFillColor(sf::Color::Blue);
                } else {
                    rectangle.setFillColor(sf::Color::Red);
                }

            } else {
                if(y % 2 == 0) {
                    rectangle.setFillColor(sf::Color::Red);
                } else {
                    rectangle.setFillColor(sf::Color::Blue);
                }
            }
            rectangle.setPosition( (i * (width/block)), (y * (height/block)));
            shapeList[i][y] = rectangle;
        }
    }

    srand(time(0));
    int goldCount = (block * block) * (rand() % 10 + 10) / 100;
    sf::CircleShape goldList[goldCount];

    for(int i = 0; i < goldCount; i++) {
        int x = rand() % block;
        int y = rand() % block;

        sf::CircleShape shape((width / (block * 2)));
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition( (x * (width/block)), (y * (height/block )));

        goldList[i] = shape;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Left && charactersPosition[order % 4][0] >= (width / block)) {
                    charactersPosition[order % 4][0] = charactersPosition[order % 4][0] - (width / block);
                }
                if (event.key.code == sf::Keyboard::Right && charactersPosition[order % 4][0] < width - (block * 3)) {
                    charactersPosition[order % 4][0] = charactersPosition[order % 4][0] + (width / block);
                }
                if (event.key.code == sf::Keyboard::Up && charactersPosition[order % 4][1] >= (height / block)) {
                    charactersPosition[order % 4][1] = charactersPosition[order % 4][1] - (height / block);
                }
                if (event.key.code == sf::Keyboard::Down && charactersPosition[order % 4][1] < height - (block * 3)) {
                    charactersPosition[order % 4][1] = charactersPosition[order % 4][1] + (height / block);
                }
                characterList[order % 4].setPosition(charactersPosition[order % 4][0],charactersPosition[order % 4][1]);
                pointList[order % 4] = pointList[order % 4] - 5;
                for(int i = 0; i < goldCount; i++) {
                    sf::Vector2f goldPosition = goldList[i].getPosition();
                    if(goldPosition.x == charactersPosition[order % 4][0] && goldPosition.y == charactersPosition[order % 4][1]) {
                        pointList[order % 4] = pointList[order % 4] + (rand() % 4 + 1) * 5;
                        goldList[i].setPosition(-100,-100);
                    }
                }
                pointText[order % 4].setString("Puan "+ to_string((order % 4) + 1) +" : " + to_string(pointList[order % 4]));
                order++;
                orderText.setString("Sira : " + to_string((order % 4) + 1));
            }
        }

        window.clear();
        for(int i = 0; i < block; i++) {
            for(int y = 0; y < block ; y++) {
                window.draw(shapeList[i][y]);
                window.draw(textList[i][y]);
            }
        }
        for(int i = 0; i < goldCount; i++) {
            window.draw(goldList[i]);
        }

        for(int i = 0; i < 4; i++) {
            window.draw(characterList[i]);
            window.draw(pointText[i]);
        }
        window.draw(orderText);

        window.display();
    }

    return 0;
}
