#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <algorithm>

#include <fstream>
#include <time.h>
#include <string.h>

#include "project.h"
#include "IOExcel.h"

#define PROJECT_MAX_SIZE 20
#define MIN_SIZE 1
#define last_project project_db[no_project - 1]



class DataBase
{
private:
	tm							timePtr;
	size_t						no_project;

	sf::RenderWindow			*window;
	sf::Event					*event;
	sf::Font					*font;

	void Add();													// adding projects
	void Remove();												// removing projects
	
	void WorkerProcess();										// workers cannot work at two project in the same time
	sf::Vector2f setProjectPosition(float position);			// next available position depending of no_project

	void GetBackup();
	inline bool BackupExists(const std::string& name){ std::ifstream f(name.c_str()); return f.good();}

	std::string SetFileName();
	void GetTime();

public:
	static IOExcel      ExcelInstance;

	void ReadWriteExcel();

	// Container for workers
	std::vector<worker> worker_db;

	// Container for projects
	std::vector<project> project_db;

	// Constructor
	DataBase(sf::RenderWindow *a_window, sf::Event *a_event, sf::Font *a_font);

	// Processing
	void Process(float mouse_x, float mouse_y);

	// Display
	void Display();

	void SaveBeforeExit();

	~DataBase();
};
