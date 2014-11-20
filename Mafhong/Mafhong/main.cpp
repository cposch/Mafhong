#include<SFML\Graphics.hpp>
#include<iostream>

int main()
{	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Mafhong");
    
	sf::Texture backgroundTexture;
	if(!backgroundTexture.loadFromFile("boden.png", sf::IntRect(0, 0, 512, 512)))
	{	
		return -1;
	}
	else
	{	
		std::cout<<"Texture geladen";
	}

	sf::Sprite background;
	background.setTexture(backgroundTexture);

	sf::ConvexShape stone;
	stone.setPointCount(5);
	stone.setPoint(0, sf::Vector2f(0,0));
	stone.setPoint(1, sf::Vector2f(0,31));
	stone.setPoint(2, sf::Vector2f(-23,31));
	stone.setPoint(3, sf::Vector2f(-23,1));
	stone.setPoint(4, sf::Vector2f(-22,0));

	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
		window.draw(background);
		window.draw(shape);
        window.display();
    }

    return 0;
}