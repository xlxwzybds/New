#include <algorithm>
#include <iostream>
#include "powermodel.h"
#include "simulator.h"
#include "config.hpp"
#include <fstream>

using namespace std;

/**
 * Calculate the frequency that is expected to cause a power consumption as close as possible to the power budget, but still respecting it.
 */
int PowerModel::getExpectedGoodFrequency(int currentFrequency, float powerConsumption, float powerBudget, int minFrequency, int maxFrequency, int frequencyStepSize) {
	int expectedGoodFrequency = minFrequency;
	float alpha = 1.0;
	//float alpha = 1 ;
	float new_gdp_power = powerBudget * alpha ;
	//printf("current_freq is %d \n", currentFrequency);
	//printf("powerConsumption is %f \n", powerConsumption);
	//printf("powerBudget is %f \n", powerBudget);
	//printf("frequencyStepSize is %d \n", frequencyStepSize);
	for (int f = minFrequency; f <= maxFrequency; f += frequencyStepSize) {
		//printf("the f now is %d \n", f);
		float expectedPower = estimatePower(currentFrequency, powerConsumption, f);
		//if (expectedPower <= powerBudget * 1.2) {
		if ( expectedPower <= new_gdp_power) {
			expectedGoodFrequency = f;
		}
	}

	// add benchmark name identify	
	std::string benchmark_name;
        std::ifstream infile("./system_sim_state_3D/benchmark_name.txt");
        if (!infile.is_open()) {
            std::cerr << "Error: Cannot open file.\n";
            return 1;
        }
        std::getline(infile, benchmark_name);
        infile.close();
        benchmark_name.erase(benchmark_name.find_last_not_of(" \n\r\t") + 1);


	int max_freq;
        if (benchmark_name == "blackscholes") {
		max_freq = 4000;
	}else if (benchmark_name == "swaption") {
		max_freq = 4000;
	}else if (benchmark_name == "bodytrack") {
		max_freq = 2500;
	}else if (benchmark_name == "streamcluster") {
		max_freq = 2500;
	}else if (benchmark_name == "dedup") {
		max_freq = 2500;
        }



	//if (expectedGoodFrequency > maxFrequency) {
	if (expectedGoodFrequency > max_freq) {
		//expectedGoodFrequency = maxFrequency;
		expectedGoodFrequency = max_freq;
	}
	if (expectedGoodFrequency < minFrequency) {
		expectedGoodFrequency = minFrequency;
	}
	return expectedGoodFrequency;
}

/** estimatePower
 * Get the estimated power consumption when switching to the new frequency.
 */
float PowerModel::estimatePower(int currentFrequency, float currentPowerConsumption, int newFrequency) {

	float staticFreqA = Sim()->getCfg()->getFloat("power/static_frequency_a") * 1000;
	float staticFreqB = Sim()->getCfg()->getFloat("power/static_frequency_b") * 1000;
	float staticPowerA = Sim()->getCfg()->getFloat("power/static_power_a");
	float staticPowerB = Sim()->getCfg()->getFloat("power/static_power_b");
	const float staticPowerM = (staticPowerB - staticPowerA) / (staticFreqB - staticFreqA);
	const float staticPowerOffset = staticPowerA - staticPowerM * staticFreqA;
	const float staticPower = staticPowerM * currentFrequency + staticPowerOffset;

	if (currentPowerConsumption <= staticPower) {
		currentPowerConsumption = staticPower;
	}

	//printf("current F is %d \n", currentFrequency);
	float dynamicPower = (currentPowerConsumption - staticPower);  // 90T
	//printf("The dynamicPower is %f \n", dynamicPower);
	float cun_f = float(currentFrequency) / 1000;
	float new_f = float(newFrequency) / 1000;
	//printf("cun_f is %f \t", cun_f);
	//printf("new_f is %f \n" , new_f);
	//float a = dynamicPower / (currentFrequency * currentFrequency * currentFrequency /(1000*1000*1000)  );
	float a = dynamicPower / ( cun_f * cun_f * cun_f );
	//printf("The a of afff is %f \n", a);
	//float expectedPower = staticPowerM * newFrequency + staticPowerOffset + a * (newFrequency * newFrequency * newFrequency/(1000*1000*1000) );
	float expectedPower = staticPowerM * newFrequency + staticPowerOffset + a * (new_f * new_f * new_f );
	//printf("The expectpower is %f \n", expectedPower);
	return expectedPower;
}

