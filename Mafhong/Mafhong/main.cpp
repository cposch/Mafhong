#include<SFML\Graphics.hpp>
#include<conio.h>
#include<iostream>

class Stone
{
public:
	sf::ConvexShape stone;
	
	Stone()
	{
		stone.setPointCount(6);
		stone.setPoint(0, sf::Vector2f(0,0));
		stone.setPoint(1, sf::Vector2f(0,30));
		stone.setPoint(2, sf::Vector2f(1,31));
		stone.setPoint(3, sf::Vector2f(23,31));
		stone.setPoint(4, sf::Vector2f(23,1));
		stone.setPoint(5, sf::Vector2f(22,0));

		stone.setScale(5,5);
	}

	void SetColor(const sf::Color &color)
	{
		stone.setFillColor(color);
	}

	void SetTablePosition(int x, int y, int z = 1)
	{
		tablePosition.x = x;
		tablePosition.y = y;
		tablePosition.z = z;
	}

	sf::Vector3i GetTablePosition()
	{
		return tablePosition;
	}
	
	void SetTablePosition2(int x1, int y1, int x2, int y2, int z = 1)
	{
		tablePosition.x = x1;
		tablePosition.y = y1;
		tablePosition.z = z;
		tablePosition2.x = x2;
		tablePosition2.y = y2;
	}

	sf::Vector3i GetTablePosition2()
	{
		return tablePosition;
	}

	void SetPosition(float x, float y)
	{
		stone.setPosition(x,y);
	}

	sf::Vector2i GetPosition()
	{
		sf::Vector2i stonePosition;
		stonePosition.x = static_cast<int>(stone.getPosition().x);
		stonePosition.y = static_cast<int>(stone.getPosition().y);

		return stonePosition;
	}
	
	/*void SetTexture(const sf::Texture texture)
	{
		stone.setTexture(texture);
	}*/

	void SetStoneValue(unsigned int _value)
	{
		value = _value;
	}

	unsigned int GetStoneValue()
	{
		return value;
	}

	void SteinSetzen()
	{
		vorhanden = true;
	}

	void SteinEntfernen()
	{
		vorhanden = false;
	}

	bool SteinKontrollieren()
	{
		return vorhanden;
	}

private:
	unsigned int value;
	sf::Vector3i tablePosition;
	sf::Vector2i tablePosition2;
	bool vorhanden;
};

bool CheckStone(sf::Vector2i stoneposition, sf::Vector2i mouseposition)
{
	if((mouseposition.x >= stoneposition.x) && (mouseposition.x < (stoneposition.x + (22*5))))
		if ((mouseposition.y >= stoneposition.y) && (mouseposition.y < (stoneposition.y + (30*5))))
			return true;
	
	return false;
}

int main()
{	
	const int stonemembers = 8;
	int nochVorhanden = stonemembers;
	int nachbarn = 0;
	sf::Vector3i myposition;
	sf::Vector3i position;
	sf::Vector2i mousePosition;
	int i;
	sf::Vector2i check;
	unsigned int value = 0;
	int stonenumber = -1;
	int ausgewaehlt = 0;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Mafhong");
	window.setFramerateLimit(60);

	/*sf::Texture backgroundTexture;
	if(!backgroundTexture.loadFromFile("boden.png", sf::IntRect(0, 0, 512, 512)))
	{	
		return -1;
	}
	else
	{	
		std::cout<<"Texture geladen\n";
	}

	sf::Sprite background;
	background.setTexture(backgroundTexture);*/


	/*sf::Texture SteinBambus1Texture;
	if(!SteinBambus1Texture.loadFromFile("Stone\\Bambus_1.jpg", sf::IntRect(0, 0, 22, 30)))
	{	
		return -1;
	}
	else
	{	
		std::cout<<"Stein Bambus 1 geladen";
	}*/

	
	Stone stone[stonemembers];
	stone[0].SetColor(sf::Color::White);
    stone[0].SetPosition(10,10);
	stone[0].SetStoneValue(1);
	stone[0].SetTablePosition(1,1);
	//stone[0].SetTexture(SteinBambus1Texture);
	//stone[0].stone.setTexture(SteinBambus1Texture);
	stone[2].SetColor(sf::Color::White);
    stone[2].SetPosition(10,175);
	stone[2].SetStoneValue(1);
	stone[2].SetTablePosition(1,2);
	
	stone[1].SetColor(sf::Color::Blue);
	stone[1].SetPosition(125,10);
	stone[1].SetStoneValue(2);
	stone[1].SetTablePosition(2,1);
	stone[3].SetColor(sf::Color::Blue);
	stone[3].SetPosition(125,175);
	stone[3].SetStoneValue(2);
	stone[3].SetTablePosition(2,2);

	stone[4].SetColor(sf::Color::Red);
	stone[4].SetPosition(240,10);
	stone[4].SetStoneValue(3);
	stone[4].SetTablePosition(3,1);
	stone[5].SetColor(sf::Color::Red);
	stone[5].SetPosition(240,175);
	stone[5].SetStoneValue(3);
	stone[5].SetTablePosition(3,2);

	stone[6].SetColor(sf::Color::Magenta);
	stone[6].SetPosition(355,10);
	stone[6].SetStoneValue(4);
	stone[6].SetTablePosition(4,1);
	stone[7].SetColor(sf::Color::Magenta);
	stone[7].SetPosition(355,175);
	stone[7].SetStoneValue(4);
	stone[7].SetTablePosition(4,2);

	for (i = 0; i < stonemembers; ++i)
	{
		stone[i].SteinSetzen();
	}


	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
			
			if(event.type == sf::Event::MouseMoved)
			{
				mousePosition.x = event.mouseMove.x;
				mousePosition.y = event.mouseMove.y;
				
			}

			if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{	
				std::cout<<mousePosition.x<<" "<<mousePosition.y<<"\n";
				nachbarn = 0;
				
				for(i = 0; i < stonemembers; ++i)
				{
					if(stone[i].SteinKontrollieren())
					{
						check = stone[i].GetPosition();
						if(CheckStone(check, mousePosition))
						{
							//Überprüfen ob wählbar
							myposition = stone[i].GetTablePosition();
							for(int j = 0; j < stonemembers; ++j)
							{
								if(j != i)
								{
									if(stone[j].SteinKontrollieren())
									{
										position = stone[j].GetTablePosition();
										if(position.z == myposition.z)
										{	
											if(position.y == myposition.y)
											{
												if(position.x == myposition.x - 1)
													++nachbarn;
												if(position.x == myposition.x + 1)
													++nachbarn;
											}
										}
									}
								}
							}
							
							
							switch(ausgewaehlt)
							{
								case 0:
									if(nachbarn < 2)
									{
										value = stone[i].GetStoneValue();
										stonenumber = i;
										std::cout<<"Ausgewaehlt: "<<stonenumber<<"\n";
										ausgewaehlt = 1;
									}
									break;
								
								case 1:
									if(nachbarn < 2)
									{
										if(stone[i].GetStoneValue() == value && i != stonenumber) //wenn zwei gleiche Steine -> werden entfernt
										{
											stone[stonenumber].SteinEntfernen();
											stone[i].SteinEntfernen();
											nochVorhanden -= 2;
										}
									}
									
									value = 0;
									stonenumber = -1;
									ausgewaehlt = 0;									
									break;								
							}
						}
					}
				}
			}
		}		

		window.clear();
		//window.draw(background);
		for(i = 0; i < stonemembers; ++i)
		{
			if(stone[i].SteinKontrollieren())
			{	if(i == stonenumber)
				{
					stone[i].stone.setOutlineThickness(0.5f);
					stone[i].stone.setOutlineColor(sf::Color::Yellow);
				}
				else
				{
					stone[i].stone.setOutlineThickness(0.0f);
				}

				window.draw(stone[i].stone);
			}
		}

		window.display();
		
		//if(nochVorhanden <= 0) //Schließt Fenster wenn kein Stein mehr übrig ist.
		//	window.close();
    }

    return 0;
}