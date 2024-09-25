#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Species {
private:
    string name;
    int population;
    string endangered_status;

    static int total_species_count;
    static int total_population;

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
    Species(string name, int population)
        : name(name), population(population) {
        total_species_count++;
        total_population += population;
        update_status();
    }

    // Destructor
    ~Species() {
        total_species_count--;
        total_population -= population;
    }

    // Static member function
    static int get_total_species_count() {
        return total_species_count;
    }

    static int get_total_population() {
        return total_population;
    }

    // Member function to update population
    void update_population(int change) {
        total_population -= population; // Subtract old population
        population += change;
        total_population += population; // Add updated population
        if (population < 0) {
            population = 0;
        }
        update_status();
    }

    // Function to display species information
    void display() const {
        cout << name << ": Population " << population << ", Status: " << endangered_status << endl;
    }
};

// Initialize static members
int Species::total_species_count = 0;
int Species::total_population = 0;

int main() {
    // Creating species
    Species tiger("Tiger", 400);
    Species elephant("Elephant", 800);

    // Display initial species details
    tiger.display();
    elephant.display();

    // Accessing static member function
    cout << "Total species count: " << Species::get_total_species_count() << endl;
    cout << "Total population: " << Species::get_total_population() << endl;

    // Updating species population
    tiger.update_population(-100);
    elephant.update_population(50);

    // Display updated species details
    cout << "\nAfter population update:\n";
    tiger.display();
    elephant.display();

    // Accessing static member function again
    cout << "Total species count: " << Species::get_total_species_count() << endl;
    cout << "Total population: " << Species::get_total_population() << endl;

    return 0;
}