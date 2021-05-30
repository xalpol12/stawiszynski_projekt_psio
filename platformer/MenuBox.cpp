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

void MenuBox::update()
{
}

void MenuBox::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
