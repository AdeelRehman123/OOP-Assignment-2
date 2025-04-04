#include <iostream>
#include <string>
using namespace std;

class User
{
protected:
	int userID;
	string name;
	bool paymentStatus;

public:
	User(int id = 0, string userName = "") : userID(id), name(userName), paymentStatus(false) {}
	virtual void makePayment() = 0;
	bool checkPayment() const { return paymentStatus; }
	int getUserID() const { return userID; }
	string getName() const { return name; }
};

class Student : public User
{
public:
	Student(int id = 0, string studentName = "") : User(id, studentName) {}
	void makePayment() override
	{
		paymentStatus = true;
		cout << name << " has successfully made the semester payment." << endl;
	}
};

class Teacher : public User
{
public:
	Teacher(int id = 0, string teacherName = "") : User(id, teacherName) {}
	void makePayment() override
	{
		paymentStatus = true;
		cout << name << " has successfully made the monthly payment." << endl;
	}
};

class Staff : public User
{
public:
	Staff(int id = 0, string staffName = "") : User(id, staffName) {}
	void makePayment() override
	{
		paymentStatus = true;
		cout << name << " has successfully made the monthly payment." << endl;
	}
};

class Route
{
private:
	int routeID;
	string startLocation;
	string endLocation;

public:
	Route(int id = 0, string start = "", string end = "") : routeID(id), startLocation(start), endLocation(end) {}
	void displayRoute() const
	{
		cout << "Route: " << startLocation << " to " << endLocation << endl;
	}
	int getRouteID() const { return routeID; }
};

class Bus
{
private:
	int busID;
	Route route;
	int seatsAvailable;
	User *usersOnBoard[30];
	int userCount;

public:
	Bus(int id = 0, Route r = Route()) : busID(id), route(r), seatsAvailable(30), userCount(0) {}
	void addUser(User *user)
	{
		if (userCount < 30)
		{
			usersOnBoard[userCount++] = user;
			seatsAvailable--;
			cout << user->getName() << " added to bus " << busID << endl;
		}
		else
		{
			cout << "No seats available on bus " << busID << endl;
		}
	}
	void displayBusDetails() const
	{
		cout << "Bus ID: " << busID << endl;
		route.displayRoute();
		cout << "Seats available: " << seatsAvailable << endl;
		cout << "Passengers on board: ";
		for (int i = 0; i < userCount; i++)
		{
			cout << usersOnBoard[i]->getName() << " ";
		}
		cout << endl;
	}
	int getBusID() const { return busID; }
};

class TransportationSystem
{
private:
	User *users[100];
	Bus buses[20];
	Route routes[20];
	int userCount, busCount, routeCount;

public:
	TransportationSystem() : userCount(0), busCount(0), routeCount(0) {}

	void registerUser()
	{
		int id, choice;
		string name;
		cout << "Register as: 1. Student 2. Teacher 3. Staff\nEnter choice: ";
		cin >> choice;
		cout << "Enter ID: ";
		cin >> id;
		cout << "Enter Name: ";
		cin.ignore();
		getline(cin, name);

		for (int i = 0; i < userCount; i++)
		{
			if (users[i]->getUserID() == id)
			{
				cout << "ID already taken! Please enter a different ID." << endl;
				return;
			}
		}

		switch (choice)
		{
		case 1:
			users[userCount++] = new Student(id, name);
			break;
		case 2:
			users[userCount++] = new Teacher(id, name);
			break;
		case 3:
			users[userCount++] = new Staff(id, name);
			break;
		default:
			cout << "Invalid choice!" << endl;
			return;
		}
		cout << name << " registered successfully!" << endl;
	}

	void makePayment()
	{
		int id;
		cout << "Enter User ID to make payment: ";
		cin >> id;
		for (int i = 0; i < userCount; i++)
		{
			if (users[i]->getUserID() == id)
			{
				users[i]->makePayment();
				return;
			}
		}
		cout << "User not found!" << endl;
	}

	void addRoute()
	{
		int id;
		string start, end;
		cout << "Enter Route ID: ";
		cin >> id;
		cout << "Enter Start Location: ";
		cin.ignore();
		getline(cin, start);
		cout << "Enter End Location: ";
		getline(cin, end);
		routes[routeCount++] = Route(id, start, end);
		cout << "Route added successfully!" << endl;
	}

	void addBus()
	{
		int busID, routeID;
		cout << "Enter Bus ID: ";
		cin >> busID;
		cout << "Enter Route ID for this bus: ";
		cin >> routeID;
		for (int i = 0; i < routeCount; i++)
		{
			if (routes[i].getRouteID() == routeID)
			{
				buses[busCount++] = Bus(busID, routes[i]);
				cout << "Bus added successfully!" << endl;
				return;
			}
		}
		cout << "Route not found!" << endl;
	}

	void assignUserToBus()
	{
		int userID, busID;
		cout << "Enter User ID: ";
		cin >> userID;
		cout << "Enter Bus ID: ";
		cin >> busID;
		for (int i = 0; i < userCount; i++)
		{
			if (users[i]->getUserID() == userID)
			{
				if (!users[i]->checkPayment())
				{
					cout << "Payment pending. User cannot board the bus." << endl;
					return;
				}
				for (int j = 0; j < busCount; j++)
				{
					if (buses[j].getBusID() == busID)
					{
						buses[j].addUser(users[i]);
						return;
					}
				}
				cout << "Bus not found!" << endl;
				return;
			}
		}
		cout << "User not found!" << endl;
	}

	void displayAllBuses()
	{
		for (int i = 0; i < busCount; i++)
		{
			buses[i].displayBusDetails();
		}
	}
};

int main()
{
	TransportationSystem ts;
	int choice;
	while (true)
	{
		cout << "\n1. Register User\n2. Make Payment\n3. Add Route\n4. Add Bus\n5. Assign User to Bus\n6. Display All Buses\n7. Exit\nEnter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			ts.registerUser();
			break;
		case 2:
			ts.makePayment();
			break;
		case 3:
			ts.addRoute();
			break;
		case 4:
			ts.addBus();
			break;
		case 5:
			ts.assignUserToBus();
			break;
		case 6:
			ts.displayAllBuses();
			break;
		case 7:
			return 0;
		default:
			cout << "Invalid choice!" << endl;
		}
	}
}
