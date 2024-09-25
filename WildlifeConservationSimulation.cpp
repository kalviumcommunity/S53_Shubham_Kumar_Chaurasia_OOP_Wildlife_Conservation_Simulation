#include <iostream>
#include <string>
using namespace std;

class Species {
private:
    string name;
    int population;
    string endangered_status;

    void update_status() {
        if (population == 0) {
            endangered_status = "Extinct";
        } else if (population < 50) {
            endangered_status = "Critically Endangered";
        } else if (population < 200) {
            endangered_status = "Endangered";
        } else if (population < 1000) {
            endangered_status = "Vulnerable";
        } else {
            endangered_status = "Least Concern";
        }
    }

public:
    Species(string name, int population, string endangered_status)
        : name(name), population(population), endangered_status(endangered_status) {}

    void update_population(int change) {
        population += change;
        if (population < 0) population = 0;
        update_status();
    }

    string get_name() const { return name; }
    int get_population() const { return population; }
    string get_status() const { return endangered_status; }

    friend ostream& operator<<(ostream& os, const Species& species) {
        os << species.name << ": Population " << species.population 
           << ", Status: " << species.endangered_status;
        return os;
    }
};

int main() {
    // Dynamically allocate memory for Species objects
    Species* tiger = new Species("Tiger", 400, "Endangered");
    Species* elephant = new Species("Elephant", 800, "Vulnerable");
    Species* panda = new Species("Panda", 100, "Endangered");

    // Print initial species data
    cout << "Initial Species data:" << endl;
    cout << *tiger << endl;
    cout << *elephant << endl;
    cout << *panda << endl;

    // Update population of species
    tiger->update_population(-50);  // Decrease tiger population
    elephant->update_population(200);  // Increase elephant population
    panda->update_population(-80);  // Decrease panda population

    // Print updated species data
    cout << "\nUpdated Species data:" << endl;
    cout << *tiger << endl;
    cout << *elephant << endl;
    cout << *panda << endl;

    // Deallocate memory using delete
    delete tiger;
    delete elephant;
    delete panda;

    return 0;
}