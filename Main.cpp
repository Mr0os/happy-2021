#include<sfml/Graphics.hpp>
#include<cmath>
#include<sstream>
class circle:public sf::Drawable
{
	sf::CircleShape cir;
	sf::Vector2f direction;
	float speed,drag;
	sf::Color circle_color;
public:
	circle(sf::Vector2f dir)
	{
		drag = 0.9999f;
		cir.setRadius(10);
		circle_color = sf::Color(rand() % 255, rand() % 255, rand() % 255, sf::Uint8(255));
		cir.setFillColor(circle_color);
		speed = rand() % 10 + 5.f;
		direction = dir;
		cir.setOrigin(sf::Vector2f(10,10)/2.f);
		cir.setPosition(sf::Vector2f(300, 300));
	}

	virtual void draw(sf::RenderTarget& t, sf::RenderStates s)const
	{
		t.draw(cir);
	}
	void update_2021()
	{
		if (cir.getGlobalBounds().left < 0.f)
			direction.x = -direction.x;
		else if (cir.getGlobalBounds().left > 600.f)
			direction.x = -direction.x;
		if (cir.getGlobalBounds().top < 0.f)
			direction.y = -direction.y; 
		if (cir.getGlobalBounds().top >600.f )
			direction.y = -direction.y;
		circle_color.a = 150;
		cir.setFillColor(circle_color);
		cir.move(direction);
	}
	void update(sf::Time elapsed_time)
	{
		cir.move(direction);
		direction *= drag;
		cir.setFillColor(circle_color);
		circle_color.a =  -255 * elapsed_time.asSeconds();
	}
};
int main()
{
	std::stringstream ss;
	ss.str("");
	sf::VertexArray rectangle(sf::Quads, 4);
	rectangle[0] = sf::Vertex(sf::Vector2f(50, 190), sf::Color::Red);
	rectangle[1] = sf::Vertex(sf::Vector2f(20, 600), sf::Color::Green);
	rectangle[2] = sf::Vertex(sf::Vector2f(600, 600), sf::Color::Blue);
	rectangle[3] = sf::Vertex(sf::Vector2f(600, 150), sf::Color::Yellow);
	sf::Texture texture_2021;
	sf::Sprite sprite_2021;
	sf::Text text;
	sf::Font font,font1;
	texture_2021.loadFromFile("2021.png");
	sprite_2021.setTexture(texture_2021);
	font.loadFromFile("leadcoat.ttf");
	font1.loadFromFile("OpenSans_Bold.ttf");
	text.setFont(font);
	text.setCharacterSize(300);
	text.setFillColor(sf::Color::Black);
	text.setOrigin(50, 50);
	text.setPosition(300, 150);
	text.setString("10");
	int count=1000;
	bool count_over = false;
	srand(static_cast<unsigned>(time(0)));
	sf::Clock elapsed_time;
	float count_down=10.f;
	std::vector<circle> objects;
	for (int i = 0; i < count; i++)
	{
		objects.push_back(circle(sf::Vector2f(std::cos(rand()%360+1)/(0.25f), std::sin(rand()%360+1)/(0.25f))));
	}
	sf::RenderWindow w(sf::VideoMode(600, 600), "Happy New Year!");
	w.setFramerateLimit(60);
	
	while (w.isOpen())
	{
		sf::Event e;
		while (w.pollEvent(e))
		{

			switch (e.type)
			{
			case 0:
				w.close();

			}
		}
		if (elapsed_time.getElapsedTime().asSeconds() > 1.f&&!count_over)
		{
			count_down -= 1.f;
			for (int i = 0; i < count; i++)
			{
				objects[i] = circle(sf::Vector2f( std::cos(rand() % 360)/(0.25f),  std::sin(rand() % 360)/(0.25f)));
			}
			elapsed_time.restart();
		}
		
		if(!count_over)
			for (int i = 0; i < count; i++)
			{
				objects[i].update(elapsed_time.getElapsedTime());
			}
		else
			for (int i = 0; i < count; i++)
			{
				objects[i].update_2021();

			}
		
		if (count_down <= -1&&!count_over)
		{
			ss.str("");
			count_over = true;
			ss << "HAPPY NEW YEAR!";
			text.setFont(font1);
			text.setCharacterSize(50);
			text.setFillColor(sf::Color::White);
			text.setPosition(125, 100);
			text.setString(ss.str());
			
			rectangle[0] = sf::Vertex(sf::Vector2f(text.getGlobalBounds().left , text.getGlobalBounds().top), sf::Color::Red);
			rectangle[1] = sf::Vertex(sf::Vector2f(text.getGlobalBounds().left+text.getGlobalBounds().width,text.getGlobalBounds().top), sf::Color::Cyan);
			rectangle[2] = sf::Vertex(sf::Vector2f(text.getGlobalBounds().left + text.getGlobalBounds().width+30, text.getGlobalBounds().top + text.getGlobalBounds().height), sf::Color::Blue);
			rectangle[3] = sf::Vertex(sf::Vector2f(text.getGlobalBounds().left+30, text.getGlobalBounds().top + text.getGlobalBounds().height), sf::Color::Yellow);
		}
		else if(!count_over)
		{
			ss.str(""); ss << int(count_down); 
			text.setString(ss.str());
		}
		

		
		w.clear();
		
		for (int i = 0; i < count; i++)
		{
			w.draw(objects[i]);
		}
		if (count_over)
		{
			
			w.draw(sprite_2021);
			w.draw(text);
		}
		else
			w.draw(text);
		w.display();

	}

}