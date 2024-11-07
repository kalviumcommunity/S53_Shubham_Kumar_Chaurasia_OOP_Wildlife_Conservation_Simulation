#include <iostream>  
#include <string>  
using namespace std;  

class Animal {  
private:  
    string name;  
    int age;  

public:  
    // Default constructor  
    Animal() : name("Unknown"), age(0) {  
        cout << "Default constructor called: " << name << " created." << endl;  
    }  

    // Parameterized constructor  
    Animal(const string& name, int age) : name(name), age(age) {  
        cout << "Parameterized constructor called: " << name << " created." << endl;  
    }  

    // Destructor  
    ~Animal() {  
        cout << "Destructor called: " << name << " destroyed." << endl;  
    }  

    // Method to display animal details  
    void display() const {  
        cout << "Animal Name: " << name << ", Age: " << age << endl;  
    }  
};  

int main() {  
    // User input for animal details  
    string name;  
    int age;  

    cout << "Enter animal name: ";  
    cin >> name; // Input name  
    cout << "Enter animal age: ";  
    cin >> age; // Input age  

    // Creating animal object using parameterized constructor  
    Animal userAnimal(name, age);  
    userAnimal.display();  

    // End of program will trigger destructor  
    return 0;  
}