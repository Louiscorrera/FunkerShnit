#include "stdafx.h"
#include "State.h"

/* Colors(Declarations at bottom of State) */
void State::initColors()
{
	this->color = new Colors();
}

/* Fonts(Declarations at bottom of State) */
void State::initFonts()
{
	this->font = new Fonts();
}

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, float grid_size_f)
{
	this->quit = false;
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->grifSizeF = grid_size_f;

	/* Keys & Time inits */
	this->keyTime = 0.f;
	this->keyTimeMax = 15.f;

	/* Color init */
	this->initColors();
	
	/* Font init */
	this->initFonts();

}

State::~State()
{
	delete this->color;
	delete this->font;
}

const bool& State::getQuit() const
{
	return this->quit;
}

const bool& State::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

void State::updateMousePos(sf::View* view)
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	if (view)
	{
		this->window->setView(*view);
	}
	else
	{
		this->window->setView(this->window->getDefaultView());
	}
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = sf::Vector2u(
		static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->grifSizeF),
		static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->grifSizeF)
	);
	//system("cls");
	//std::cout << "X : " << this->mousePosWindow.x << " Y: " << this->mousePosWindow.y << "\n";
}

void State::updateKeytime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 100.f * dt;
	}
}

void State::endState()
{
	this->quit = true;
}



/* Colors */
/* WARNING: Can be accessed anywhere in a state and manipulated */
Colors::Colors()
{
	this->initColors();
}


void Colors::initColors()
{
	this->pukeGreen = sf::Color(204, 204, 0, 255);
	this->darkRed = sf::Color(153, 0, 0, 255);
	this->lightPurple1 = sf::Color(178, 102, 205, 255);
	this->darkPurple1 = sf::Color(102, 0, 204, 255);
	this->darkPurple2 = sf::Color(51, 0, 102, 255);
	this->lightGreen = sf::Color(51, 255, 51, 255);
	this->teal = sf::Color(0, 204, 204, 255);
	this->lightGrey = sf::Color(192, 192, 192, 255);
	this->lighterGrey = sf::Color(224, 224, 224, 255);
}



/* Fonts */
Fonts::Fonts()
{
	this->initFonts();
}

void Fonts::initFonts()
{
	if (!this->corleone.loadFromFile("Resources/Fonts/Corleone.ttf"))
	{
		throw "ERROR::InitFonts()::FONTS::STATE could not load one or more fonts from file";
	}
	if (!this->dashHorizon.loadFromFile("Resources/Fonts/Dash-Horizon-Demo.otf"))
	{
		throw "ERROR::InitFonts()::FONTS::STATE could not load one or more fonts from file";
	}
	if (!this->franchise.loadFromFile("Resources/Fonts/Franchise.ttf"))
	{
		throw "ERROR::InitFonts()::FONTS::STATE could not load one or more fonts from file";
	}
	if (!this->marketDeco.loadFromFile("Resources/Fonts/Market_Deco.ttf"))
	{
		throw "ERROR::InitFonts()::FONTS::STATE could not load one or more fonts from file";
	}
	if (!this->amazDoomRight.loadFromFile("Resources/Fonts/AmazDoomRight.ttf"))
	{
		throw "ERROR::InitFonts()::FONTS::STATE could not load one or more fonts from file";
	}
}
