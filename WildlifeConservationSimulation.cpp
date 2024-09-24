#include <iostream>
#include <string>
#include <vector>
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
    // Create an array of Species objects
    Species speciesArray[3] = {
        Species("Tiger", 400, "Endangered"),
        Species("Elephant", 800, "Vulnerable"),
        Species("Panda", 100, "Endangered")
    };

    // Print initial species data
    cout << "Initial Species data:" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << speciesArray[i] << endl;
    }

    // Update population of the species
    cout << "\nUpdating populations...\n" << endl;
    speciesArray[0].update_population(-50);  // Decrease tiger population
    speciesArray[1].update_population(200);  // Increase elephant population
    speciesArray[2].update_population(-80);  // Decrease panda population

    // Print updated species data
    cout << "Updated Species data:" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << speciesArray[i] << endl;
    }

    return 0;
}