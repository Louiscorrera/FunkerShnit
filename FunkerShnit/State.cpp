#include "stdafx.h"
#include "State.h"



void GfxSettings::loadGfxFromFile(std::string GfxFileName)
{
	/* Open in file stream to read from window config file */
	std::ifstream ifs("Config/window_config.txt");
	if (ifs.is_open() == false)
	{
		std::cout << "ERROR::InitWindow()::Game Window config file could not be opened to initialize window\n";
	}

	/* Defaults */
	this->resolution = sf::VideoMode::getDesktopMode();
	this->title = "Default";
	this->fullscreen = false;
	this->verticalSyncEnabled = false;
	this->frameRateLimit = 120;

	/* GridSize */
	this->gridSizeF = 50.f;

	/* Take in data from window config file */
	ifs >> this->resolution.width >> this->resolution.height;
	ifs >> this->title;
	ifs >> this->fullscreen;
	ifs >> this->frameRateLimit;
	ifs >> this->gridSizeF;

	ifs.close();
}

void GfxSettings::saveGfxToFile(std::string GfxFileName)
{
	/* Open out file stream to read from window config file */
	std::ofstream ofs("Config/window_config.txt");
	if (ofs.is_open() == false)
	{
		std::cout << "ERROR::InitWindow()::Game Window config file could not be opened to initialize window\n";
	}

	/* Send \out data from window config file */
	ofs << this->resolution.width << " " << this->resolution.height << " ";
	ofs << this->title << " ";
	ofs << this->fullscreen << " ";
	ofs << this->frameRateLimit << " ";
	ofs << this->gridSizeF;

	ofs.close();
}


StateData::StateData()
{
	this->gfxSettings = new GfxSettings();
	this->gfxSettings->loadGfxFromFile("GFX file settings path");
	this->initGridSize();
	this->initFontsColors();
}





State::State(StateData* state_data)
{
	this->stateData = state_data;


	this->quit = false;

	/* Keys & Time inits */
	this->keyTime = 0.f;
	this->keyTimeMax = 15.f;

}

State::~State()
{
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
	this->mousePosWindow = sf::Mouse::getPosition(*this->stateData->window);

	if (view)
	{
		this->stateData->window->setView(*view);
	}
	else
	{
		this->stateData->window->setView(this->stateData->window->getDefaultView());
	}
	this->mousePosView = this->stateData->window->mapPixelToCoords(sf::Mouse::getPosition(*this->stateData->window));
	this->mousePosGrid = sf::Vector2u(
		static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->stateData->gfxSettings->gridSizeF),
		static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->stateData->gfxSettings->gridSizeF)
	);
	//Debug
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




