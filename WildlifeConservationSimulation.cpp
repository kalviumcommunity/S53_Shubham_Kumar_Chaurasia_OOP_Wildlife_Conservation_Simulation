#include <iostream>  
#include <string>  
#include <vector>  
#include <memory>  
using namespace std;  

// Base class for Animal  
class Animal {  
protected:  
    string name;  
    int age;  

public:  
    // Constructor Overloading (First Type of Polymorphism)  
    Animal() : name("Unknown"), age(0) {}  
    Animal(string n) : name(n), age(0) {}  
    Animal(string n, int a) : name(n), age(a) {}  

    // Virtual function for runtime polymorphism  
    virtual void displayInfo() {  
        cout << "Name: " << name << ", Age: " << age << endl;  
    }  

    // Function Overloading (Second Type of Polymorphism)  
    void makeSound() {  
        cout << "Generic animal sound" << endl;  
    }  

    void makeSound(int volume) {  
        cout << "Generic animal sound at volume " << volume << endl;  
    }  

    // Virtual destructor for proper memory management  
    virtual ~Animal() {  
        cout << "Animal destructor called" << endl;  
    }  

    // Getter methods  
    string getName() const { return name; }  
    int getAge() const { return age; }  
};  

// Derived class: Predator  
class Predator : public Animal {  
private:  
    string huntingTechnique;  

public:  
    // Constructor Overloading  
    Predator(string n, int a, string technique)   
        : Animal(n, a), huntingTechnique(technique) {}  

    // Method Overriding (Runtime Polymorphism)  
    void displayInfo() override {  
        Animal::displayInfo();  
        cout << "Hunting Technique: " << huntingTechnique << endl;  
    }  

    // Overloaded method specific to Predator  
    void makeSound() {  
        cout << name << " roars loudly!" << endl;  
    }  

    void makeSound(bool isAggressive) {  
        if (isAggressive) {  
            cout << name << " roars aggressively!" << endl;  
        } else {  
            cout << name << " makes a calm predator sound" << endl;  
        }  
    }  
};  

// Operator Overloading example  
class ConservationEffort {  
private:  
    int fundedAmount;  

public:  
    ConservationEffort(int amount = 0) : fundedAmount(amount) {}  

    // Operator overloading for addition  
    ConservationEffort operator+(const ConservationEffort& other) {  
        return ConservationEffort(this->fundedAmount + other.fundedAmount);  
    }  

    // Operator overloading for stream insertion  
    friend ostream& operator<<(ostream& os, const ConservationEffort& effort) {  
        os << "Funded Amount: $" << effort.fundedAmount;  
        return os;  
    }  
};  

// Demonstration function with polymorphic behavior  
void demonstratePolymorphism() {  
    // Using polymorphic pointers  
    vector<unique_ptr<Animal>> animals;  

    // Create different types of animals  
    animals.push_back(make_unique<Animal>("Generic Animal", 5));  
    animals.push_back(make_unique<Predator>("Lion", 7, "Stalking"));  

    // Polymorphic method calls  
    cout << "\nPolymorphic Method Demonstration:" << endl;  
    for (const auto& animal : animals) {  
        animal->displayInfo();  
    }  
}  

int main() {  
    // Demonstrate Constructor Overloading  
    cout << "Constructor Overloading Examples:" << endl;  
    Animal generic;  
    Animal namedAnimal("Tiger");  
    Animal fullDetailsAnimal("Elephant", 10);  

    // Demonstrate Method Overloading  
    cout << "\nMethod Overloading Examples:" << endl;  
    Predator lion("Lion", 8, "Hunting in Prides");  
    lion.makeSound();  // No volume  
    lion.makeSound(5);  // With volume  
    lion.makeSound(true);  // Aggressive sound  

    // Demonstrate Operator Overloading  
    cout << "\nOperator Overloading:" << endl;  
    ConservationEffort effort1(50000);  
    ConservationEffort effort2(75000);  
    ConservationEffort totalEffort = effort1 + effort2;  
    cout << "Effort 1: " << effort1 << endl;  
    cout << "Effort 2: " << effort2 << endl;  
    cout << "Total Effort: " << totalEffort << endl;  

    // Demonstrate Polymorphic Behavior  
    demonstratePolymorphism();  

    return 0;  
}