#include "project.h"


bool project::is_selected = false;
std::vector<worker>	*project::p_worker;


void project::Add(std::vector<std::string> &v_string)
{
	std::vector<std::string> v_s = v_string;

	size_t v_worker_size = 0;
	sf::Vector2f v_pos;

	for (std::vector<std::string>::iterator it = v_s.begin(); it != v_s.end(); it++)
	{
		v_worker_size = p_worker->size();
		i_worker.push_back(v_worker_size);
		v_pos = setWorkerPosition((float)(no_workers - 1));

		p_worker->resize(v_worker_size + 1);
		p_worker->at(v_worker_size).Initialize(font, event, v_pos.x, v_pos.y);

		p_worker->at(v_worker_size).str = *it;
		p_worker->at(v_worker_size).text.setString(p_worker->at(v_worker_size).str);

		p_worker->at(v_worker_size).project_name = str;
	}
	return;
}

void project::Add()
{
	// Adding workers

	if (no_workers < WORKER_MAX_SIZE)
	{
		if (last_worker.text.getFillColor() != sf::Color::Magenta)
		{
			if (last_worker.str != "+")
			{
				last_worker.project_name = str;

				size_t v_worker_size = p_worker->size();
				i_worker.push_back(v_worker_size);

				sf::Vector2f v_pos = setWorkerPosition((float)(no_workers-1));

				p_worker->resize(v_worker_size + 1);
				p_worker->at(v_worker_size).Initialize(font, event, v_pos.x, v_pos.y);
			}
		}
	}
	return;
}

bool project::checkClick(float mouse_x, float mouse_y)
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

void project::statusChange(float mouse_x, float mouse_y)
{
	switch (status)
	{
	case project::is_not_clicked:
		if (is_selected == false)
		{
			if (checkClick(mouse_x, mouse_y))
			{
				status = is_clicked;
			}
		}
		contur.setFillColor(sf::Color::Green);
		break;
	case project::is_clicked:
		
		is_selected = true;
		if (checkClick(mouse_x, mouse_y))
		{
			if ((first_click > sf::seconds(0.0f)) && (first_click < sf::seconds(0.5f)))
			{
				//status = is_double_clicked;
			}
			else
			{
				status = is_not_clicked;
				is_selected = false;
			}
		}
		contur.setFillColor(sf::Color::Red);
		break;
	case project::is_double_clicked:

		if (checkClick(mouse_x, mouse_y))
		{
			status = is_not_clicked;
			is_selected = false;
		}
		contur.setFillColor(sf::Color::Transparent);
		break;
	default:
		break;
	}
	return;
}

sf::Vector2f project::setWorkerPosition(float position)
{
	float y_pos = floor(position / 5);
	int x_pos = (int)position % 5;
	sf::Vector2f v;

	v.x = ((200 * (float)x_pos) + 20);
	v.y = (y_pos * 50) + 300;

	return v;
}

void project::SettingUp()
{
	if (text.getFillColor() == sf::Color::White)
	{
		if (str != "+")
		{
			if (i_worker.size() == 0)
			{
				size_t v_worker_size = p_worker->size();
				i_worker.push_back(v_worker_size);

				p_worker->resize(v_worker_size + 1);
				p_worker->at(v_worker_size).Initialize(font, event, 20, 300);
			}
			else
			{
				Add();
			}
		}
	}
	return;
}

void project::Process(float mouse_x, float mouse_y)
{
	float x = mouse_x;
	float y = mouse_y;

	TextInput(x, y);
	statusChange(x, y);

	SettingUp();

	if (status == is_clicked)
	{
		for (size_t i = 0; i < no_workers; i++)
		{
			p_worker->at(i_worker[i]).TextInput(x, y);
			p_worker->at(i_worker[i]).statusChange(x, y);
			p_worker->at(i_worker[i]).Process();

			if (p_worker->at(i_worker[i]).status == is_not_clicked)
			{
				total_time += p_worker->at(i_worker[i]).minutes;
			}
		}
	}
	return;
}

void project::Display(sf::RenderWindow *window)
{
	if (status == is_not_clicked)
	{
		window->draw(contur);
		window->draw(text);
	}
	else
	{
		window->draw(contur);
		window->draw(text);

		for (size_t i = 0; i < no_workers; i++)
		{
			p_worker->at(i_worker[i]).Display(window);
		}
	}
	return;
}

project::project()
{
	total_time = 0;

	is_click = false;
	status = is_not_clicked;
}

project::~project()
{
}
