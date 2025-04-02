#include <iostream>
#include <string>

// Light class
class Light {
private:
    std::string name;
    bool isOn;

public:
    Light(const std::string& lightName) : name(lightName), isOn(false) {}

    void on() {
        isOn = true;
        std::cout << name << " light turned on" << std::endl;
    }

    void off() {
        isOn = false;
        std::cout << name << " light turned off" << std::endl;
    }
};

// Thermostat class
class Thermostat {
private:
    int temperature;
    std::string mode;

public:
    Thermostat() : temperature(20), mode("normal") {}

    void setTemperature(int temp) {
        temperature = temp;
        std::cout << "Thermostat set to " << temp << "°C" << std::endl;
    }

    void setEcoMode() {
        mode = "eco";
        temperature = 18;
        std::cout << "Thermostat set to eco mode (18°C)" << std::endl;
    }

    void setComfortMode() {
        mode = "normal";
        temperature = 22;
        std::cout << "Thermostat set to comfort mode (22°C)" << std::endl;
    }
};

// SecurityCamera class
class SecurityCamera {
private:
    std::string name;
    bool isActive;

public:
    SecurityCamera(const std::string& cameraName) : name(cameraName), isActive(false) {}

    void activate() {
        isActive = true;
        std::cout << name << " camera activated" << std::endl;
    }

    void deactivate() {
        isActive = false;
        std::cout << name << " camera deactivated" << std::endl;
    }
};

// SmartHomeFacade class
class SmartHomeFacade {
private:
    Light livingRoomLight;
    Light kitchenLight;
    Thermostat thermostat;
    SecurityCamera frontCamera;
    SecurityCamera backCamera;

public:
    SmartHomeFacade() 
        : livingRoomLight("Living room"), 
          kitchenLight("Kitchen"),
          frontCamera("Front door"),
          backCamera("Back yard") {}

    void leavingHome() {
        std::cout << "\nActivating 'Leaving Home' scenario:" << std::endl;
        livingRoomLight.off();
        kitchenLight.off();
        thermostat.setEcoMode();
        frontCamera.activate();
        backCamera.activate();
    }

    void arrivingHome() {
        std::cout << "\nActivating 'Arriving Home' scenario:" << std::endl;
        livingRoomLight.on();
        kitchenLight.on();
        thermostat.setComfortMode();
        frontCamera.deactivate();
        backCamera.deactivate();
    }
};

// Main function
int main() {
    SmartHomeFacade smartHome;

    // Simulate leaving home scenario
    smartHome.leavingHome();

    // Simulate arriving home scenario
    smartHome.arrivingHome();

    return 0;
}
