#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
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
        if (population < 0) {
            population = 0;
        }
        update_status();
    }

    string get_name() const { return name; }
    int get_population() const { return population; }
    string get_status() const { return endangered_status; }

    friend ostream& operator<<(ostream& os, const Species& species) {
        os << species.name << ": Population " << species.population << ", Status: " << species.endangered_status;
        return os;
    }
};

class Habitat {
private:
    string name;
    int capacity;
    int quality;
    vector<Species*> species;

public:
    Habitat(string name, int capacity, int quality)
        : name(name), capacity(capacity), quality(quality) {}

    bool add_species(Species* new_species) {
        if (species.size() < static_cast<size_t>(capacity)) {
            species.push_back(new_species);
            return true;
        }
        return false;
    }

    bool remove_species(Species* target_species) {
        auto it = find(species.begin(), species.end(), target_species);
        if (it != species.end()) {
            species.erase(it);
            return true;
        }
        return false;
    }

    void update_quality(int change) {
        quality += change;
        if (quality < 0) {
            quality = 0;
        } else if (quality > 100) {
            quality = 100;
        }
    }

    void simulate_events() {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0, 1.0);
        uniform_int_distribution<> population_change(-10, 20);

        for (auto& s : species) {
            if (dis(gen) < 0.5) {  // 50% chance of population change
                s->update_population(population_change(gen));
            }
        }
    }

    friend ostream& operator<<(ostream& os, const Habitat& habitat) {
        os << habitat.name << ": Quality " << habitat.quality << "%, Species: " << habitat.species.size();
        return os;
    }

    ~Habitat() {
        // Clean up dynamically allocated Species objects
        for (Species* s : species) {
            delete s;
        }
    }
};

int main() {
    // Dynamically create Species objects using 'new'
    Species* tiger = new Species("Tiger", 400, "Endangered");
    Species* elephant = new Species("Elephant", 800, "Vulnerable");

    // Create Habitat object
    Habitat* forest = new Habitat("Tropical Forest", 5, 80);

    // Add species to habitat
    forest->add_species(tiger);
    forest->add_species(elephant);

    cout << "Initial state:" << endl;
    cout << *forest << endl;
    cout << *tiger << endl;
    cout << *elephant << endl;

    // Simulate events
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> quality_change(-5, 5);

    for (int i = 0; i < 5; ++i) {
        forest->simulate_events();
        forest->update_quality(quality_change(gen));
    }

    cout << "\nAfter simulation:" << endl;
    cout << *forest << endl;
    cout << *tiger << endl;
    cout << *elephant << endl;

    // Clean up dynamically allocated memory
    delete forest;  // This will also delete species within habitat due to Habitat destructor

    return 0;
}