#include "motor_protection.h"

#include <cmath>
#include <stdexcept>

MotorProtection::MotorProtection(ProtectionConfig config) : config_(config) {
    const bool finite = std::isfinite(config_.tripTemperatureC) &&
                        std::isfinite(config_.resetTemperatureC) &&
                        std::isfinite(config_.minSensorC) &&
                        std::isfinite(config_.maxSensorC);
    if (!finite || config_.minSensorC > config_.resetTemperatureC ||
        config_.resetTemperatureC >= config_.tripTemperatureC ||
        config_.tripTemperatureC > config_.maxSensorC) {
        throw std::invalid_argument("Invalid motor protection configuration");
    }
}

MotorState MotorProtection::update(double temperatureCelsius) {
    if (!std::isfinite(temperatureCelsius) ||
        temperatureCelsius < config_.minSensorC ||
        temperatureCelsius > config_.maxSensorC) {
        // Fail-safe: sensor hatasinda motoru durdurulmus kabul et.
        // Hata kalkinca sicaklik reset esigine kadar dusmeden alarm acilmaz.
        alarmLatched_ = true;
        state_ = MotorState::SensorFault;
        return state_;
    }

    if (temperatureCelsius >= config_.tripTemperatureC) {
        alarmLatched_ = true;
    } else if (temperatureCelsius <= config_.resetTemperatureC) {
        alarmLatched_ = false;
    }

    state_ = alarmLatched_ ? MotorState::Alarm : MotorState::Normal;
    return state_;
}

MotorState MotorProtection::state() const {
    return state_;
}

const char* toString(MotorState state) {
    switch (state) {
        case MotorState::Normal: return "NORMAL";
        case MotorState::Alarm: return "ALARM";
        case MotorState::SensorFault: return "SENSOR_FAULT";
    }
    return "UNKNOWN";
}
