#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <limits>
using namespace std;

// Abstract base class defining core conservation strategy
class ConservationStrategy {
public:
    virtual ~ConservationStrategy() = default;

    // Pure virtual methods to be implemented by derived strategies
    virtual void implementConservationPlan() = 0;
    virtual double calculateConservationImpact() = 0;
    virtual string getStrategyType() const = 0;
};

// Concrete strategy implementations
class HabitatPreservationStrategy : public ConservationStrategy {
private:
    string preservationArea;
    double protectedLandArea;

public:
    HabitatPreservationStrategy(const string& area, double landArea)
        : preservationArea(area), protectedLandArea(landArea) {}

    void implementConservationPlan() override {
        cout << "Implementing Habitat Preservation Strategy for " << preservationArea << endl;
    }

    double calculateConservationImpact() override {
        return protectedLandArea * 0.75; // Impact calculation
    }

    string getStrategyType() const override {
        return "Habitat Preservation";
    }
};

class SpeciesReintroductionStrategy : public ConservationStrategy {
private:
    string targetSpecies;
    int plannedReintroductions;

public:
    SpeciesReintroductionStrategy(const string& species, int reintroductions)
        : targetSpecies(species), plannedReintroductions(reintroductions) {}

    void implementConservationPlan() override {
        cout << "Implementing Species Reintroduction Strategy for " << targetSpecies << endl;
    }

    double calculateConservationImpact() override {
        return plannedReintroductions * 2.5; // Impact calculation
    }

    string getStrategyType() const override {
        return "Species Reintroduction";
    }
};

// New strategy: Climate Adaptation
class ClimateAdaptationStrategy : public ConservationStrategy {
public:
    void implementConservationPlan() override {
        cout << "Implementing Climate Adaptation Strategy" << endl;
    }

    double calculateConservationImpact() override {
        return 10.0; // Example impact calculation
    }

    string getStrategyType() const override {
        return "Climate Adaptation";
    }
};

// Conservation Manager using OCP
class ConservationManager {
private:
    vector<unique_ptr<ConservationStrategy>> strategies;

public:
    // Add a new strategy dynamically
    void addStrategy(unique_ptr<ConservationStrategy> strategy) {
        strategies.push_back(move(strategy));
    }

    void executeAllStrategies() {
        for (auto& strategy : strategies) {
            strategy->implementConservationPlan();
            double impact = strategy->calculateConservationImpact();
            cout << "Strategy Impact: " << impact
                 << " for " << strategy->getStrategyType() << endl;
        }
    }
};

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

// Class for endangered species management
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

    void generateConservationReport() const override {
        cout << "\n=== Endangered Species Conservation Report ===" << endl;
        displayBasicInfo();
        cout << "Population Count: " << populationCount << endl;
        cout << "Primary Habitat: " << habitat << endl;
    }

    string getConservationStatusDescription() const override {
        switch (conservationStatus) {
            case 1: return "Critical";
            case 2: return "Endangered";
            case 3: return "Vulnerable";
            default: return "Unknown";
        }
    }
};

// Main function demonstrating OCP
int main() {
    ConservationManager conservationManager;

    // Adding and executing conservation strategies
    conservationManager.addStrategy(make_unique<HabitatPreservationStrategy>("Amazon Rainforest", 1000.0));
    conservationManager.addStrategy(make_unique<SpeciesReintroductionStrategy>("Pandas", 50));
    conservationManager.addStrategy(make_unique<ClimateAdaptationStrategy>());

    cout << "\n=== Executing Conservation Strategies ===" << endl;
    conservationManager.executeAllStrategies();

    return 0;
}
