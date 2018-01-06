#include "DataBase.h"


IOExcel      DataBase::ExcelInstance;


void DataBase::GetTime()
{
	time_t getting_time = time(NULL);
	localtime_s(&timePtr, &getting_time);

	return;
}

std::string DataBase::SetFileName()
{
	std::string s = "-";

	switch (timePtr.tm_mon)
	{
	case 0:
		s += "january";
		break;
	case 1:
		s += "february";
		break;
	case 2:
		s += "march";
		break;
	case 3:
		s += "april";
		break;
	case 4:
		s += "may";
		break;
	case 5:
		s += "june";
		break;
	case 6:
		s += "july";
		break;
	case 7:
		s += "august";
		break;
	case 8:
		s += "september";
		break;
	case 9:
		s += "october";
		break;
	case 10:
		s += "november";
		break;
	default:
		s += "decembre";
		break;
	}
	s += std::to_string(timePtr.tm_year + 1900);

	return s;
}

void DataBase::ReadWriteExcel()
{
	for (size_t i = 0; i < worker_db.size(); i++)
	{
		if (worker_db[i].has_worked)
		{
			if (worker_db[i].status == DBox::states::is_not_clicked)
			{
				std::string file_name = "C:\\Time report\\Time report ";
				file_name += worker_db[i].str;
				file_name += SetFileName();
				file_name += ".xlsx";

				ExcelInstance.Close_Workbook();
				ExcelInstance.Open_Workbook(file_name);
				int sheet_colon = ExcelInstance.Find_Project(worker_db[i].project_name);

				ExcelInstance.Write_Double(sheet_colon, timePtr.tm_mday + 1, worker_db[i].minutes);
				ExcelInstance.Write_String(sheet_colon, 1, worker_db[i].project_name);

				ExcelInstance.Save_Workbook();
				worker_db[i].has_worked = false;
			}
		}
	}
	return;
}

void DataBase::GetBackup()
{
	std::ifstream file("backup");
	char read_chr(' ');

	std::string line_str;
	std::vector<std::string> v_str;

	v_str.resize(1);
	size_t v_size = 0;

	while (file.is_open())
	{
		if (file.peek() == EOF)
		{
			file.close();
		}
		else
		{
			file.get(read_chr);

			if (read_chr == '.')
			{
				sf::Vector2f v = setProjectPosition((float)(no_project));
				no_project++;
				project_db.resize(no_project);

				last_project.Initialize(font, event, v.x, v.y);
				last_project.str = v_str[0];
				last_project.text.setString(v_str[0]);

				if (last_project.str != "+")
				{
					v_str.erase(v_str.begin());
					last_project.Add(v_str);
				}
				v_str.clear();
				v_str.resize(1);

				v_size = 0;
			}
			else
			{
				if (read_chr == ' ')
				{
					v_size++;
					v_str.resize(v_size + 1);
				}
				else
				{
					v_str[v_size] += read_chr;
				}
			}
		}
	}
	return;
}

void DataBase::SaveBeforeExit()
{
	for (size_t i = 0; i < worker_db.size(); i++)
	{
		worker_db[i].status = DBox::states::is_not_clicked;
	}
	std::ofstream f("backup");
	
	for (size_t i = 0; i < project_db.size(); i++)
	{
		f << project_db[i].str;

		if (worker_db.size() > 0)
		{
			for (size_t j = 0; j < project_db[i].i_worker.size(); j++)
			{
				//f << " " << project_db[i].i_worker[j] << " " << worker_db[project_db[i].i_worker[j]].str;
				f << " " << worker_db[project_db[i].i_worker[j]].str;
			}
		}
		f << '.';
	}
	f.close();

	ReadWriteExcel();
	ExcelInstance.Close_Workbook();

	window->close();
	return;
}

void DataBase::Add()
{
	// Adding project

	if (no_project < PROJECT_MAX_SIZE)
	{
		if (last_project.text.getFillColor() != sf::Color::Magenta)
		{
			if (last_project.str != "+")
			{
				// Project cannot be added with an existing name

				for (size_t i = 0; i < (project_db.size() - 1); i++)
				{
					if (last_project.str == project_db[i].str)
					{
						last_project.str = "+";
						last_project.text.setString(last_project.str);
						last_project.text.setFillColor(sf::Color::White);
					}
				}
				sf::Vector2f project_v = setProjectPosition((float)(no_project));

				no_project++;
				project_db.resize(no_project);

				last_project.Initialize(font, event, project_v.x, project_v.y);
			}
		}
	}
	return;
}

void DataBase::Remove()
{
// Removing projects
	bool erased = false;

	if (no_project > MIN_SIZE)
	{
		for (size_t i = 0; i < (project_db.size() - 1); i++)
		{
			if ((project_db[i].str == "+") && (project_db[i].text.getFillColor() != sf::Color::Magenta))
			{
				no_project--;
				last_project.is_selected = false;
				project_db.erase(project_db.begin() + i);

				erased = true;
			}
		}
	}
	if (erased)
	{
		for (size_t i = 0; i < project_db.size(); i++)
		{
			project_db[i].SetPosition(setProjectPosition((float)i));
		}
		erased = false;
	}
	return;
}

sf::Vector2f DataBase::setProjectPosition(float position)
{
	sf::Vector2f v;
	if (position > 0)
	{
		float y_pos = floor(position / 5);
		int x_pos = (int)position % 5;

		v.x = ((200 * (float)x_pos) + 20);
		v.y = (y_pos * 50) + 10;
	}
	else
	{
		v.x = 20;
		v.y = 10;
	}
	return v;
}

DataBase::DataBase(sf::RenderWindow *a_window, sf::Event *a_event, sf::Font *a_font)
{
	window = a_window;
	event  = a_event;
	font   = a_font;

	project::p_worker = &worker_db;

	no_project = 0;

	if (BackupExists("backup"))
	{
		GetBackup();
	}
	else
	{
		no_project = 1;
		project_db.resize(no_project);
		project_db[0].Initialize(font, event, 20, 10);
	}

	GetTime();

	return;
}

void DataBase::Process(float mouse_x, float mouse_y)
{
	if (window->hasFocus())
	{
		for (size_t i = 0; i < project_db.size(); i++)
		{
			project_db[i].Process(mouse_x, mouse_y);
		}
		Add();
		Remove();
		WorkerProcess();

		ReadWriteExcel();
	}

	return;
}

void DataBase::WorkerProcess()
{
	for (size_t i = 0; i < worker_db.size(); i++)
	{
		if (worker_db[i].status == DBox::states::is_clicked)
		{
			for (size_t j = 0; j < worker_db.size(); j++)
			{
				if (j != i)
				{
					if (worker_db[i].str == worker_db[j].str)
					{
						if (worker_db[j].status == DBox::states::is_clicked)
						{
							worker_db[j].status = DBox::states::is_not_clicked;
							worker_db[i].status = DBox::states::is_not_clicked;
						}
					}
				}
			}
		}
	}
	return;
}

void DataBase::Display()
{
	for (size_t i = 0; i < project_db.size(); i++)
	{
		project_db[i].Display(window);
	}
	return;
}

DataBase::~DataBase()
{
	return;
}
