#include <iostream>  
#include <string>  
#include <vector>  
using namespace std;  

class Species {  
private:  
    string name;  
    int population;  
    string endangered_status;  

    // Static members to keep track of total counts  
    static int total_species_count;  
    static int total_population;  

    // Private method to automatically update status based on population  
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
    Species(const string& name, int population) : name(name), population(population) {  
        total_species_count++;  
        total_population += population;  
        update_status();  
    }  

    // Destructor  
    ~Species() {  
        total_species_count--;  
        total_population -= population;  
    }  

    // Getters for the private attributes  
    string get_name() const { return name; }  
    int get_population() const { return population; }  
    string get_endangered_status() const { return endangered_status; }  

    // Setter for population  
    void set_population(int new_population) {  
        if (new_population >= 0) {  
            total_population -= population;  
            population = new_population;  
            total_population += population;  
            update_status();  
        }  
    }  

    // Function to display the species information  
    void display() const {  
        cout << name << ": Population " << population << ", Status: " << endangered_status << endl;  
    }  

    static int get_total_species_count() {  
        return total_species_count;  
    }  

    static int get_total_population() {  
        return total_population;  
    }  
};  

// Initialize static members  
int Species::total_species_count = 0;  
int Species::total_population = 0;  

int main() {  
    // Input variables for user  
    string name;  
    int population;  

    // Getting user input for Species  
    cout << "Enter the species name: ";  
    cin >> name;  // Read species name  
    cout << "Enter the initial population: ";  
    cin >> population;  // Read species population  

    // Creating species object based on user input  
    Species user_species(name, population);  

    // Display initial species details  
    user_species.display();  

    // Display total statistics  
    cout << "Total species count: " << Species::get_total_species_count() << endl;  
    cout << "Total population: " << Species::get_total_population() << endl;  

    // Update population via user input  
    int change;  
    cout << "Enter the change in population (positive or negative): ";  
    cin >> change;  

    user_species.set_population(user_species.get_population() + change); // Update population  

    // Display updated species details  
    cout << "\nAfter population update:\n";  
    user_species.display();  

    // Display total statistics again  
    cout << "Total species count: " << Species::get_total_species_count() << endl;  
    cout << "Total population: " << Species::get_total_population() << endl;  

    return 0;  
}