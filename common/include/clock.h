#ifndef RINTPC_CLOCK_H
#define RINTPC_CLOCK_H

#include "constants.h"

namespace rintpc {

class Clock{
public:
    Clock(int frequency);
    void RINTPC_BLOCKING sleep();

private:
    int frequency;
};

}

#endif //RINTPC_CLOCK_H