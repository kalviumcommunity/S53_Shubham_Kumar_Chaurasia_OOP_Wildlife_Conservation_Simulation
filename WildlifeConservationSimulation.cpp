#include <iostream>  
#include <string>  
#include <vector>  
using namespace std;  

// Base class: Animal  
class Animal {  
protected:  
    string name;  
    int age;  

public:  
    // Constructor  
    Animal(string n = "Unknown", int a = 0) : name(n), age(a) {}  

    // Virtual function for making sound  
    virtual void makeSound() {  
        cout << "Animal sound" << endl;  
    }  

    // Getter methods  
    string getName() const { return name; }  
    int getAge() const { return age; }  
};  

// Single Inheritance: Mammal inherits from Animal  
class Mammal : public Animal {  
private:  
    bool isWarmBlooded;  

public:  
    // Constructor with initialization list  
    Mammal(string n, int a, bool warmBlooded)   
        : Animal(n, a), isWarmBlooded(warmBlooded) {}  

    // Override makeSound method  
    void makeSound() override {  
        cout << name << " makes a mammal sound" << endl;  
    }  

    // Additional method specific to Mammal  
    void nurtureBabies() {  
        cout << name << " nurtures its young" << endl;  
    }  
};  

// Multiple Inheritance Example  
class EndangeredSpecies {  
protected:  
    int populationCount;  
    string conservationStatus;  

public:  
    EndangeredSpecies(int count = 0, string status = "Not Endangered")   
        : populationCount(count), conservationStatus(status) {}  

    void displayConservationStatus() {  
        cout << "Population: " << populationCount   
             << ", Status: " << conservationStatus << endl;  
    }  
};  

// Multilevel Inheritance: Tiger inherits from Mammal and EndangeredSpecies  
class Tiger : public Mammal, public EndangeredSpecies {  
private:  
    string habitat;  

public:  
    // Constructor with comprehensive initialization  
    Tiger(string name, int age, int population, string status, string tigerHabitat)  
        : Mammal(name, age, true),   
          EndangeredSpecies(population, status),  
          habitat(tigerHabitat) {}  

    // Specialized method  
    void displayTigerDetails() {  
        cout << "Tiger Details:" << endl;  
        cout << "Name: " << getName() << endl;  
        cout << "Age: " << getAge() << endl;  
        cout << "Habitat: " << habitat << endl;  
        displayConservationStatus();  
    }  
};  

int main() {  
    // User Input  
    string name, habitat, status;  
    int age, population;  

    // Prompt for Tiger details  
    cout << "Enter Tiger Name: ";  
    getline(cin, name);  

    cout << "Enter Tiger Age: ";  
    cin >> age;  
    cin.ignore(); // Clear input buffer  

    cout << "Enter Tiger Habitat: ";  
    getline(cin, habitat);  

    cout << "Enter Population Count: ";  
    cin >> population;  
    cin.ignore(); // Clear input buffer  

    cout << "Enter Conservation Status: ";  
    getline(cin, status);  

    // Create Tiger object  
    Tiger tiger(name, age, population, status, habitat);  

    // Demonstrate inherited and overridden methods  
    tiger.makeSound();  
    tiger.nurtureBabies();  
    tiger.displayTigerDetails();  

    return 0;  
}