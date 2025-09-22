#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class BreachType { LOW, HIGH, NORMAL };

struct Limit {
    float min;
    float max;
};

struct Measurement {
    string name;
    float value;
    Limit limit;
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
        default: return "NORMAL";
    }
}

// Report abnormal status only (I/O separate)
void reportStatus(const Measurement& m, BreachType breach) {
    if(breach != BreachType::NORMAL) {
        cout << m.name << " is " << breachToString(breach) << "!\n";
    }
}

// Battery validation (loop over all checks)
bool batteryIsOk(const vector<Measurement>& measurements) {
    bool status = true;
    for(const auto& m : measurements) {
        BreachType breach = checkLimit(m.value, m.limit);
        reportStatus(m, breach);
        if(breach != BreachType::NORMAL) status = false;
    }
    return status;
}

// ✅ Tests
int main() {
    vector<Measurement> case1 = {
        {"Temperature", 25, {0, 45}},
        {"State of Charge", 70, {20, 80}},
        {"Charge Rate", 0.7, {0, 0.8}}
    };
    assert(batteryIsOk(case1) == true);

    vector<Measurement> case2 = {
        {"Temperature", 50, {0, 45}},
        {"State of Charge", 85, {20, 80}},
        {"Charge Rate", 0.9, {0, 0.8}}
    };
    assert(batteryIsOk(case2) == false);

    vector<Measurement> case3 = {
        {"Temperature", -5, {0, 45}},
        {"State of Charge", 10, {20, 80}},
        {"Charge Rate", 0.7, {0, 0.8}}
    };
    assert(batteryIsOk(case3) == false);

    cout << "All tests passed!\n";
}
