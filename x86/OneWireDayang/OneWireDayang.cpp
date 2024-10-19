#include "../../onewire.ino"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>
#include <map>

std::map<unsigned, bool> g_data_samples;
const size_t VALUES_COUNT = 10005;

unsigned parse_timestamp(const std::string& line)
{
	unsigned time_stamp = 0;
	if (line.size())
	{
		std::stringstream ss(line.substr(1, std::string::npos));
		ss >> time_stamp;
	}

	return (time_stamp);
}

bool parse_value(const std::string& line)
{
	bool var_val = 0;
	if (line.size())
	{
		std::stringstream ss(line.substr(0, line.size() - 1));
		ss >> var_val;
	}

	return var_val;
}

int main(int argc, char* argv[])
{
	std::ifstream vcd_file;
	std::string line;

	vcd_file.open(argv[1]);

	//Get initial val
	getline(vcd_file, line);
	bool var_value = parse_value(line);

	g_data_samples[0] = (var_value);

	long prev_time_stamp = 0;
	long time_stamp = 0;
	
	for (auto i = 1; i < VALUES_COUNT; ++i) 
	{
		getline(vcd_file, line);
		time_stamp = parse_timestamp(line); 
		getline(vcd_file, line);
		var_value = parse_value(line);

		g_data_samples[time_stamp] = var_value;
	}

	setup();

	while (true)
	{
		loop();
	}
}
