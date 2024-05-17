#include <bits/stdc++.h>
using namespace std;


//Rules:
/*
-> write variables in CamelCase
-> Use solid principles
-> use oops concepts
*/


/* Architecture
Everyone is a people/citizen
so, Topmost Class --> People

                        People  
                    /    |       \
              Driver  Members(MP)  Commissiner
                         |    
                      Ministers
                         |
                        PM

*/

class People {  //Topmost Class
public:
    string name;
    int age;

    People(string name, int age) : name(name), age(age) {}

    string getPeopleName() {
        return name;
    }

    int getAge() {
        return age;
    }
};

class Driver : public People { // Driver is a people (Inheritence)
public:
    Driver(string name, int age) : People(name, age) {}
};

class Mp : public People {  //MP comes under people (Inheritence)
public:
    string constituency;
    string DriverAssigned;
    int spendlimit;
    int expenses;

    Mp(string name, int age, string constituency, string DriverAssigned, int spendlimit, int expenses)
        : People(name, age), constituency(constituency), DriverAssigned(DriverAssigned), spendlimit(spendlimit), expenses(expenses) {}

    string getdrivername() {
        return DriverAssigned;
    }

    string getConstituency() {
        return constituency;
    }

    bool exceedspendinglimit() {
        return expenses > spendlimit;
    }
};

class Minister : public Mp {
public:
    Minister(string name, int age, string DriverAssigned, int spendlimit, int expenses)
        : Mp(name, age, "", DriverAssigned, spendlimit, expenses) {}
};

class PrimeMinister : public Minister {
public:
    bool haveairplane = true;
    bool havePermission;

    PrimeMinister(string name, int age, string DriverAssigned, int spendlimit, int expenses, bool havePermission)
        : Minister(name, age, DriverAssigned, spendlimit, expenses), havePermission(havePermission) {}
};

class Commisioner : public People {  //Commissiner is also a people (Inheritence)
public:
    Commisioner(string name, int age) : People(name, age) {}

    //using the concept of reference of pointers to a class
    void CanArrest(const Mp& p) {
        if (p.expenses > p.spendlimit) {
            cout << "Can Be Arrested" << endl;
        }
        else {
            cout << "Can't Be Arrested" << endl;
        }
    }

    void CanArrest(const PrimeMinister& p) {
        cout << "Pm Can't Be Arrested" << endl;
    }

    void CanArrest(const Minister& m, const PrimeMinister& p) {
        if (m.expenses > m.spendlimit) {
            if (p.havePermission == true) {
                cout << "Can Be arrested" << endl;
            }
            else {
                cout << "Can't be Arrested" << endl;
            }
        }
        else {
            cout << "Can't Be Arrested" << endl;
        }
    }
};

int main() {
    //Sublime Necessity
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    std::ios::sync_with_stdio(false);

    cout<<"Coded by-->siddharth.mishra@bigohtech.com"<<endl<<endl;

    Driver d("Siddharth", 20);
    string name = d.getPeopleName();
    int age = d.getAge();

    // {Limit, expense}

    PrimeMinister pm("Narendra Modi", 50, "Jay Shah", 10000, 200, true); //bcoz PM have the permission power (Composition)

    string drivername = pm.getdrivername();
    cout << "Driver: "<<drivername << endl;

    Commisioner c("Siddharth", 20);
    cout << "Prime Minister" << " " << endl;
    c.CanArrest(pm);

    cout<<endl;
    Minister M("AtalBihari", 60, "Ramesh", 10000, 200000);
    cout << "Minister" << " " << endl;
    c.CanArrest(M, pm);

    return 0;
}
