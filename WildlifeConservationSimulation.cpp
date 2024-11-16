#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// Base class defining core animal protection contract  
class ProtectedAnimal {  
public:  
    virtual ~ProtectedAnimal() = default;

    // Core methods that must be consistently implemented  
    virtual string getSpeciesName() const = 0;  
    virtual int getPopulationCount() const = 0;  
    virtual bool isEndangered() const = 0;  

    // Default implementation for conservation status  
    virtual double calculateConservationRisk() const {  
        return isEndangered() ? 1.0 : 0.5;  
    }  
};  

// Correct LSP Implementation with Consistent Behavior  
class EndangeredSpecies : public ProtectedAnimal {  
private:  
    string speciesName;  
    int populationCount;  
    bool endangered;  

public:  
    EndangeredSpecies(const string& name, int count, bool status)  
        : speciesName(name), populationCount(count), endangered(status) {}  

    string getSpeciesName() const override {  
        return speciesName;  
    }  

    int getPopulationCount() const override {  
        return populationCount;  
    }  

    bool isEndangered() const override {  
        return endangered;  
    }  

    // More nuanced risk calculation  
    double calculateConservationRisk() const override {  
        if (populationCount < 50) return 1.0;  // High risk  
        if (populationCount < 200) return 0.75;  // Moderate risk  
        return 0.25;  // Low risk  
    }  
};  

class MammalSpecies : public ProtectedAnimal {  
private:  
    string speciesName;  
    int populationCount;  
    string habitatType;  

public:  
    MammalSpecies(const string& name, int count, const string& habitat)  
        : speciesName(name), populationCount(count), habitatType(habitat) {}  

    string getSpeciesName() const override {  
        return speciesName;  
    }  

    int getPopulationCount() const override {  
        return populationCount;  
    }  

    bool isEndangered() const override {  
        return populationCount < 100;  
    }  

    double calculateConservationRisk() const override {  
        if (habitatType == "Critically Threatened") return 1.0;  
        return ProtectedAnimal::calculateConservationRisk();  
    }  
};  

// New valid subclass adhering to LSP  
class BirdSpecies : public ProtectedAnimal {  
private:  
    string speciesName;  
    int populationCount;  
    bool migratory;  

public:  
    BirdSpecies(const string& name, int count, bool isMigratory)  
        : speciesName(name), populationCount(count), migratory(isMigratory) {}  

    string getSpeciesName() const override {  
        return speciesName;  
    }  

    int getPopulationCount() const override {  
        return populationCount;  
    }  

    bool isEndangered() const override {  
        return populationCount < 50;  
    }  

    double calculateConservationRisk() const override {  
        if (migratory) return ProtectedAnimal::calculateConservationRisk() + 0.25;  
        return ProtectedAnimal::calculateConservationRisk();  
    }  
};  

// Conservation Risk Assessment Manager  
class ConservationRiskManager {  
public:  
    static void assessConservationRisk(const ProtectedAnimal& animal) {  
        cout << "Species: " << animal.getSpeciesName() << endl;  
        cout << "Population: " << animal.getPopulationCount() << endl;  
        cout << "Conservation Risk: " << animal.calculateConservationRisk() << endl;  
    }  
};  

// Demonstration of LSP  
void demonstrateLSPInConservation() {  
    EndangeredSpecies tiger("Bengal Tiger", 45, true);  
    MammalSpecies elephant("African Elephant", 120, "Savanna");  
    BirdSpecies parrot("Amazon Parrot", 30, true);  

    ConservationRiskManager::assessConservationRisk(tiger);  
    ConservationRiskManager::assessConservationRisk(elephant);  
    ConservationRiskManager::assessConservationRisk(parrot);  
}  

int main() {  
    demonstrateLSPInConservation();  
    return 0;  
}
