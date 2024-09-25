#include <iostream>
#include <string>
using namespace std;

class Species {
private:
    string name;
    int population;
    string endangered_status;

    static int total_species_count;  // Static variable to track the number of species
    static int total_population;     // Static variable to track the total population of all species

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
    // Constructor
    Species(string name, int population, string endangered_status)
        : name(name), population(population), endangered_status(endangered_status) {
        total_species_count++;
        total_population += population;
    }

    // Destructor
    ~Species() {
        total_species_count--;
        total_population -= population;
    }

    void update_population(int change) {
        total_population -= population; // Remove old population from total
        population += change;
        if (population < 0) population = 0;
        update_status();
        total_population += population; // Add updated population to total
    }

    string get_name() const { return name; }
    int get_population() const { return population; }
    string get_status() const { return endangered_status; }

    // Static function to get total species count
    static int get_total_species_count() {
        return total_species_count;
    }

    // Static function to get total population
    static int get_total_population() {
        return total_population;
    }

    friend ostream& operator<<(ostream& os, const Species& species) {
        os << species.name << ": Population " << species.population 
           << ", Status: " << species.endangered_status;
        return os;
    }
};

// Initialize static members
int Species::total_species_count = 0;
int Species::total_population = 0;

int main() {
    // Create Species objects
    Species* tiger = new Species("Tiger", 400, "Endangered");
    Species* elephant = new Species("Elephant", 800, "Vulnerable");
    Species* panda = new Species("Panda", 100, "Endangered");

    // Print initial species data and static variables
    cout << "Initial Species data:" << endl;
    cout << *tiger << endl;
    cout << *elephant << endl;
    cout << *panda << endl;

    cout << "\nTotal species count: " << Species::get_total_species_count() << endl;
    cout << "Total population: " << Species::get_total_population() << endl;

    // Update population of species
    tiger->update_population(-50);  // Decrease tiger population
    elephant->update_population(200);  // Increase elephant population
    panda->update_population(-80);  // Decrease panda population

    // Print updated species data and static variables
    cout << "\nUpdated Species data:" << endl;
    cout << *tiger << endl;
    cout << *elephant << endl;
    cout << *panda << endl;

    cout << "\nTotal species count: " << Species::get_total_species_count() << endl;
    cout << "Total population: " << Species::get_total_population() << endl;

    // Deallocate memory
    delete tiger;
    delete elephant;
    delete panda;

    cout << "\nAfter deleting species:" << endl;
    cout << "Total species count: " << Species::get_total_species_count() << endl;
    cout << "Total population: " << Species::get_total_population() << endl;

    return 0;
}