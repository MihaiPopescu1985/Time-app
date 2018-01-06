#pragma once
#include "DBox.h"
#include <time.h>
#include <string>


class worker : public DBox
{
private:
	bool				is_click;
	sf::Time			first_click;
	sf::Clock			clock;

	time_t				start_time;
	time_t				stop_time;

	bool checkClick(float mouse_x, float mouse_y); // 
public:
	std::string			project_name;
	bool				has_worked;
	double				minutes;

// Is not clicked, is clicked once, is double clicked
	void statusChange(float mouse_x, float mouse_y);

	void Process(); // To be checked
	void Display(sf::RenderWindow *window);

	worker();
	~worker();
};

