/**
 * performancecounters
 * This header implements the static class PerformanceCounters
 */

#ifndef __PERFORMANCECOUNTERS_H
#define __PERFORMANCECOUNTERS_H

#include <string>
#include <vector>

class PerformanceCounters {
public:
    PerformanceCounters(std::string instPowerFileName, std::string instTemperatureFileName, std::string instCPIStackFileName);
    double getPowerOfComponent (std::string component) const;
    double getPowerOfCore(int coreId) const;
    double getPeakTemperature () const;
    double getTemperatureOfComponent (std::string component) const;
    double getTemperatureOfCore (int coreId) const;
    double getCPIStackPartOfCore(int coreId, std::string metric) const;
    double getUtilizationOfCore(int coreId) const;
    double getCPIOfCore(int coreId) const;
    int getFreqOfCore(int coreId) const;
    double getIPSOfCore(int coreId) const;
    double getTemperatureOfBank(int bankId) const;

    void notifyFreqsOfCores(std::vector<int> frequencies);
private:
    std::vector<int> frequencies;

    std::string instPowerFileName;
    std::string instTemperatureFileName;
    std::string instCPIStackFileName;

    std::vector<std::string> getCPIStackParts() const;
};

#endif
