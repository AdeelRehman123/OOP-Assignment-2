#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    int id, speed, capacity;
    float energyEff;
    static int totalActiveDeliveries;

public:
    Vehicle(int id, int speed, int capacity, float energyEff) {
        this->id = id;
        this->speed = speed;
        this->capacity = capacity;
        this->energyEff = energyEff;
        totalActiveDeliveries++;
    }

    virtual void move() {
        cout << "Vehicle " << id << " is moving in a general manner." << endl;
    }

    virtual void calcOptimalDeliveryRoute() {
        cout << "Calculating optimal route for Vehicle " << id << endl;
    }

    virtual void calcEstimatedDeliveryTime() {
        cout << "Calculating estimated delivery time for Vehicle " << id << endl;
    }

    static int getTotalActiveDeliveries() {
        return totalActiveDeliveries;
    }

    static Vehicle* resolveConflict(Vehicle* v1, Vehicle* v2) {
        return (v1->speed > v2->speed) ? v1 : v2;
    }

    int getId() const {
        return id;
    }
};

// Initialize static member
int Vehicle::totalActiveDeliveries = 0;

class RamzanDrone : public Vehicle {
public:
    RamzanDrone(int id) : Vehicle(id, 150, 5, 9.5f) {}

    void move() override {
        cout << id << " RamzanDrone flying for high-speed delivery." << endl;
    }
};

class RamzanTimeShip : public Vehicle {
public:
    RamzanTimeShip(int id) : Vehicle(id, 100, 10, 8.0f) {}

    void move() override {
        cout << id << " RamzanTimeShip ensuring historical consistency before delivery." << endl;
    }
};

class RamzanHyperPod : public Vehicle {
public:
    RamzanHyperPod(int id) : Vehicle(id, 200, 20, 7.5f) {}

    void move() override {
        cout << id << " RamzanHyperPod navigating underground tunnels for efficient delivery." << endl;
    }
};

class Command {
private:
    string deliveryType;
    int packageID;
    string urgencyLevel;

public:
    Command(string deliveryType, int packageID, string urgencyLevel)
        : deliveryType(deliveryType), packageID(packageID), urgencyLevel(urgencyLevel) {}

    Command(string deliveryType, int packageID)
        : deliveryType(deliveryType), packageID(packageID), urgencyLevel("normal") {}

    void execute(Vehicle* vehicle) {
        cout << "Executing command for Vehicle " << vehicle->getId()
             << " Package: " << packageID << " Urgency: " << urgencyLevel << endl;
        vehicle->calcOptimalDeliveryRoute();
        vehicle->calcEstimatedDeliveryTime();
        vehicle->move();
    }
};

int main() {
    Vehicle* v1 = new RamzanDrone(1);
    Vehicle* v2 = new RamzanHyperPod(2);
    Vehicle* v3 = new RamzanTimeShip(3);

    Command c1("Deliver", 101, "urgent");
    c1.execute(v1);

    Command c2("Deliver", 102);
    c2.execute(v2);

    Command c3("Deliver", 103, "historical");
    c3.execute(v3);

    cout << "Total Active Deliveries: " << Vehicle::getTotalActiveDeliveries() << endl;

    // Clean up
    delete v1;
    delete v2;
    delete v3;

    return 0;
}
