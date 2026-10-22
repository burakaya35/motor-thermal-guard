#include "motor_protection.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    std::vector<double> temperatures;

    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            try {
                const std::string input(argv[i]);
                std::size_t processed = 0;
                const double value = std::stod(input, &processed);
                if (processed != input.size()) {
                    throw std::invalid_argument("Unexpected characters");
                }
                temperatures.push_back(value);
            } catch (const std::exception&) {
                std::cerr << "Invalid temperature: " << argv[i] << "\n";
                std::cerr << "Usage: motor_monitor [temperature1 temperature2 ...]\n";
                return 2;
            }
        }
    } else {
        temperatures = {25.0, 74.9, 75.0, 73.0, 70.0, 80.0, 180.0, 72.0, 69.0};
    }

    MotorProtection monitor;
    std::cout << "Motor thermal protection simulation\n";
    std::cout << "Trip: " << kTripTemperatureC << " C, reset: " << kResetTemperatureC << " C\n";

    for (const double temperature : temperatures) {
        const MotorState current = monitor.update(temperature);
        std::cout << "Temperature: " << temperature
                  << " C -> " << toString(current) << "\n";
    }

    // Bu ogrenme projesi gercek bir motoru veya sensoru surmez.
    return 0;
}
