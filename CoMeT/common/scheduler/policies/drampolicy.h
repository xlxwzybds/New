/**
 * This header implements the DRAM policy interface.
 */

#ifndef __DRAMPOLICY_H
#define __DRAMPOLICY_H

#include <map>

#define LOW_POWER 0
#define NORMAL_POWER 1
#define POWER9 9
#define POWER8 8
#define POWER7 7
#define POWER6 6
#define POWER5 5

class DramPolicy {
public:
    virtual ~DramPolicy() {}
    virtual std::map<int, int> getNewBankModes(std::map<int, int> old_bank_modes) = 0;
};

#endif
