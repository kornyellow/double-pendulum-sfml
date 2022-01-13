#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#define GRAVITY 0.2

struct Ball {

	float l;
	float m;
	float a;
	float a_v;
	float a_a;
	float x;
	float y;
	float b_x;
	float b_y;

	sf::CircleShape shape;

	Ball(float length, float mass, float x, float y) {

		this->m = mass;
		this->l = length;
		this->x = x;
		this->y = y;

		this->a = 10;

		this->shape.setFillColor(sf::Color::White);
		this->shape.setRadius(this->m);
		this->shape.setOrigin(sf::Vector2f(this->m, this->m));
	}

	void update() {

		this->b_x = this->x + (this->l * sin(this->a));
		this->b_y = this->y + (this->l * cos(this->a));

		this->shape.setPosition(this->b_x, this->b_y);

		this->a_v += this->a_a;
		this->a += this->a_v;
	}

	void update(Ball& ball) {

		this->update();
		this->x = ball.b_x;
		this->y = ball.b_y;
	}

	void draw(sf::RenderWindow& window) {

		sf::Vertex line[2] = {
			sf::Vertex(sf::Vector2f(this->x, this->y)),
			sf::Vertex(sf::Vector2f(this->b_x, this->b_y))
		};

		window.draw(line, 2, sf::Lines);
		window.draw(this->shape);
	}
};

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 800), "Double Pendulum SFML");
	window.setFramerateLimit(80);

	sf::Event event;

	Ball b1(150, 15, 400, 400);
	Ball b2(150, 15, 400, 400);

	while(window.isOpen()) {

		while(window.pollEvent(event)) {

			switch(event.type) {

				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::TextEntered:
					if(event.text.unicode == 'q')
						window.close();
					break;

				default:
					break;
			}
		}

		float a, b, c, d, e, f, g, h, i;

		a = -GRAVITY * ((2 * b1.m) + b2.m) * sin(b1.a);
		b = b2.m * GRAVITY * sin(b1.a - (2 * b2.a));
		c = (b2.a_v * b2.a_v) * b2.l;
		d = (b1.a_v * b1.a_v) * b1.l * cos(b1.a - b2.a);
		e = 2 * sin(b1.a - b2.a) * b2.m * (c + d);
		f = a - b - e;
		g = (2 * b1.m) + b2.m;
		h = b2.m * cos((2 * b1.a) - (2 * b2.a));
		i = b1.l * (g - h);
		b1.a_a = f / i;

		a = 2 * sin(b1.a - b2.a);
		b = (b1.a_v * b1.a_v) * b1.l * (b1.m + b2.m);
		c = GRAVITY * (b1.m + b2.m) * cos(b1.a);
		d = (b2.a_v * b2.a_v) * b2.l * b2.m * cos(b1.a - b2.a);
		e = b + c + d;
		f = a * e;
		g = b2.m * cos((2 * b1.a) - (2 * b2.a));
		h = b2.l * ((2 * b1.m) + b2.m - g);
		b2.a_a = f / h;

		b1.update();
		b2.update(b1);

		window.clear();

		b1.draw(window);
		b2.draw(window);

		window.display();
	}

	return 0;
}