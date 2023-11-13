#include <unistd.h>

#include "clock.h"

namespace rintpc {

constexpr unsigned int MICRO_SECONDS = 1000000; 

Clock::Clock(int frequency): frequency(frequency) {}
    
void RINTPC_BLOCKING Clock::sleep(){
    usleep(MICRO_SECONDS / this->frequency);
}

}