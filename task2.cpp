#include<bits/stdc++.h>
using namespace std;


/* Architecture
2 Classes--> Inverter, Battery
             /      \
        Solar       NonSolar
         /             \
(PCU,GTI,Regalia)    (Zelio, iCurze)


*/

class Inverter {  //Topmost Class
public:
    string type;   // for solar and non solar
    int current;
    int operatingVoltage;

    Inverter(string type, int current, int operatingVoltage) : type(type), current(current), operatingVoltage(operatingVoltage) {}

    int powerRating() {
        return current * operatingVoltage;
    }
};

//Now, another type of class is Solar
class Battery {  // Inverter has a battery  (Composition is here)
public:
    string companyName;
    int capacity;

    Battery(string companyName, int capacity) : companyName(companyName), capacity(capacity) {}
};

//Now, another type of class is Solar
class Solar : public Inverter { // Some Inverter are Solar (inheritence)
public:
    bool haveBattery;
    bool isGridon;
    bool haveSolarpanels = true;

    Solar(string type, int current, int operatingVoltage, bool isGridon, bool haveBattery) : Inverter(type, current, operatingVoltage), isGridon(isGridon), haveBattery(haveBattery) {}

    bool checkbatteryAvailability() {
        if (haveBattery) {
            cout << "Yes, Inverter have a battery" << endl;
            return true;
        }
        else {
            cout << "No, Inverter do not have a battery" << endl;
            return false;
        }
    }

    void checkgridonAvailability() {
        if (isGridon) {
            cout << "Yes, Inverter have GridOn" << endl;
        }
        else {
            cout << "No, Inverter do not have a GridOn" << endl;
        }
    }
};



// Here I am defining the types of Solar Inverters classes, that will inherit Solar Class  (PCU, GTI, Regalia)
class PCU :public Solar {
public:
    PCU(string type, int current, int operatingVoltage, bool isGridon, bool haveBattery) : Solar(type, current, operatingVoltage, isGridon, haveBattery) {}
};

class GTI :public Solar {
public:
    GTI(string type, int current, int operatingVoltage, bool isGridon, bool haveBattery) : Solar(type, current, operatingVoltage, isGridon, haveBattery) {}
};

class Regalia :public Solar {
public:
    Regalia(string type, int current, int operatingVoltage, bool isGridon, bool haveBattery) : Solar(type, current, operatingVoltage, isGridon, haveBattery) {}
};


//Now, another type of class is NonSolar 
class NonSolar :public Inverter {
public:
    bool haveBattery = true;
    NonSolar(string type, int current, int operatingVoltage) : Inverter(type, current, operatingVoltage) {}

    bool isgridAvailable() {
        return haveBattery == true;
    }
};

// Here I am defining the types of Non-Solar Inverters classes, that will inherit Non-Solar Class  (Zelio, iCruze)
class Zelio : public NonSolar {
public:
    Zelio(string type, int current, int operatingVoltage) : NonSolar(type, current, operatingVoltage) {}
};

class iCurze : public NonSolar {
public:
    iCurze(string type, int current, int operatingVoltage) : NonSolar(type, current, operatingVoltage) {}
};

int main() {
    
    //Sublime Necessity
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    std::ios::sync_with_stdio(false);

    cout<<"Coded by-->siddharth.mishra@bigohtech.com"<<endl<<endl;

    iCurze ic("Non Solar", 7, 20);
    bool batteryCheck = ic.haveBattery;
    int calculatePowerrate = ic.powerRating();

    cout << "Power Rating= " << calculatePowerrate << endl;

    if (batteryCheck) cout << "Yes, The Inverter contains a battery" << endl;
    else cout << "No, The Inverter do not contains a battery" << endl;

    return 0;
}
