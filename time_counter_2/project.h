#pragma once
#include "DBox.h"
#include "worker.h"
#include <vector>
#include <time.h>

#define WORKER_MAX_SIZE 20
#define no_workers i_worker.size()
#define last_worker p_worker->at(i_worker[no_workers-1])

class project : public DBox
{
private:
	bool				is_click;
	time_t				time;
	sf::Time			first_click;
	sf::Clock			clock;

	double				total_time;
	
	// Adding workers
	void Add();

	bool checkClick(float mouse_x, float mouse_y); 
	sf::Vector2f setWorkerPosition(float position);

public:
	std::vector<int>			i_worker;
	static std::vector<worker>	*p_worker;

	static bool					is_selected;

	void Add(std::vector<std::string> &v_string);

	// Is not clicked, is clicked once, is double clicked
	void statusChange(float mouse_x, float mouse_y);

	// Setting up
	void SettingUp();

	// Processing
	void Process(float mouse_x, float mouse_y);

	// Display
	void Display(sf::RenderWindow *window);

	project();
	~project();
};

