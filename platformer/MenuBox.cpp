#include "stdafx.h"
#include "MenuBox.h"


MenuBox::MenuBox(float height_, float width_, float posX_, float posY_, std::string text_, sf::Font font_, int fontSize_) 
{
	this->size.x = height_;
	this->size.y = width_;
	this->shape.setSize(this->size);
	this->shape.setPosition(posX_,posY_);
	this->shape.setFillColor(sf::Color::Transparent);

	this->font = font_;
	this->text.setPosition((posX_ + size.x) / 2, (posY_ + size.y/2));
	this->text.setFont(this->font);
	this->text.setCharacterSize(fontSize_);
	this->text.setFillColor(sf::Color::White);
	this->text.setString(text_);

	this->imageExists = false;
}

MenuBox::MenuBox(float height_, float width_, float posX_, float posY_, std::string imagePath_)
{
	this->size.x = height_;
	this->size.y = width_;
	this->shape.setSize(this->size+sf::Vector2f(2.f,2.f));
	this->shape.setPosition(posX_, posY_);
	this->shape.setFillColor(sf::Color::Transparent);

	this->image.setPosition(posX_+1.f, posY_+1.f);
	if (this->imageTexture.loadFromFile(imagePath_))
		this->image.setTexture(this->imageTexture);
	this->imageExists = true;

}

MenuBox::~MenuBox()
{
}

const sf::FloatRect MenuBox::getPanelBounds() const
{
	return this->shape.getGlobalBounds();
}

void MenuBox::changeTextColor(sf::Color color_)
{
	this->text.setFillColor(color_);
}

void MenuBox::changeBoxColor(sf::Color color_)
{
	this->shape.setFillColor(color_);
}


void MenuBox::update()
{
}

void MenuBox::render(sf::RenderTarget& target)
{
	
	target.draw(this->shape);

	if (this->imageExists)	//check if image actually exists (second constructor has been called)
		target.draw(this->image);
	else
		target.draw(this->text);
}
