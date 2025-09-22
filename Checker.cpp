#include <assert.h>
#include <iostream>
#include <string>
using namespace std;

enum class BreachType { LOW, HIGH, NORMAL };

struct Limit {
    float min;
    float max;
};

// Generic check function (pure)
BreachType checkLimit(float value, const Limit& limit) {
    if(value < limit.min) return BreachType::LOW;
    if(value > limit.max) return BreachType::HIGH;
    return BreachType::NORMAL;
}

// Convert breach type to string (pure)
string breachToString(BreachType breach) {
    switch(breach) {
        case BreachType::LOW: return "LOW";
        case BreachType::HIGH: return "HIGH";
        case BreachType::NORMAL: return "NORMAL";
    }
    return "UNKNOWN";
}

// Report check (I/O separate)
void reportStatus(const string& name, BreachType breach) {
    if(breach != BreachType::NORMAL) {
        cout << name << " is " << breachToString(breach) << "!\n";
    }
}

// Battery validation (composition of pure functions)
bool batteryIsOk(float temperature, float soc, float chargeRate) {
    bool status = true;

    BreachType tempStatus = checkLimit(temperature, {0, 45});
    BreachType socStatus = checkLimit(soc, {20, 80});
    BreachType chargeStatus = checkLimit(chargeRate, {0, 0.8});

    reportStatus("Temperature", tempStatus);
    reportStatus("State of Charge", socStatus);
    reportStatus("Charge Rate", chargeStatus);

    if(tempStatus != BreachType::NORMAL) status = false;
    if(socStatus != BreachType::NORMAL) status = false;
    if(chargeStatus != BreachType::NORMAL) status = false;

    return status;
}

// ✅ Tests
int main() {
    // Normal values
    assert(batteryIsOk(25, 70, 0.7) == true);

    // Temperature too high
    assert(batteryIsOk(50, 70, 0.7) == false);

    // Temperature too low
    assert(batteryIsOk(-5, 70, 0.7) == false);

    // SOC too high
    assert(batteryIsOk(25, 85, 0.7) == false);

    // SOC too low
    assert(batteryIsOk(25, 10, 0.7) == false);

    // Charge rate too high
    assert(batteryIsOk(25, 70, 0.9) == false);

    // Multiple failures
    assert(batteryIsOk(50, 85, 0.9) == false);

    cout << "All tests passed!\n";
}
