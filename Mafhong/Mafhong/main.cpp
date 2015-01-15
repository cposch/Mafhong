#include<SFML\Graphics.hpp>
#include<conio.h>
#include<stdlib.h>
#include<iostream>
#include<string>

//Stein
float scale = 2.74f;

class Position
{
public:
	int x1;
	int x2;
	int y1;
	int y2;
	int z;
};

class Stone
{
public:
	sf::RectangleShape stonepicture;
	sf::ConvexShape stonesite;
	sf::ConvexShape stonefront;
	
	Stone()
	{
		stonepicture.setSize(sf::Vector2f(22,30));

		stonesite.setPointCount(4);
		stonesite.setPoint(0, sf::Vector2f(22,0));
		stonesite.setPoint(1, sf::Vector2f(22,30));
		stonesite.setPoint(2, sf::Vector2f(23,31));
		stonesite.setPoint(3, sf::Vector2f(23,1));
		
		stonefront.setPointCount(4);
		stonefront.setPoint(0, sf::Vector2f(0,30));
		stonefront.setPoint(1, sf::Vector2f(22,30));
		stonefront.setPoint(2, sf::Vector2f(23,31));
		stonefront.setPoint(3, sf::Vector2f(1,31));
		
		stonepicture.setScale(scale, scale);
		stonefront.setScale(scale, scale);
		stonesite.setScale(scale, scale);

		stonesite.setOutlineThickness(0.3f);
		stonefront.setOutlineThickness(0.3f);
		stonepicture.setOutlineThickness(0.5f);

	}

	void SetColor(const sf::Color &color)
	{
		stonepicture.setFillColor(color);
		stonesite.setFillColor(color);
		stonefront.setFillColor(color);
	}

	void SetOutLineColor(const sf::Color &color)
	{
		stonesite.setOutlineColor(color);
		stonefront.setOutlineColor(color);
		stonepicture.setOutlineColor(color);
	}

	void SetTablePosition(int x1, int y1, int x2 = -1, int y2 = -1, int z = 0)
	{
		tp.x1 = x1;
		tp.x2 = x2;
		tp.y1 = y1;
		tp.y2 = y2;
		tp.z = z;
	}

	Position GetTablePosition()
	{
		return tp;
	}

	void SetPosition(float x, float y)
	{
		stonepicture.setPosition(x,y);
		stonesite.setPosition(x,y);
		stonefront.setPosition(x,y);
	}

	sf::Vector2i GetPosition()
	{
		sf::Vector2i stonePosition;
		stonePosition.x = static_cast<int>(stonefront.getPosition().x);
		stonePosition.y = static_cast<int>(stonefront.getPosition().y);

		return stonePosition;
	}

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

	/*void SetTexture(sf::Texture *texture)
	{
		stonepicture.setTexture(texture);
	}*/

private:
	unsigned int value;
	Position tp;
	bool vorhanden;
};

bool CheckStone(sf::Vector2i stoneposition, sf::Vector2i mouseposition)
{
	if((mouseposition.x >= stoneposition.x) && (mouseposition.x < (stoneposition.x + (22*scale))))
		if ((mouseposition.y >= stoneposition.y) && (mouseposition.y < (stoneposition.y + (30*scale))))
			return true;
	
	return false;
}


int main()
{	
	bool nachbarl = false;
	bool nachbarr = false;
	Position myposition;
	Position position;
	sf::Vector2i mousePosition;
	int i = 0;
	int j = 0;
	int check_z = -1;
	int check_stonenumber = -1;
	int reihe = 0;
	int hoehe = 0;
	sf::Vector2i check;
	unsigned int value = 0;
	int stonenumber = -1;
	bool ausgewaehlt = false;
	int randomzahl = 0;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Mafhong");
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

//Steintexture laden
	sf::Texture SteinTexture[36];
	int zaehler = 1;
	std::string nummer;
	std::string stein;
	
	for(i=0; i<36; ++i, ++zaehler)
	{		
		nummer = std::to_string(zaehler);

		if(i<9)
			stein = "Bambus_" + nummer + ".jpg";
		else
		{
			if(i>=9 && i<=17)
				stein = "Kreis_" + nummer + ".jpg";
			else
			{
				if(i>=18 && i<=26)
					stein = "Zahl_" + nummer + ".jpg";
				else
					stein = "Special_" + nummer + ".jpg";				
			}
		}

		if(!SteinTexture[i].loadFromFile(stein, sf::IntRect(0, 0, 22, 30)))
		{	
			return -1;
		}
		else
		{	
			std::cout<<stein<<" geladen.\n";
		}

		if(zaehler == 9)
			zaehler = 0;
	}
	
//Leveldisgn

	//const int maxlevel = 1;
	int level = 1;
	//const int stonemembers = 8;
	int stonemembers = 144;
	Stone stone[144];
	
	//sf::Vector2i levelTablePosition[stonemembers];
	//sf::Vector2i levelPosition[stonemembers];
	
	//sf::Vector2i[8];
	
	
	if(level == 0)
	{		
		stone[0].SetColor(sf::Color::White);
		stone[0].SetPosition(10,10);
		stone[0].SetStoneValue(1);
		stone[0].SetTablePosition(1,1);
		//stone[0].SetTexture(SteinBambus1Texture);
		//stone[0].stonepicture.setTexture(SteinBambus1Texture);
		stone[2].SetColor(sf::Color::White);
		//stone[2].SetPosition(10,175);
		stone[2].SetPosition(10,105);
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
	}
	
	if(level == 1)
	{		
		hoehe = 0;
		stone[0].SetTablePosition(1, 3, -1, 4);
		stone[0].SetPosition((63 + 10), (85*3 + 52.5));
		stone[0].SteinSetzen();
		j = 1;
						
		while(j < stonemembers && hoehe < 4)
		{			
			//hoehe=0: R0,R7:2-13, R1,R6: 4-11, R2,R5: 3-12, R3,R4: 2-13 + (R3+R4,1)+(R3+R4,14)+(R3+R4,15)
			if(hoehe == 0)
			{
				if(reihe == 0 || reihe == 3 || reihe == 4 || reihe == 7)
				{
					for(i = 2; i <= 13; ++i, ++j)
					{	
						stone[j].SetTablePosition(i, reihe);
						stone[j].SetPosition((63*i + 10), (85*reihe + 10));
						stone[j].SteinSetzen();
					}
					
					++reihe;
				}

				if(reihe == 1 || reihe == 6)
				{
					for(i = 4; i <= 11; ++i, ++j)
					{	
						stone[j].SetTablePosition(i, reihe);
						stone[j].SetPosition((63*i+10), (85*reihe + 10));
						stone[j].SteinSetzen();
					}
					
					++reihe;
				}

				if(reihe == 2 || reihe == 5)
				{
					for(i = 3; i <= 12; ++i, ++j)
					{	
						stone[j].SetTablePosition(i, reihe);
						stone[j].SetPosition((63*i+10), (85*reihe + 10));
						stone[j].SteinSetzen();
					}

					++reihe;
				}

				if(reihe == 8)
				{	
					stone[j].SetTablePosition(14, 3, -1, 4);
					stone[j].SetPosition((63*14 + 10), (85*3 + 52.5));
					stone[j].SteinSetzen();
					++j;
					stone[j].SetTablePosition(15, 3, -1, 4);
					stone[j].SetPosition((63*15 + 10), (85*3 + 52.5));
					stone[j].SteinSetzen();
					++j;

					reihe = 1;
					++hoehe;
				}
			}
				
			//hoehe=1: R1-R6: 5-10
			if(hoehe == 1)
			{
				for(i = 5; i <= 10; ++i, ++j)
				{	
					stone[j].SetTablePosition(i, reihe, -1, -1, 1);
					stone[j].SetPosition((63*i + 8), (85*reihe + 8));
					stone[j].SteinSetzen();
				}
					
				if(reihe == 6)
				{	
					reihe = 2;
					++hoehe;
				}
				else
					++reihe;
			}

			//hoehe=2: R2-R5: 6-9
			if(hoehe == 2)
			{
				for(i = 6; i <= 9; ++i, ++j)
				{	
					stone[j].SetTablePosition(i, reihe, -1, -1, 2);
					stone[j].SetPosition((63*i + 6), (85*reihe + 6));
					stone[j].SteinSetzen();
				}
					
				if(reihe == 5)
				{	
					reihe = 3;
					++hoehe;
				}
				else
					++reihe;
			}
			//hoehe=3: R3-R4: 7-8
			if(hoehe == 3)
			{
				for(i = 7; i <= 8; ++i, ++j)
				{	
					stone[j].SetTablePosition(i, reihe, -1, -1, 3);
					stone[j].SetPosition((63*i + 4), (85*reihe + 4));
					stone[j].SteinSetzen();
				}
					
				if(reihe == 4)
					++hoehe;
				else
					++reihe;
			}
			//hoehe=4: (R3+R4, 7+8)
			if(hoehe == 4)
			{
				stone[j].SetTablePosition(7, 3, 8, 4, 4);
				stone[j].SetPosition((63*7+33.5), (85*3+44.5));
				stone[j].SteinSetzen();
			}
		}

		//Steinwerte zuweisen
		//randomzahl = rand() % 36;
	}	

	int nochVorhanden = stonemembers;

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
				nachbarl = false;
				nachbarr = false;
				
				check_z = -1;

				for(i=0; i<stonemembers; ++i)
				{
					if(stone[i].SteinKontrollieren())
					{
						check = stone[i].GetPosition();
												
						if(CheckStone(check, mousePosition))
						{
							myposition = stone[i].GetTablePosition();
							
							if(check_z < myposition.z)
							{
								check_stonenumber = i;
								check_z = myposition.z;

								std::cout<<check_stonenumber<<" "<<check_z<<"\n";
							}
						}
					}
				}

				myposition = stone[check_stonenumber].GetTablePosition();

				for(j = 0; j < stonemembers; ++j)
				{
					if(j != check_stonenumber)
					{
						if(stone[j].SteinKontrollieren())
						{
							position = stone[j].GetTablePosition();
							
							if(myposition.y1 == position.y1 || myposition.y1 == position.y2)
							{	
								if(myposition.x1 == position.x1 || myposition.x1 == position.x2)
								{
									if(myposition.x2!=-1)
									{
										if(myposition.x2 == position.x1 || myposition.x2 == position.x2)
										{
											if(myposition.z < position.z)
											{
												nachbarl = true;
												nachbarr = true;
												break;
											}
										}
									}
									else
									{
										if(myposition.z < position.z)
										{
											nachbarl = true;
											nachbarr = true;
											break;
										}
									}
								}

								if(myposition.z == position.z)
								{
									if(position.x1 == myposition.x1 - 1)
										nachbarl = true;
									if(position.x1 == myposition.x1 + 1)
										nachbarr = true;
									if(position.x2 == myposition.x1 - 1)
										nachbarl = true;
									if(position.x2 == myposition.x1 + 1)
										nachbarr = true;
												
									if(myposition.x2 != -1)
									{
										if(position.x1 == myposition.x2 - 1)
											nachbarl = true;
										if(position.x1 == myposition.x2 + 1)
											nachbarr = true;
										if(position.x2 == myposition.x2 - 1)
											nachbarl = true;
										if(position.x2 == myposition.x2 + 1)
											nachbarr = true;
									}												
								}
							}
						}
					}
				}

				switch(ausgewaehlt)
				{
					case false:
						if(!nachbarl || !nachbarr)
						{
							value = stone[check_stonenumber].GetStoneValue();
							stonenumber = check_stonenumber;
							std::cout<<"Ausgewaehlt: "<<stonenumber<<"\n";
							ausgewaehlt = true;
						}
						break;
					
					case true:
						if(!nachbarl || !nachbarr)
						{
							if(stone[check_stonenumber].GetStoneValue() == value && check_stonenumber != stonenumber) //wenn zwei gleiche Steine -> werden entfernt
							{
								stone[stonenumber].SteinEntfernen();
								stone[check_stonenumber].SteinEntfernen();
								nochVorhanden -= 2;
							}
						}
								
						value = 0;
						stonenumber = -1;
						check_stonenumber = -1;
						ausgewaehlt = false;									
						break;								
				}
			}		
		}
		
		window.clear();
		//window.draw(background);
		for(i = 0; i < stonemembers; ++i)
		{
			if(stone[i].SteinKontrollieren())
			{	
				if(i == stonenumber)
				{
					stone[i].SetOutLineColor(sf::Color::Yellow);
				}
				else
				{
					stone[i].SetOutLineColor(sf::Color::Black);
				}
				
				//stone[i].stonepicture          //Steintextur hinzufügen

				window.draw(stone[i].stonepicture);
				window.draw(stone[i].stonesite);
				window.draw(stone[i].stonefront);
			}
		}

		window.display();
		
		if(nochVorhanden <= 0) //Schließt Fenster wenn kein Stein mehr übrig ist.
			window.close();
    }

    return 0;
}