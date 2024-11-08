#include <iostream>  
#include <string>  
#include <vector>  
#include <memory>  
using namespace std;  

// Abstract Base Class  
class WildlifeEntity {  
protected:  
    string name;  
    int conservationStatus;  

public:  
    // Pure Virtual Function (makes the class Abstract)  
    virtual void generateConservationReport() = 0;  

    // Virtual Destructor  
    virtual ~WildlifeEntity() {  
        cout << "WildlifeEntity Destructor" << endl;  
    }  

    // Virtual Function for common behavior  
    virtual void displayBasicInfo() {  
        cout << "Name: " << name << endl;  
        cout << "Conservation Status: " << getConservationStatusDescription() << endl;  
    }  

    // Pure Virtual Function for conservation status  
    virtual string getConservationStatusDescription() = 0;  

    // Setter methods  
    void setName(const string& entityName) {  
        name = entityName;  
    }  

    void setConservationStatus(int status) {  
        conservationStatus = status;  
    }  
};  

// Concrete Derived Class: Endangered Species  
class EndangeredSpecies : public WildlifeEntity {  
private:  
    int populationCount;  
    string habitat;  

public:  
    EndangeredSpecies(const string& speciesName, int status, int population, const string& speciesHabitat)  
        : populationCount(population), habitat(speciesHabitat) {  
        name = speciesName;  
        conservationStatus = status;  
    }  

    // Implementing Pure Virtual Function for Conservation Report  
    void generateConservationReport() override {  
        cout << "\n--- Conservation Report ---" << endl;  
        displayBasicInfo();  
        cout << "Population Count: " << populationCount << endl;  
        cout << "Primary Habitat: " << habitat << endl;  
        cout << "Conservation Strategies:" << endl;  
        recommendConservationStrategies();  
    }  

    // Implementing Pure Virtual Function for Status Description  
    string getConservationStatusDescription() override {  
        switch(conservationStatus) {  
            case 1: return "Critical";  
            case 2: return "Endangered";  
            case 3: return "Vulnerable";  
            default: return "Unknown";  
        }  
    }  

    // Additional Virtual Method  
    virtual void recommendConservationStrategies() {  
        cout << "1. Habitat Protection" << endl;  
        cout << "2. Breeding Programs" << endl;  
        cout << "3. Anti-Poaching Measures" << endl;  
    }  
};  

// Another Concrete Derived Class: Ecosystem  
class Ecosystem : public WildlifeEntity {  
private:  
    string type;  
    vector<string> keySpecies;  

public:  
    Ecosystem(const string& ecosystemName, const string& ecosystemType)  
        : type(ecosystemType) {  
        name = ecosystemName;  
        conservationStatus = 2; // Moderate Risk  
    }  

    // Implementing Pure Virtual Function for Conservation Report  
    void generateConservationReport() override {  
        cout << "\n--- Ecosystem Conservation Report ---" << endl;  
        displayBasicInfo();  
        cout << "Ecosystem Type: " << type << endl;  
        cout << "Key Species:" << endl;  
        for (const auto& species : keySpecies) {  
            cout << "- " << species << endl;  
        }  
    }  

    // Implementing Pure Virtual Function for Status Description  
    string getConservationStatusDescription() override {  
        switch(conservationStatus) {  
            case 1: return "Critically Damaged";  
            case 2: return "Moderately Threatened";  
            case 3: return "Stable";  
            default: return "Unknown";  
        }  
    }  

    // Method to add key species  
    void addKeySpecies(const string& species) {  
        keySpecies.push_back(species);  
    }  
};  

// Demonstration Function  
void demonstrateAbstractClassAndVirtualFunctions() { 
    vector<unique_ptr<WildlifeEntity>> conservationEntities;  

    // Create Endangered Species  
    auto tigerSpecies = make_unique<EndangeredSpecies>("Bengal Tiger", 2, 2967, "Tropical Forests");  
    
    // Create Ecosystem  
    auto forestEcosystem = make_unique<Ecosystem>("Amazon Rainforest", "Tropical Rainforest");  
    forestEcosystem->addKeySpecies("Jaguar");  
    forestEcosystem->addKeySpecies("Harpy Eagle");  

    // Add to vector of wildlife entities  
    conservationEntities.push_back(move(tigerSpecies));  
    conservationEntities.push_back(move(forestEcosystem));  

    // Polymorphic method calls  
    cout << "\nGenerating Conservation Reports:" << endl;  
    for (const auto& entity : conservationEntities) {  
        entity->generateConservationReport();  
    }  
}  

int main() {  
    // Demonstrate Abstract Class and Virtual Functions  
    demonstrateAbstractClassAndVirtualFunctions();  

    return 0;  
}