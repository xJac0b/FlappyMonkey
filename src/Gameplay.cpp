#include "pch.h"
#include "Gameplay.h"

Gameplay::Gameplay(sf::Vector2u v, std::map<sf::String, sf::Texture>& textures, sf::Font& font, sf::RenderStates& state) : v(v), textures(textures), font(font),
	start(1), end(0), fall(0), pipe(0), xPipe(1000.f), points(0)
{
	this->state = state;
	this->background.resize(4, sf::Vertex());
	gui::setVertexShape(this->background, { 0, 0, static_cast<float>(v.x),
		static_cast<float>(v.y) });
	gui::setVertexShape(this->background, { 0, 0, static_cast<float>(this->state.texture->getSize().x),
		static_cast<float>(this->state.texture->getSize().y) }, 0);
	//init keys image
	this->keysState.texture = &this->textures["KEYS"];
	this->keys.resize(4, sf::Vertex());
	gui::setVertexShape(this->keys, { gui::p2pX(31.775f, v),gui::p2pY(70.f, v),
		gui::p2pX(36.45f, v), gui::p2pY(27.77f, v)});
	gui::setVertexShape(this->keys, {0.f, 0.f,
		 700.f, 300.f}, 0);
	//init monkey
	this->monkey = std::make_unique<Monkey>(
		sf::FloatRect(
			gui::p2pX(45.81f, v), gui::p2pY(30.05f, v),
			gui::p2pX(10.f, v), gui::p2pY(17.78f, v)),
		sf::FloatRect(
			gui::p2pX(3.0f, v), gui::p2pY(1.f, v),
			gui::p2pX(3.6f, v), gui::p2pY(17.f, v)),
		this->textures["MONKEY"], sf::Vector2f(250.f, 600.f));
	//init view
	this->view = std::make_unique<sf::View>(sf::FloatRect(0.f, 0.f,
		static_cast<float>(v.x), static_cast<float>(v.y)));
	for (auto i = 0; i < 8; i++)
		this->updatePipes();
	//Init text
	this->pointsText.setOutlineThickness(3.f);
	this->pointsText.setOutlineColor(sf::Color::Black);
	this->pointsText.setFont(this->font);
	this->pointsText.setCharacterSize(gui::calcCharSize(v, 20));
	this->pointsText.setString(std::to_string(this->points / 2));
	this->pointsText.setPosition(v.x / 2 - this->pointsText.getGlobalBounds().width / 2.f,
		gui::p2pY(10.f, v));
	//init music
	this->music.openFromFile("Resources/Sounds/music.ogg");
	this->music.setVolume(20.f);
}

Gameplay::~Gameplay()
{
}

const unsigned int Gameplay::getPoints() const
{
	return this->points;
}

const bool& Gameplay::gameOver() const
{
	return this->end;
}

void Gameplay::pauseMusic()
{
	if (this->music.getStatus() == sf::Music::Playing)
		this->music.pause();
	else
		this->music.play();
}

void Gameplay::updatePipes()
{
	if (this->pipes.size() > 7)
		this->pipes.pop_front();

	float h = rand() % static_cast<int>(gui::p2pY(45.f, v)) +
		gui::p2pY(9.25f, v), space = gui::p2pY(34.25f, v);


	if (h >= gui::p2pY(27.78f, v))
		this->pipes.push_back(std::make_unique<Pipe>(sf::FloatRect(this->xPipe, v.y - h,
			gui::p2pX(11.19f, v), h),
			sf::FloatRect(gui::p2pX(1.f, v), gui::p2pY(2.f, v),
				gui::p2pX(10.19f, v), h),
			this->textures["PIPE1"]));
	else
		this->pipes.push_back(std::make_unique<Pipe>(sf::FloatRect(this->xPipe, v.y - h,
			gui::p2pX(11.19f, v), gui::p2pY(27.77f, v)),
			sf::FloatRect(gui::p2pX(1.f, v), gui::p2pY(2.f, v),
				gui::p2pX(10.19f, v), gui::p2pY(27.77f, v)),
			this->textures["PIPE1"]));

	if (h >= gui::p2pY(41.66f, v))
		this->pipes.push_back(std::make_unique<Pipe>(sf::FloatRect(this->xPipe, 0.f - (v.y - h - space),
			gui::p2pX(11.19f, v), gui::p2pY(27.77f, v)),
			sf::FloatRect(gui::p2pX(1.f, v), gui::p2pY(-2.f, v),
				gui::p2pX(10.19f, v), gui::p2pY(27.77f, v)),
			this->textures["PIPE2"]));
	else
		this->pipes.push_back(std::make_unique<Pipe>(sf::FloatRect(this->xPipe, 0.f,
			gui::p2pX(11.19f, v), v.y - space - h),
			sf::FloatRect(gui::p2pX(1.f, v), gui::p2pY(-2.f, v),
				gui::p2pX(10.19f, v), v.y - space - h),
			this->textures["PIPE2"]));

	this->xPipe += gui::p2pX(26.f, v);
}

void Gameplay::update(const float& dt)
{
	if (!this->fall)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			if (this->start)
			{
				this->start = false;
				this->music.play();
			}	
			else
				this->monkey->jump();
		if (!this->start)
			this->monkey->update(dt);

		this->view->setCenter(this->monkey->getPosition().x + this->monkey->getBounds().width / 2.f,
			v.y / 2.f);

		if (this->monkey->getPosition().x > this->pipes[pipe]->getPosition().x + this->pipes[pipe]->getBounds().width / 2.f)
		{
			pipe += 1;
			points++;
			this->pointsText.setString(std::to_string(this->points / 2));
			this->pointsText.setPosition(v.x / 2 - this->pointsText.getGlobalBounds().width / 2.f,
				gui::p2pY(10.f, v));
			if (pipe > 4)
			{
				pipe = 4;
				this->updatePipes();
			}

		}
		if (this->pipes[pipe]->getBounds(1).intersects(this->monkey->getBounds(1)) ||
			this->pipes[pipe + 1]->getBounds(1).intersects(this->monkey->getBounds(1)) ||
			this->monkey->getPosition().y < -this->monkey->getBounds().height ||
			this->monkey->getPosition().y > v.y + this->monkey->getBounds().height)
		{
			this->music.stop();
			this->fall = true;
		}
	}
	else
	{
		this->monkey->fall(dt);
		if (this->monkey->getPosition().y > v.y + this->monkey->getBounds().height)
			this->end = true;
	}
	
}

void Gameplay::render(sf::RenderTarget& target)
{
	target.draw(&this->background[0], 4, sf::Quads, this->state);

	target.setView(*this->view);
	for (auto& i : this->pipes)
		i->render(target);
	this->monkey->render(target);

	target.setView(target.getDefaultView());

	if (this->start)
		target.draw(&this->keys[0], 4, sf::Quads, this->keysState);

	if (!this->end)
		target.draw(this->pointsText);
}
