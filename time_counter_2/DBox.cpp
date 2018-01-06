#include "DBox.h"

bool DBox::is_editable = true;

//	Setting the font, event and initial position
void DBox::Initialize(sf::Font *a_font,sf::Event *a_event, float x, float y)
{
	font            = a_font;
	event           = a_event;
	position.x      = x;
	position.y      = y;

	is_text_entered = false;

	contur.setSize(sf::Vector2f(180, 35));
	contur.setOutlineColor(sf::Color::Black);
	contur.setOutlineThickness(2);
	contur.setFillColor(sf::Color::White);
	contur.setPosition(position);

	str = "+";
	text.setFont(*font);
	text.setString(str);
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(1);
	text.setOutlineColor(sf::Color::Black);
	text.setPosition((position.x + 10), (position.y));
	return;
}

// Getting input from keybord
void DBox::TextInput(float mouse_x, float mouse_y)
{
	if (is_editable)
	{
		if (contur.getGlobalBounds().contains(mouse_x, mouse_y))
		{
			if (event->mouseButton.button == sf::Mouse::Right)
			{
				text.setFillColor(sf::Color::Magenta);
				is_editable = false;
			}
		}
	}
	else
	{
		if (text.getFillColor() == sf::Color::Magenta)
		{
			if (event->type == sf::Event::TextEntered)
			{
				if (is_text_entered == false)
				{
					// Getting input from keyboard

					c = event->text.unicode;
					is_text_entered = true;
				}
			}
			else
			{
				if (is_text_entered)
				{
					switch (c)
					{
					case 8: // Backspace key
					{
						if (str.length() > 0)
						{
							str.pop_back();
							text.setString(str);
							is_text_entered = false;
							break;
						}
					}
					case 13: // Return key
					{
						if (str.length() == 0)
						{
							str += '+';
							text.setString(str);
						}
						text.setFillColor(sf::Color::White);
						is_text_entered = false;
						is_editable = true;
						break;
					}
					default: // Default
					{
						if (str.length() < 15)
						{
							str += c;
							text.setString(str);
							is_text_entered = false;
							break;
						}
						else
						{
							is_text_entered = false;
							break;
						}
					}
					}
				}
			}
		}
	}
	return;
}

void DBox::SetPosition(sf::Vector2f v)
{
	contur.setPosition(v);
	text.setPosition((v.x + 10), (v.y));

	return;
}

DBox::DBox()
{
}

DBox::~DBox()
{
}
