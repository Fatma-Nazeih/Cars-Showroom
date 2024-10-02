#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

static fstream myfile;

int menu() {
    int choice;
    cout << "1. Add a Car" << endl;
    cout << "2. Number of Cars In Certain Model" << endl;
    cout << "3. Rent a Car" << endl;
    cout << "4. Buy a Car" << endl;
    cout << "5. Return a Car" << endl;
    cout << "6. Display Cars" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter Your Choice: ";
    cin >> choice;
    cin.ignore();
    return choice;
}

class Cars {
private:
    vector<string> model;
    vector<string> Color;
    vector<string> EngineSize;
    vector<int> MaxSpeed;
    vector<int> PurchasePrice;
    vector<int> RentalPrice;
    vector<int> Horsepower;
    vector<int> dayrent;
    vector<int> Num;

public:
    bool operator==(const string& s) {
        for (const auto& it : model) {
            if (it == s) {
                return true;
            }
        }
        return false;
    }

    void add(const string& m, const string& c, const string& e, const int& max, const int& b, const int& r, const int& h, const int& n) {
        if (operator==(m)) {
            cout << "Car model already exists." << endl;
        }
        else {
            model.push_back(m);
            Color.push_back(c);
            EngineSize.push_back(e);
            MaxSpeed.push_back(max);
            PurchasePrice.push_back(b);
            RentalPrice.push_back(r);
            Horsepower.push_back(h);
            Num.push_back(n);
            myfile.open("Cars.txt", ios::app);
            if (myfile.is_open()) {
                myfile << m << "," << c << "," << e << "," << max << "," << b << "," << r << "," << h << "," << n << endl;
                myfile.close();
                cout << "Car added successfully." << endl;
            }
            else {
                cout << "Unable to open file." << endl;
            }
        }
    }

    void num(const string& m) {
        for (size_t i = 0; i < model.size(); i++) {
            if (model[i] == m) {
                cout << "Number of cars available: " << Num[i] << endl;
                return;
            }
        }
        cout << "Model not found." << endl;
    }

    double discount(const string& m, const int& d) {
        for (size_t i = 0; i < model.size(); i++) {
            if (model[i] == m) {
                if (d > 10) {
                    return (d / 10) * 5.0;
                }
                break;
            }
        }
        return 0.0;
    }

    void rent(const string& m, const int& d) {
        for (size_t i = 0; i < model.size(); i++) {
            if (model[i] == m) {
                if (Num[i] > 0) {
                    double disc = discount(m, d);
                    double rentalCost = (RentalPrice[i] * d) - disc;
                    Num[i]--;
                    cout << "Car is available. Total cost: " << rentalCost << " USD" << endl;
                    return;
                }
                else {
                    cout << "Car not available." << endl;
                    return;
                }
            }
        }
        cout << "Car model not found." << endl;
    }

    void buy(const string& m) {
        for (size_t i = 0; i < model.size(); i++) {
            if (model[i] == m) {
                if (Num[i] > 0) {
                    Num[i]--;
                    cout << "Car is available. Total cost: " << PurchasePrice[i] << " USD" << endl;
                    return;
                }
                else {
                    cout << "Car not available." << endl;
                    return;
                }
            }
        }
        cout << "Car model not found." << endl;
    }

    void RETURN(const string& m) {
        for (size_t i = 0; i < model.size(); i++) {
            if (model[i] == m) {
                Num[i]++;
                cout << "Car returned successfully." << endl;
                return;
            }
        }
        cout << "Car model not found." << endl;
    }

    void display(const string& m) {
        for (size_t i = 0; i < model.size(); i++) {
            if (model[i] == m) {
                cout << "Model: " << model[i] << endl;
                cout << "Color: " << Color[i] << endl;
                cout << "Engine Size: " << EngineSize[i] << endl;
                cout << "Max Speed: " << MaxSpeed[i] << " km/h" << endl;
                cout << "Purchase Price: " << PurchasePrice[i] << " USD" << endl;
                cout << "Rental Price: " << RentalPrice[i] << " USD" << endl;
                cout << "Horsepower: " << Horsepower[i] << endl;
                cout << "Available Units: " << Num[i] << endl;
                return;
            }
        }
        cout << "Car model not found." << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Cars cars;
    int choice;

    do {
        choice = menu();
        if (choice == 1) {
            string m, color, engineSize;
            int maxSpeed, purchasePrice, rentalPrice, horsepower, num;
            cout << "Enter car model: ";
            getline(cin, m);
            cout << "Enter car color: ";
            getline(cin, color);
            cout << "Enter engine size: ";
            getline(cin, engineSize);
            cout << "Enter max speed (km/h): ";
            cin >> maxSpeed;
            cout << "Enter purchase price (USD): ";
            cin >> purchasePrice;
            cout << "Enter rental price (USD): ";
            cin >> rentalPrice;
            cout << "Enter horsepower: ";
            cin >> horsepower;
            cout << "Enter available units: ";
            cin >> num;
            cin.ignore();  // Clear the newline from the input buffer
            cars.add(m, color, engineSize, maxSpeed, purchasePrice, rentalPrice, horsepower, num);
        }
        else if (choice == 2) {
            string m;
            cout << "Enter car model: ";
            getline(cin, m);
            cars.num(m);
        }
        else if (choice == 3) {
            string m;
            int d;
            cout << "Enter car model: ";
            getline(cin, m);
            cout << "How many days will you rent? ";
            cin >> d;
            cars.rent(m, d);
        }
        else if (choice == 4) {
            string m;
            cout << "Enter car model: ";
            getline(cin, m);
            cars.buy(m);
        }
        else if (choice == 5) {
            string m;
            cout << "Enter car model: ";
            getline(cin, m);
            cars.RETURN(m);
        }
        else if (choice == 6) {
            string m;
            cout << "Enter car model: ";
            getline(cin, m);
            cars.display(m);
        }
    } while (choice != 7);

    return 0;
}
