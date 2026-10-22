#pragma once

// Bu değerler derleme zamanında sabittir (constexpr).
constexpr double kTripTemperatureC = 75.0;
constexpr double kResetTemperatureC = 70.0;
constexpr double kMinimumSensorC = -40.0;
constexpr double kMaximumSensorC = 150.0;

enum class MotorState {
    Normal,
    Alarm,
    SensorFault
};

struct ProtectionConfig {
    double tripTemperatureC = kTripTemperatureC;
    double resetTemperatureC = kResetTemperatureC;
    double minSensorC = kMinimumSensorC;
    double maxSensorC = kMaximumSensorC;
};

class MotorProtection {
public:
    explicit MotorProtection(ProtectionConfig config = {});

    // Her yeni sicaklik olcumunde cagirilir.
    MotorState update(double temperatureCelsius);
    MotorState state() const;

private:
    ProtectionConfig config_;
    MotorState state_ = MotorState::Normal;
    bool alarmLatched_ = false;
};

const char* toString(MotorState state);
