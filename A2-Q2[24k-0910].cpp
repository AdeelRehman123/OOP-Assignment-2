#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Ghost {
protected:
	string nameOfWorker;
	int scareLevel;
public:
	Ghost(string nameOfWorker, int scareLevel) {
		this->nameOfWorker = nameOfWorker;
		this->scareLevel = scareLevel;
	}

	Ghost(string name1, string name2, int level1, int level2) {
		this->nameOfWorker = name1 + " " + name2;
		this->scareLevel = level1 + level2;
	}

	virtual void haunting() {
		cout << "Haunting" << endl;
	}

	virtual void display() {
		cout << "Name: " << nameOfWorker << " Scare Level: " << scareLevel << endl;
	}

	void increaseLevel(Ghost* ghost) {
		this->nameOfWorker += ghost->nameOfWorker;
		this->scareLevel += ghost->scareLevel;
	}

	string getNameOfWorker() const {
		return nameOfWorker;
	}

	int getScareLevel() const {
		return scareLevel;
	}

	virtual ~Ghost() {}
};

class Poltergeists : public Ghost {
public:
	Poltergeists(string nameOfWorker, int scareLevel) : Ghost(nameOfWorker, scareLevel) {}

	void haunting() override {
		cout << "Moving Objects" << endl;
	}
};

class Banshees : public Ghost {
public:
	Banshees(string nameOfWorker, int scareLevel) : Ghost(nameOfWorker, scareLevel) {}

	void haunting() override {
		cout << "Screaming Loudly" << endl;
	}
};

class ShadowGhosts : public Ghost {
public:
	ShadowGhosts(string nameOfWorker, int scareLevel) : Ghost(nameOfWorker, scareLevel) {}

	void haunting() override {
		cout << "Whispering Creepily" << endl;
	}
};

class HybridGhost : public Ghost {
	Ghost* g1;
	Ghost* g2;
public:
	HybridGhost(Ghost* g1, Ghost* g2) : Ghost(g1->getNameOfWorker(), g2->getNameOfWorker(), g1->getScareLevel(), g2->getScareLevel()) {
		this->g1 = g1;
		this->g2 = g2;
	}

	void haunting() override {
		g1->haunting();
		g2->haunting();
	}
};

class HauntedHouse {
	string name;
	vector<Ghost*> ghosts;
public:
	HauntedHouse(string name) {
		this->name = name;
	}

	void addGhost(Ghost* g) {
		ghosts.push_back(g);
	}

	string getName() const {
		return name;
	}

	const vector<Ghost*>& getGhosts() const {
		return ghosts;
	}
};

class Visitor {
	string name;
	int bravery;
public:
	Visitor(string name, int bravery) {
		this->name = name;
		this->bravery = bravery;
	}

	static void visit(vector<Visitor>& visitors, HauntedHouse& house) {
		for (int i = 0; i < visitors.size(); i++) {
			for (int j = 0; j < house.getGhosts().size(); j++) {
				Ghost* ghost = house.getGhosts()[j];
				if (visitors[i].bravery > ghost->getScareLevel()) {
					cout << visitors[i].name << " laughing to " << ghost->getNameOfWorker() << endl;
				} else if (visitors[i].bravery < ghost->getScareLevel()) {
					cout << visitors[i].name << " screaming running away from " << ghost->getNameOfWorker() << endl;
				} else {
					cout << visitors[i].name << " Shaky voice to " << ghost->getNameOfWorker() << endl;
				}
			}
		}
	}
};

int main() {
	vector<Visitor> visitors1 = {
		Visitor("Farhan", 4),
		Visitor("Zeeshan", 8),
		Visitor("Rafay", 10)
	};

	vector<Visitor> visitors2 = {
		Visitor("bisma", 5),
		Visitor("Zeeshan", 8),
		Visitor("Rafay", 10)
	};

	vector<Visitor> visitors3 = {
		Visitor("Farhan", 4),
		Visitor("Danish", 6),
		Visitor("bisma", 5)
	};

	HauntedHouse house1("BOLLYWOOD");
	HauntedHouse house2("VINEWOOD");
	HauntedHouse house3("HOLLYWOOD");

	Ghost* g1 = new ShadowGhosts("Vampire", 2);
	Ghost* g2 = new Banshees("Darcula", 7);
	Ghost* g3 = new Poltergeists("Granny", 9);
	Ghost* g4 = new HybridGhost(g1, g2);

	house1.addGhost(g1); house1.addGhost(g2); house1.addGhost(g3); house1.addGhost(g4);
	house2.addGhost(g1); house2.addGhost(g2); house2.addGhost(g3); house2.addGhost(g4);
	house3.addGhost(g1); house3.addGhost(g2); house3.addGhost(g3); house3.addGhost(g4);

	cout << "---" << house1.getName() << "---" << endl;
	Visitor::visit(visitors1, house1);

	cout << "---" << house2.getName() << "---" << endl;
	Visitor::visit(visitors2, house2);

	cout << "---" << house3.getName() << "---" << endl;
	Visitor::visit(visitors3, house3);

	// Clean up
	delete g1;
	delete g2;
	delete g3;
	delete g4;

	return 0;
}
