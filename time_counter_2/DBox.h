#pragma once
#include <string>
#include <SFML\Graphics.hpp>

class DBox
{
private:
	char                c;
public:
	static bool         is_editable;
	bool                is_text_entered;

	sf::Font            *font;
	sf::Event			*event;
	sf::Vector2f		position;

	std::string         str;
	sf::Text            text;
	sf::RectangleShape  contur;

	enum states { is_not_clicked, is_clicked, is_double_clicked } status;

// Setting position
	void SetPosition(sf::Vector2f v);

//	Setting the font, event and initial position 
	void Initialize(sf::Font *a_font, sf::Event *a_event, float x, float y);

// Getting input from keyboard
	void TextInput(float mouse_x, float mouse_y);

	DBox();
	~DBox();
};

