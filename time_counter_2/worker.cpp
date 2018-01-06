#include "worker.h"



bool worker::checkClick(float mouse_x, float mouse_y)
{
	if ((str != "+") && (str != ""))
	{
		if (is_click)
		{
			if (!(sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				is_click = false;
				return true;
			}
		}
		else
		{
			if (contur.getGlobalBounds().contains(mouse_x, mouse_y))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					first_click = clock.restart();
					is_click = true;
				}
			}
		}
	}
	return false;
}

void worker::statusChange(float mouse_x, float mouse_y)
{
	switch (status)
	{
	case worker::is_not_clicked:

		if (checkClick(mouse_x, mouse_y))
		{
			status = is_clicked;
			std::time(&start_time);
		}
		contur.setFillColor(sf::Color::Green);
		break;
	case worker::is_clicked:

		has_worked = true;

		if (checkClick(mouse_x, mouse_y))
		{
			if ((first_click > sf::seconds(0.0f)) && (first_click < sf::seconds(0.5f)))
			{
				//status = is_double_clicked;
			}
			else
			{
				status = is_not_clicked;
				std::time(&stop_time);
				minutes = difftime(stop_time, start_time)/3600;
				//minutes = std::round(minutes);
			}
		}
		contur.setFillColor(sf::Color::Red);
		break;
	case worker::is_double_clicked:

		if (checkClick(mouse_x, mouse_y))
		{
			status = is_not_clicked;
		}
		contur.setFillColor(sf::Color::Transparent);
		break;
	default:
		break;
	}
	return;
}

void worker::Process()
{
	return;
}

void worker::Display(sf::RenderWindow *window)
{
	window->draw(contur);
	window->draw(text);
	return;
}

worker::worker()
{
	has_worked = false;
	minutes = 0;

	is_click = false;
	status = is_not_clicked;
}

worker::~worker()
{
}
