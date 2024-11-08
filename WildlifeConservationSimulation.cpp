#include <iostream>  
#include <string>  
#include <vector>  
#include <memory>  
using namespace std;  

// Abstract Base Class  
class LibraryResource {  
protected:  
    string title;  
    string uniqueID;  
    bool isAvailable;  

public:  
    // Pure Virtual Function (makes the class Abstract)  
    virtual void displayDetails() = 0;  

    // Virtual Function for checking out  
    virtual bool checkOut() {  
        if (isAvailable) {  
            isAvailable = false;  
            return true;  
        }  
        return false;  
    }  

    // Virtual Function for returning  
    virtual void returnResource() {  
        isAvailable = true;  
    }  

    // Pure Virtual Function for calculating late fees  
    virtual double calculateLateFees(int daysOverdue) = 0;  

    // Virtual Destructor  
    virtual ~LibraryResource() {  
        cout << "LibraryResource Destructor" << endl;  
    }  

    // Setter methods  
    void setTitle(const string& resourceTitle) {  
        title = resourceTitle;  
    }  

    void setUniqueID(const string& id) {  
        uniqueID = id;  
    }  

    // Getter methods  
    string getTitle() const { return title; }  
    string getUniqueID() const { return uniqueID; }  
    bool getAvailabilityStatus() const { return isAvailable; }  
};  

// Concrete Derived Class: Book  
class Book : public LibraryResource {  
private:  
    string author;  
    int pageCount;  

public:  
    Book(const string& bookTitle, const string& bookAuthor, const string& id, int pages)  
        : author(bookAuthor), pageCount(pages) {  
        title = bookTitle;  
        uniqueID = id;  
        isAvailable = true;  
    }  

    // Implementing Pure Virtual Function for Displaying Details  
    void displayDetails() override {  
        cout << "\n--- Book Details ---" << endl;  
        cout << "Title: " << title << endl;  
        cout << "Author: " << author << endl;  
        cout << "Unique ID: " << uniqueID << endl;  
        cout << "Page Count: " << pageCount << endl;  
        cout << "Availability: " << (isAvailable ? "Available" : "Checked Out") << endl;  
    }  

    // Overriding Late Fees Calculation  
    double calculateLateFees(int daysOverdue) override {  
        // Complex late fee calculation based on book type  
        double baseRate = 0.5; // $0.50 per day  
        double maxFee = 20.0;  // Maximum fee  
        
        // Adjust fee based on page count  
        double pageFactor = pageCount > 500 ? 1.5 : 1.0;  
        
        double lateFee = baseRate * daysOverdue * pageFactor;  
        return min(lateFee, maxFee);  
    }  

    // Additional Book-specific method  
    void displayAuthorInfo() {  
        cout << "Author: " << author << endl;  
        cout << "Book Length: " << pageCount << " pages" << endl;  
    }  
};  

// Concrete Derived Class: Digital Resource  
class DigitalResource : public LibraryResource {  
private:  
    string fileFormat;  
    double fileSize;  

public:  
    DigitalResource(const string& resourceTitle, const string& format, const string& id, double size)  
        : fileFormat(format), fileSize(size) {  
        title = resourceTitle;  
        uniqueID = id;  
        isAvailable = true;  
    }  

    // Implementing Pure Virtual Function for Displaying Details  
    void displayDetails() override {  
        cout << "\n--- Digital Resource Details ---" << endl;  
        cout << "Title: " << title << endl;  
        cout << "File Format: " << fileFormat << endl;  
        cout << "Unique ID: " << uniqueID << endl;  
        cout << "File Size: " << fileSize << " MB" << endl;  
        cout << "Availability: " << (isAvailable ? "Available" : "In Use") << endl;  
    }  

    // Overriding Checkout for Digital Resource  
    bool checkOut() override {  
        if (isAvailable) {  
            cout << "Downloading Digital Resource..." << endl;  
            isAvailable = false;  
            return true;  
        }  
        cout << "Resource is currently unavailable for download." << endl;  
        return false;  
    }  

    // Overriding Late Fees Calculation  
    double calculateLateFees(int daysOverdue) override {  
        // Digital resources have different late fee structure  
        double baseRate = 0.25; // $0.25 per day  
        double maxFee = 10.0;   // Maximum fee  
        
        // Adjust fee based on file size  
        double sizeFactor = fileSize > 100 ? 1.2 : 1.0;  
        
        double lateFee = baseRate * daysOverdue * sizeFactor;  
        return min(lateFee, maxFee);  
    }  
};  

// Library Management System  
class LibraryManagementSystem {  
private:  
    vector<unique_ptr<LibraryResource>> resources;  

public:  
    // Add Resource to Library  
    void addResource(unique_ptr<LibraryResource> resource) {  
        resources.push_back(move(resource));  
    }  

    // Display All Resources  
    void displayAllResources() {  
        cout << "\n=== Library Catalog ===" << endl;  
        for (const auto& resource : resources) {  
            resource->displayDetails();  
        }  
    }  

    // Check Out Resource by Unique ID  
    bool checkOutResource(const string& uniqueID) {  
        for (auto& resource : resources) {  
            if (resource->getUniqueID() == uniqueID) {  
                return resource->checkOut();  
            }  
        }  
        cout << "Resource not found." << endl;  
        return false;  
    }  

    // Calculate Late Fees for a Resource  
    double calculateResourceLateFees(const string& uniqueID, int daysOverdue) {  
        for (auto& resource : resources) {  
            if (resource->getUniqueID() == uniqueID) {  
                return resource->calculateLateFees(daysOverdue);  
            }  
        }  
        cout << "Resource not found." << endl;  
        return 0.0;  
    }  
};  

// Demonstration Function  
void demonstrateAbstractClassAndVirtualFunctions() {  
    // Create Library Management System  
    LibraryManagementSystem librarySystem;  

    // Create Different Types of Resources  
    auto book1 = make_unique<Book>("C++ Programming", "John Doe", "BOOK001", 600);  
    auto book2 = make_unique<Book>("Data Structures", "Jane Smith", "BOOK002", 450);  
    
    auto digitalResource1 = make_unique<DigitalResource>("Machine Learning Tutorial", "PDF", "DIGITAL001", 150.5);  
    auto digitalResource2 = make_unique<DigitalResource>("Programming Basics", "EPUB", "DIGITAL002", 75.2);  

    // Add Resources to Library System  
    librarySystem.addResource(move(book1));  
    librarySystem.addResource(move(book2));  
    librarySystem.addResource(move(digitalResource1));  
    librarySystem.addResource(move(digitalResource2));  

    // Display All Resources  
    librarySystem.displayAllResources();  

    // Demonstrate Checkout and Late Fees  
    cout << "\n=== Resource Checkout Simulation ===" << endl;  
    librarySystem.checkOutResource("BOOK001");  
    
    // Calculate Late Fees  
    double lateFees = librarySystem.calculateResourceLateFees("BOOK001", 5);  
    cout << "Late Fees for BOOK001: $" << lateFees << endl;  
}  

int main() {  
    // Demonstrate Abstract Class and Virtual Functions  
    demonstrateAbstractClassAndVirtualFunctions();  

    return 0;  
}