#include "motor_protection.h"

#include <iostream>
#include <limits>
#include <stdexcept>

int failures = 0;
int checks = 0;

void check(const char* description, MotorState actual, MotorState expected) {
    ++checks;
    if (actual == expected) {
        std::cout << "[PASS] " << description << "\n";
    } else {
        ++failures;
        std::cerr << "[FAIL] " << description
                  << " (expected " << toString(expected)
                  << ", got " << toString(actual) << ")\n";
    }
}

int main() {
    MotorProtection monitor;
    check("initial state", monitor.state(), MotorState::Normal);
    check("cold", monitor.update(25.0), MotorState::Normal);
    check("just below trip", monitor.update(74.9), MotorState::Normal);
    check("trip boundary", monitor.update(75.0), MotorState::Alarm);
    check("alarm remains latched", monitor.update(73.0), MotorState::Alarm);
    check("reset boundary", monitor.update(70.0), MotorState::Normal);
    check("hot", monitor.update(100.0), MotorState::Alarm);
    check("maximum valid sensor reading", monitor.update(150.0), MotorState::Alarm);
    check("out of range high", monitor.update(150.1), MotorState::SensorFault);
    check("fault recovery stays safe", monitor.update(72.0), MotorState::Alarm);
    check("recover after cooling", monitor.update(69.0), MotorState::Normal);
    check("out of range low", monitor.update(-40.1), MotorState::SensorFault);
    check("minimum valid value recovers", monitor.update(-40.0), MotorState::Normal);
    check("NaN is a sensor fault", monitor.update(std::numeric_limits<double>::quiet_NaN()),
          MotorState::SensorFault);

    ProtectionConfig custom;
    custom.tripTemperatureC = 80.0;
    custom.resetTemperatureC = 75.0;
    MotorProtection modified(custom);
    check("custom below trip", modified.update(79.9), MotorState::Normal);
    check("custom trip", modified.update(80.0), MotorState::Alarm);
    check("custom hysteresis", modified.update(77.0), MotorState::Alarm);
    check("custom reset", modified.update(75.0), MotorState::Normal);

    bool rejectedInvalidConfig = false;
    try {
        ProtectionConfig invalid;
        invalid.tripTemperatureC = 65.0;
        MotorProtection shouldFail(invalid);
    } catch (const std::invalid_argument&) {
        rejectedInvalidConfig = true;
    }
    ++checks;
    if (rejectedInvalidConfig) {
        std::cout << "[PASS] invalid configuration rejected\n";
    } else {
        ++failures;
        std::cerr << "[FAIL] invalid configuration accepted\n";
    }

    std::cout << "Checks: " << checks << ", failures: " << failures << "\n";
    return failures == 0 ? 0 : 1;
}
