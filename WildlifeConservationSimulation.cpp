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
    Species(const string& name, int population)  
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

    // Static member functions  
    static int get_total_species_count() {  
        return total_species_count;  
    }  

    static int get_total_population() {  
        return total_population;  
    }  

    // Accessor methods  
    string get_name() const {  
        return name;  
    }  

    int get_population() const {  
        return population;  
    }  

    string get_endangered_status() const {  
        return endangered_status;  
    }  

    // Mutator method to update population  
    void set_population(int new_population) {  
        if (new_population >= 0) {  
            total_population -= population; // Subtract old population  
            population = new_population; // Update to new population  
            total_population += population; // Add updated population  
            update_status(); // Update status accordingly  
        }  
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

    // Accessing static member functions  
    cout << "Total species count: " << Species::get_total_species_count() << endl;  
    cout << "Total population: " << Species::get_total_population() << endl;  

    // Updating species population  
    tiger.set_population(300);  
    elephant.set_population(850);  

    // Display updated species details  
    cout << "\nAfter population update:\n";  
    tiger.display();  
    elephant.display();  

    // Accessing static member functions again  
    cout << "Total species count: " << Species::get_total_species_count() << endl;  
    cout << "Total population: " << Species::get_total_population() << endl;  

    return 0;  
}