#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <limits>
using namespace std;

// Base class for all wildlife entities
class WildlifeEntity {
protected:
    string name;
    int conservationStatus;

public:
    virtual ~WildlifeEntity() = default;
    
    virtual void generateConservationReport() const = 0;
    
    virtual void displayBasicInfo() const {
        cout << "Name: " << name << endl;
        cout << "Conservation Status: " << getConservationStatusDescription() << endl;
    }
    
    virtual string getConservationStatusDescription() const = 0;
    
    void setName(const string& entityName) {
        name = entityName;
    }
    
    void setConservationStatus(int status) {
        conservationStatus = status;
    }
    
    string getName() const { return name; }
    int getStatus() const { return conservationStatus; }
};

// Class to manage individual animals
class Animal {
private:
    string species;
    string habitat;
    int age;
    string healthStatus;

public:
    Animal(const string& speciesName, const string& animalHabitat, int animalAge)
        : species(speciesName), habitat(animalHabitat), age(animalAge), healthStatus("Healthy") {}
    
    void displayAnimalDetails() const {
        cout << "Species: " << species << endl;
        cout << "Habitat: " << habitat << endl;
        cout << "Age: " << age << endl;
        cout << "Health Status: " << healthStatus << endl;
    }
    
    void updateHealthStatus(const string& status) {
        healthStatus = status;
    }
    
    string getSpecies() const { return species; }
    string getHabitat() const { return habitat; }
};

// Class for endangered species management
class EndangeredSpecies : public WildlifeEntity {
private:
    int populationCount;
    string habitat;
    vector<Animal> individuals;

public:
    EndangeredSpecies(const string& speciesName, int status, int population, const string& speciesHabitat)
        : populationCount(population), habitat(speciesHabitat) {
        name = speciesName;
        conservationStatus = status;
    }

    void generateConservationReport() const override {
        cout << "\n=== Endangered Species Conservation Report ===" << endl;
        displayBasicInfo();
        cout << "Population Count: " << populationCount << endl;
        cout << "Primary Habitat: " << habitat << endl;
        cout << "Conservation Strategies:" << endl;
        recommendConservationStrategies();
    }

    string getConservationStatusDescription() const override {
        switch(conservationStatus) {
            case 1: return "Critical";
            case 2: return "Endangered";
            case 3: return "Vulnerable";
            default: return "Unknown";
        }
    }

    void recommendConservationStrategies() const {
        cout << "1. Habitat Protection" << endl;
        cout << "2. Breeding Programs" << endl;
        cout << "3. Anti-Poaching Measures" << endl;
    }
    
    void addIndividual(const Animal& animal) {
        individuals.push_back(animal);
        populationCount = individuals.size();
    }
};

// Class for ecosystem management
class Ecosystem : public WildlifeEntity {
private:
    string type;
    vector<string> keySpecies;
    map<string, string> habitatHealth;

public:
    Ecosystem(const string& ecosystemName, const string& ecosystemType)
        : type(ecosystemType) {
        name = ecosystemName;
        conservationStatus = 2;
    }

    void generateConservationReport() const override {
        cout << "\n=== Ecosystem Conservation Report ===" << endl;
        displayBasicInfo();
        cout << "Ecosystem Type: " << type << endl;
        displayKeySpecies();
        displayHabitatHealth();
    }

    string getConservationStatusDescription() const override {
        switch(conservationStatus) {
            case 1: return "Critically Damaged";
            case 2: return "Moderately Threatened";
            case 3: return "Stable";
            default: return "Unknown";
        }
    }

    void addKeySpecies(const string& species) {
        keySpecies.push_back(species);
    }
    
    void updateHabitatHealth(const string& area, const string& status) {
        habitatHealth[area] = status;
    }
    
private:
    void displayKeySpecies() const {
        cout << "Key Species:" << endl;
        for (const auto& species : keySpecies) {
            cout << "- " << species << endl;
        }
    }
    
    void displayHabitatHealth() const {
        cout << "Habitat Health Status:" << endl;
        for (const auto& [area, status] : habitatHealth) {
            cout << "- " << area << ": " << status << endl;
        }
    }
};

// Utility functions for input validation
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getValidIntInput(const string& prompt, int min, int max) {
    int input;
    while (true) {
        cout << prompt;
        if (cin >> input && input >= min && input <= max) {
            clearInputBuffer();
            return input;
        }
        cout << "Invalid input. Please enter a number between " << min << " and " << max << endl;
        clearInputBuffer();
    }
}

string getValidStringInput(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (!input.empty()) {
            return input;
        }
        cout << "Input cannot be empty. Please try again." << endl;
    }
}

class ConservationSystem {
private:
    vector<unique_ptr<WildlifeEntity>> entities;

public:
    void addEndangeredSpecies() {
        cout << "\n=== Adding New Endangered Species ===" << endl;
        
        string speciesName = getValidStringInput("Enter species name: ");
        
        cout << "\nConservation Status:" << endl;
        cout << "1. Critical" << endl;
        cout << "2. Endangered" << endl;
        cout << "3. Vulnerable" << endl;
        int status = getValidIntInput("Enter status (1-3): ", 1, 3);
        
        int population = getValidIntInput("Enter current population count: ", 0, 1000000);
        
        string habitat = getValidStringInput("Enter primary habitat: ");

        auto species = make_unique<EndangeredSpecies>(speciesName, status, population, habitat);

        // Add individual animals
        char addAnimal;
        cout << "Would you like to add individual animals? (y/n): ";
        cin >> addAnimal;
        clearInputBuffer();

        while (tolower(addAnimal) == 'y') {
            string animalHabitat = getValidStringInput("Enter specific habitat for this individual: ");
            int age = getValidIntInput("Enter age: ", 0, 100);
            
            Animal individual(speciesName, animalHabitat, age);
            species->addIndividual(individual);

            cout << "Add another animal? (y/n): ";
            cin >> addAnimal;
            clearInputBuffer();
        }

        entities.push_back(move(species));
        cout << "Endangered species added successfully!" << endl;
    }

    void addEcosystem() {
        cout << "\n=== Adding New Ecosystem ===" << endl;
        
        string ecosystemName = getValidStringInput("Enter ecosystem name: ");
        string ecosystemType = getValidStringInput("Enter ecosystem type: ");

        auto ecosystem = make_unique<Ecosystem>(ecosystemName, ecosystemType);

        // Add key species
        char addSpecies;
        cout << "Would you like to add key species? (y/n): ";
        cin >> addSpecies;
        clearInputBuffer();

        while (tolower(addSpecies) == 'y') {
            string species = getValidStringInput("Enter key species name: ");
            ecosystem->addKeySpecies(species);

            cout << "Add another species? (y/n): ";
            cin >> addSpecies;
            clearInputBuffer();
        }

        // Add habitat health information
        char addHealth;
        cout << "Would you like to add habitat health information? (y/n): ";
        cin >> addHealth;
        clearInputBuffer();

        while (tolower(addHealth) == 'y') {
            string area = getValidStringInput("Enter area name: ");
            string status = getValidStringInput("Enter health status: ");
            
            ecosystem->updateHabitatHealth(area, status);

            cout << "Add another area? (y/n): ";
            cin >> addHealth;
            clearInputBuffer();
        }

        entities.push_back(move(ecosystem));
        cout << "Ecosystem added successfully!" << endl;
    }

    void generateAllReports() const {
        if (entities.empty()) {
            cout << "No conservation entities to report on." << endl;
            return;
        }

        cout << "\n=== Generating All Conservation Reports ===" << endl;
        for (const auto& entity : entities) {
            entity->generateConservationReport();
            cout << endl;
        }
    }
};

int main() {
    ConservationSystem conservationSystem;

    bool running = true;
    while (running) {
        cout << "\n=== Wildlife Management System ===" << endl;
        cout << "1. Add Endangered Species" << endl;
        cout << "2. Add Ecosystem" << endl;
        cout << "3. Generate Conservation Reports" << endl;
        cout << "4. Exit" << endl;
        
        int choice = getValidIntInput("Enter your choice: ", 1, 4);
        
        switch (choice) {
            case 1:
                conservationSystem.addEndangeredSpecies();
                break;
            case 2:
                conservationSystem.addEcosystem();
                break;
            case 3:
                conservationSystem.generateAllReports();
                break;
            case 4:
                running = false;
                cout << "Exiting Wildlife Management System." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
