#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>

std::vector<unsigned int> g_delays;
std::vector<bool> g_values;
bool g_sim_output = false;


void setOutput(bool var_val)
{
	g_sim_output = var_val;
	
	std::cout << var_val << std::endl;
}

unsigned parse_timestamp(const std::string& line)
{
	unsigned time_stamp = 0;
	if(line.size())
	{
		std::stringstream ss(line.substr(1, std::string::npos));
		ss >> time_stamp;
	}
	
	return time_stamp;
}

bool parse_value(const std::string& line)
{
	bool var_val = 0;
	if(line.size())
	{
		std::stringstream ss(line.substr(0, line.size() - 1));
		ss >> var_val;
	}
	
	return var_val;
}

void delay(unsigned time_stamp)
{
	std::this_thread::sleep_for(std::chrono::microseconds(time_stamp));
}
	
int main(int argc, char* argv[])
{
	std::ifstream vcd_file;
	std::string line;
	
	vcd_file.open(argv[1]);
	
	g_delays.reserve(10000);
	g_values.reserve(10000);
	
	//Get initial val
	getline(vcd_file, line);	
	bool var_value = parse_value(line);
	//setOutput(var_value);
	g_values.push_back(var_value);
	
	unsigned prev_time_stamp = 0;
	unsigned time_stamp = 0;
	g_delays.push_back(0);

	while(getline(vcd_file, line))
	{
		time_stamp = parse_timestamp(line);

		//delay(time_stamp - prev_time_stamp);
		g_delays.push_back(time_stamp - prev_time_stamp);
		prev_time_stamp = time_stamp;
	
		if(getline(vcd_file, line))
		{
			var_value = parse_value(line);
			//setOutput(var_value);
			g_values.push_back(var_value);
		}
		else
		{
			break;
		}
	}
	
	std::cout << g_delays.size() << std::endl;
	std::cout << g_values.size() << std::endl;


	for(auto i  = 0; i < g_values.size(); i++)
	{
		delay(g_delays[i]);
		//std::cout << g_delays[i] << " ";
		setOutput(g_values[i]);
	}
	
}