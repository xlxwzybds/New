#include "dramLowpower.h"
#include <iomanip>
#include <iostream>
#include <map>

#include <sstream>
#include <fstream>
#include <string>

using namespace std;

DramLowpower::DramLowpower(
        const PerformanceCounters *performanceCounters,
        int numberOfBanks,
        float dtmCriticalTemperature,
        float dtmRecoveredTemperature)
    : performanceCounters(performanceCounters),
      numberOfBanks(numberOfBanks),
      dtmCriticalTemperature(dtmCriticalTemperature),
      dtmRecoveredTemperature(dtmRecoveredTemperature) {

}

/*
Return the new memory modes, based on current temperatures.
*/
std::map<int,int> DramLowpower::getNewBankModes(std::map<int, int> old_bank_modes) {

    cout << "in DramLowpower::getNewBankModes\n";
    std::map<int,int> new_bank_mode_map;
	


	// XJY add 3D-GDP LOWPOWER Policy here
	std::string file_path = "./system_sim_state_3D/frequency_bank.txt";
	std::ifstream bank_file(file_path);
	if (!bank_file.is_open()) {
                 std::cerr << "Error: Could not open file " << file_path << std::endl;
        }
	std::cerr << "Value is below" << std::endl;
	std::string bank_line;
	std::vector<double> frequency_vector;
	if (std::getline(bank_file, bank_line)){
		std::stringstream ss(bank_line);
		double value;
		while (ss >> value) {
			//std::cerr << value << std::endl;
			frequency_vector.push_back(value);
		}
	}
	

	
	//
	std::string filename = "./system_sim_state/mapping.txt";
	std::ifstream infile(filename);
	if (!infile.is_open()) {
		std::cerr << "Error: Could not open file " << filename << std::endl;
	}

	std::string line;
	if (std::getline(infile, line)) {
		// std::map<int, int> new_bank_modes_map;
		std::istringstream iss(line);
		int index = 0;
		int key;
		int value;
		
		double bank_power =0;
		int bank_idex = 0;
		// Parse the line into the map
		std::cerr << "value to bank mode is below" << std::endl;
		while (iss >> value) {
			if (value == 1.00){

				bank_power = frequency_vector[bank_idex];
				//std::cerr << bank_power << std::endl;

				if (bank_power ==0.4 )
					new_bank_mode_map[index] = LOW_POWER;
				else if ( bank_power==0.5 )
					new_bank_mode_map[index] = POWER5;
				else if ( bank_power==0.6 )
					new_bank_mode_map[index] = POWER6;
				else if ( bank_power==0.7 )
					new_bank_mode_map[index] = POWER7;
				else if ( bank_power==0.8 )
					new_bank_mode_map[index] = POWER8;
				else if ( bank_power==0.9 )
					new_bank_mode_map[index] = POWER9;
				else if (bank_power ==1.0)
					new_bank_mode_map[index] = NORMAL_POWER;
				++bank_idex;

			}
			else 
				new_bank_mode_map[index] = NORMAL_POWER;
			++index;
		}
		// Print the map to verify
		//for (const auto& pair : new_bank_mode_map) {
		//	std::cout << "Index: " << pair.first << ", Value: " << pair.second << std::endl;
		//}
	} else {
		std::cerr << "Error: Could not read the first line from file." << std::endl;
	}
	infile.close();
	bank_file.close();
	// XJY ADD Code END Here

    return new_bank_mode_map;
}
