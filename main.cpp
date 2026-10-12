#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

// --- 1. Car Class ---
class Car {
protected:
    std::string name;
    int topSpeed;
    int horsepower;
    int upgradeLevel;

public:
    Car(std::string n, int speed, int hp) : name(n), topSpeed(speed), horsepower(hp), upgradeLevel(0) {}

    virtual ~Car() = default;

    std::string getName() const { return name; }
    int getTopSpeed() const { return topSpeed; }
    int getHorsepower() const { return horsepower; }
    int getUpgradeLevel() const { return upgradeLevel; }
    
    void upgrade() {
        if (upgradeLevel < 10) {
            upgradeLevel++;
            topSpeed += 5;
            horsepower += 10;
            std::cout << name << " upgraded to level " << upgradeLevel << "!\n" 
                      << "==+==New Top Speed: " << topSpeed << " km/h | New HP: " << horsepower << "==+==\n";
        } else {
            std::cout << "Oops, sorry! "<< name << " is already at the maximum upgrade level!\n";
        }
    }

    virtual void displayCars() const {
        std::cout << "Car: " << name << " | Top Speed: " << getTopSpeed() << " km/h | HP: " << getHorsepower() << " | Level: " << upgradeLevel << "\n"; 
    }
};


// --- 2. Driver Class ---
class Driver {
private:
    std::string name;
    int experienceLevel;
    int wins;

public:
    Driver(std::string n, int exp) : name(n), experienceLevel(exp), wins(0) {}

    std::string getName() const { return name; }
    int getExperience() const { return experienceLevel; }
    int getWins() const { return wins; }
    void addWin() { wins++; }   

    void displayDriver() const {
        std::cout << "Driver: " << name << " | Experience: " << experienceLevel << " | Career Wins: " << wins << "\n";
    }
};

// --- 3. Race Track Class ---
class RaceTrack {
private:
    std::string name;
    int length; // in km
    int difficulty; // 1 (easiest) to 5 (hardest)

public:
    RaceTrack(std::string n, int len, int diff) : name(n), length(len), difficulty(diff) {}

    std::string getName() const { return name; }
    int getLength() const { return length; }
    int getDifficulty() const { return difficulty; }

    void displayTrack() const {
        std::cout << "Race Track: " << name << " | Length: " << length << " km | Difficulty: " << difficulty << "/5\n";
    }
};

// ===== 4. Motorsport kinds ---INHERITANCE--- =====
class Nascar : public Car {
public:
    Nascar(std::string n) : Car(n, 325, 670) {}
    void displayCars() const override {
        std::cout << "Nascar: ";
        Car::displayCars();
    }
};

class Formula1 : public Car {
public:
    Formula1(std::string n) : Car(n, 360, 800) {}
    void displayCars() const override { 
        std::cout << "Formula1: ";
        Car::displayCars();
    }
};

class GT3 : public Car {
public:
    GT3(std::string n) : Car(n, 320, 650) {}
    void displayCars() const override {
        std::cout << "[GT3] ";
        Car::displayCars();
    }
};

// ---!!!!!--- 5. Game Management System ---!!!!!---
class RacingGameManager {
private:
    int budget;
    std::vector<std::unique_ptr<Car>> garage;
    std::vector<Driver> drivers;
    std::vector<RaceTrack> tracks;

public:
    RacingGameManager() : budget(1000000) {
        garage.push_back(std::make_unique<Nascar>("Lightning McQueen Nascar"));
        garage.push_back(std::make_unique<Formula1>("Ferrari F1"));
        garage.push_back(std::make_unique<GT3>("Porsche 911 GT3"));
        garage.push_back(std::make_unique<GT3>("Lamborghini Huracan GT3"));
        garage.push_back(std::make_unique<Nascar>("Ford Mustang Nascar"));
        
        drivers.emplace_back("Lightning McQueen", 95);
        drivers.emplace_back("Charles Leclerc", 92);
        drivers.emplace_back("Max Verstappen", 96);
        drivers.emplace_back("Chris Buescher", 88);
        drivers.emplace_back("Maro Engel", 93);

        tracks.emplace_back("Daytona International Speedway", 4, 3);
        tracks.emplace_back("Monaco Grand Prix", 3, 5);
        tracks.emplace_back("Silverstone Circuit", 6, 4);
        tracks.emplace_back("Indianapolis Motor Speedway", 5, 4);
        tracks.emplace_back("spa-Francorchamps", 7, 5);
    }

    void showDashboard() const {
        std::cout << "\n========================================\n";
        std::cout << "      RACING MOTORSPORT MANAGEMENT      \n";
        std::cout << "========================================\n";
        std::cout << "Team Budget: $" << budget << "\n";
        std::cout << "Cars in Garage: " << garage.size() << "\n";
        std::cout << "Drivers on Roster: " << drivers.size() << "\n";
        std::cout << "Available Tracks: " << tracks.size() << "\n";
        std::cout << "========================================\n";
    }

    void viewGarage() const {
        std::cout << "\n--- GARAGE FLEET ---\n";
        for (size_t i = 0; i < garage.size(); ++i) {
            std::cout << "[" << i << "] ";
            garage[i]->displayCars();
        }
    }

    void viewDrivers() const {
        std::cout << "\n--- DRIVER ROSTER ---\n";
        for (size_t i = 0; i < drivers.size(); ++i) {
            std::cout << "[" << i << "] ";
            drivers[i].displayDriver();
        }
    }

    void viewTracks() const {
        std::cout << "\n==|======= RACING TRACKS =======|=\n";
        for (size_t i = 0; i < tracks.size(); ++i) {
            std::cout << "[" << i << "] ";
            tracks[i].displayTrack();
        }
    }

    void upgradeCarMenu() {
        viewGarage();
        std::cout << "Enter car index to upgrade ($50,000): ";
        size_t idx;
        std::cin >> idx;

        if (idx < garage.size()) {
            if (budget >= 50000) {
                budget -= 50000;
                garage[idx]->upgrade();
            } else {
                std::cout << "Not enough budget to upgrade!\n";
            }
        } else {
            std::cout << "Invalid selection.\n";
        }
    }

    void startRaceSimulation() {
        if (garage.empty() || drivers.empty() || tracks.empty()) {
            std::cout << "You need cars, drivers, and tracks configured to race!\n";
            return;
        }

        viewGarage();
        std::cout << "Select car index for race: ";
        size_t carIdx;
        std::cin >> carIdx;

        viewDrivers();
        std::cout << "Select driver index for race: ";
        size_t drvIdx;
        std::cin >> drvIdx;

        viewTracks();
        std::cout << "Select track index for race: ";
        size_t trkIdx;
        std::cin >> trkIdx;

        if (carIdx >= garage.size() || drvIdx >= drivers.size() || trkIdx >= tracks.size()) {
            std::cout << "Invalid choices. Race cancelled.\n";
            return;
        }

        std::cout << "\n--- RACE START: " << tracks[trkIdx].getName() << " ---\n";
        std::cout << drivers[drvIdx].getName() << " is stepping into the " << garage[carIdx]->getName() << "...\n";
        std::cout << "Lights out and away we go!\n\n";

        int carScore = garage[carIdx]->getTopSpeed() + garage[carIdx]->getHorsepower() / 4;
        int driverScore = drivers[drvIdx].getExperience() * 3;
        int totalPerformance = carScore + driverScore;

        int randomFactor = (rand() % 151) - 75;
        int finalScore = totalPerformance + randomFactor;

        std::cout << "Simulating laps...\n";
        int aiRandomFactor = (rand() % 101) - 50;
        int aiScore = 750 + aiRandomFactor + (tracks[trkIdx].getDifficulty() * 10);

        std::cout << "Your Performance Score: " << finalScore << " | AI Benchmark: " << aiScore << "\n";

        if (finalScore > aiScore) {
            int prize = 100000;
            std::cout << "\nVICTORY! " << drivers[drvIdx].getName() << " takes 1st place!\n";
            std::cout << "Prize Awarded: $" << prize << "\n";
            budget += prize;
            drivers[drvIdx].addWin();
        } else {
            std::cout << "\nDefeat! Tough race conditions, you finished outside the podium.\n";
        }
    }

    void run() {
        srand(static_cast<unsigned int>(time(0)));
        int choice;
        do {
            showDashboard();
            std::cout << "1. View Garage\n";
            std::cout << "2. View Drivers\n";
            std::cout << "3. View Tracks\n";
            std::cout << "4. Upgrade Car ($50,000)\n";
            std::cout << "5. Enter Race Event\n";
            std::cout << "6. Exit Game\n";
            std::cout << "Select option: ";
            std::cin >> choice;

            switch (choice) {
                case 1: viewGarage(); break;
                case 2: viewDrivers(); break;
                case 3: viewTracks(); break;
                case 4: upgradeCarMenu(); break;
                case 5: startRaceSimulation(); break;
                case 6: std::cout << "Saving and exiting... Goodbye!\n"; break;
                default: std::cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 6);
    }
};



int main() {
    RacingGameManager game;
    game.run();
    return 0;
}
