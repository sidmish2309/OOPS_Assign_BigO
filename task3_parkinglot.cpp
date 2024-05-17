#include <iostream>
#include <vector>
#include <map>
#include <chrono>
using namespace std;

//Rules:
/*
-> write variables in CamelCase
-> Use solid principles
-> use OOP concepts
*/


/* Architecture

                User, ParkingLot,      Vehicle     |
                  \        /    \        /    \    |
                   \      /      \    Car    Bike  |
                TicketManage      \                |---> Admin (using friend Class concept)      
                ParkingManage      \               |
                                  FloorManage      |
                                                   
//Class Desciption:
ParkingLot--> CreateParkingLot(), FindvacantSpot()
TicketManage-->DisplayResult(), & updation to database
Vehicle-->occupyspot(), vacantspot(), calculatetimeinhours()
ParkingManage-->Park(), leave(), printparking()
FloorManage-->Manage to add new floor by resizing it
PaymentMethod--> to provide user functionality for paying amount
Admin--> this class have the acess to all the classes



    //We will use the grid of pointers, as pointers take 8 bytes of space, which is less
    as compared to a 2D grid of any other data type
    classes-> vehicle, parking, admin

    //Vehicle--> rowNo(int), spotNo(int), parkingStartTime(chrono usage)
    //Parking--> rows, columns (grid usage), findVacantSpot, park, leave, update the spot

    // Functions: ->occupySpot(int R, int C),
                  ->vacantSpot()--> this will find the first NULL pointer
                  ->virtual calculateFee()=0
                  ->calculateTime()

                  //calculateTime firstly get the time taken and then use the concept of money charges
                  to calculate the amount for it (Rs 4, Rs 3.5, Rs 2.5)
                  also, it will find the "Way" how the person wants to pay money (credit, cash)
                  ->virtual getType()=0

                  //main working
                  ->focus on concurrency problem


*/

map<pair<string,int>,pair<int,int>> parkingLotData;  //to store entire data of ParkingLot

class User{   
public:
    string name;
    int age;

    // Default constructor
    User() {}

    // Parameterized constructor
    User(string name, int age) : name(name), age(age) {}

    string getUserName() {
        return name;
    }

    int getUserAge() {
        return age;
    }

    friend class Admin;
};


class Vehicle{  //User has Vehicle (composition)-->relation setup
public:
    int rowNo, spotNo;

    //to get local time of the system in c++
    chrono::time_point<chrono::system_clock> parkingStartTime;

public:
    Vehicle(){
        rowNo = -1;
        spotNo = -1;
    }


    //This is used to occupy the current spot
    void occupySpot(int rowtoOccupy, int spottoOccupy)
    {
        rowNo = rowtoOccupy;
        spotNo = spottoOccupy;
    }


    //To vacant the occupied spot and again set rowNo and SpotNo to -1
    void vacantSpot()  
    {
        rowNo = -1;
        spotNo = -1;
    }

    // Time calculation using any inbuilt method
    int calculateTimeinHours(){
        auto now = chrono::system_clock::now();
        auto duration = chrono::duration_cast<chrono::hours>(now - parkingStartTime);
        return duration.count();
    }

    virtual double calculateFee() = 0;
    virtual string getType() = 0;

    friend class Admin;

};

class Car : public Vehicle{
public:
    string getType(){
        return "Car";
    }

    // this will calculate fee based on the timings and Rs/Hr
    double calculateFee(){
        // Assuming calculateTimeinHours() is defined somewhere
        int hours = calculateTimeinHours();
        double payingCost = 0.0;
        if(hours > 0) payingCost = 4.0;
        if(hours > 1) payingCost += 3.5;
        if(hours > 2) payingCost += 2.5 * (hours - 2);

        return payingCost;
    }
};

class Bike : public Vehicle{
public:
    string getType(){
        return "Bike";
    }

    //this will calculate fee based on the timings and Rs/Hr
    double calculateFee(){
        // Assuming calculateTimeinHours() is defined somewhere
        int hours = calculateTimeinHours();
        double payingCost = 1.0;
        if(hours > 0) payingCost = 4.0;
        if(hours > 1) payingCost += 3.5;
        if(hours > 2) payingCost += 2.5 * (hours - 2);

        return payingCost;
    }
};

//
//Main
 class that contains entire ParkingLot System
class ParkingLot{
public:
    int rows;
    int spotsperRows;
    vector<vector<Vehicle*>> grid;

    //Creating Parking Lot of (R*C)
    void CreateParkingLot(int R, int C){
        rows = R;
        spotsperRows = C;
        grid.resize(rows);
        for(int i = 0; i < rows; i++) grid[i].resize(spotsperRows);
    }

   
    pair<int,int> findVacantSpot(){   // this will find the first NULL pointer 
        for(int i = 0; i < rows; i++) 
        {
            for(int j = 0; j < spotsperRows; j++)
            {
                if(grid[i][j] == NULL) return {i, j};
            }
        }


        cout << "No Space found" << endl;

        return {-1, -1};  //if no vacant space found
    }

    friend class Admin;
};

//to manage tickets
class TicketManage: public ParkingLot,public User{
public:
    pair<int,int> locate;

    //firstly checks if find valid spot or not
    void displayResult()
    {
        if(locate.first == -1 && locate.second == -1)
        {
            cout << "Sorry, No space available for your Vehicle" << endl;
        }
        else
        {
            cout << "You have got a perfect parking space" << endl;
            //Now, store this in the database
            parkingLotData[{name, age}] = locate;
        }
    }

    friend class Admin;
};

//This Class will manage the entire parking System
class ParkingManage: public ParkingLot, public User{  //ParkingLot has a ParkingManage System
public:
    pair<int,int> location;

    // Default constructor
    ParkingManage() {}

    // Parameterized constructor to initialize User
    ParkingManage(string name, int age) : User(name, age) {
        location = findVacantSpot();
    }

    //for paking the vehicle at specified spot and returning if done successfully
    bool Park(Vehicle* V, int rowNum, int spotNum){
        if(grid[rowNum][spotNum]!=NULL){
            cout<<"Sorry! No parking available at "<<rowNum<<" "<<spotNum<<endl;
            return false;
        }
        V->occupySpot(rowNum, spotNum);
        grid[rowNum][spotNum] = V;

        cout<<"Thanks for parking your vehicle at "<<rowNum<<" "<<spotNum<<endl;
        return true;
    }

     //Doing function overloading here to park the vehicle
    bool Park(Vehicle *V)
    {
        if (location.first >= 0 && location.second >= 0 && location.first < rows && location.second < spotsperRows)
        {
            bool parked = Park(V, location.first, location.second);
            if (parked)
                location = findVacantSpot(); // Update the location after parking
            return parked;
        }
        else
        {
            cout << "Sorry! No parking available" << endl;
            return false;
        }
    }

    //When leaving the spot
    //The Spot is again set to NULL and then it will display the Fee accordingly
    void leave(Vehicle *V){
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < spotsperRows; j++)
            {
                if(grid[i][j] == V){
                    grid[i][j] = NULL;
                    int fee=V->calculateFee();
                    cout<<"Fee is= "<<fee<<endl;
                    V->vacantSpot();
                }
            }
        }
    }


    //This will print the current status of the parkingLot
    void printParking()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < spotsperRows; j++)
        {
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
}



friend class Admin;

};

//FloorManager Class having floors to manage
class FloorManage: public ParkingLot{ //ParkingLot and Vehicle has a FloorManagement system
public:
    //resizing
    int newFloors;

    // Assuming grid is a member of ParkingLot
    void resizeGrid(int newFloors) {
        grid.resize(newFloors);
    }

    friend class Admin;
};

//To provide user a functionality to pay via creditcard or cash
class PaymentMethod: public User{

    public:
    string paymentWay;
    PaymentMethod(string name, int age, string paymentWay): User(name,age), paymentWay(paymentWay){}
};

//Admin Class have entire access of the system
class Admin{  //Admin has a access to the system (composition)-> relation
    
   public:
   Admin() {}

   //Using the concept of friend class to provide Admin access to all classes
   void access_vehicle(Vehicle &v1){}
   void access_parkinglot(ParkingLot &pl){}
   void access_user(User &u){}
   void access_ticketmanage(TicketManage &tm){}
   void access_parkingmanage(ParkingManage &pm){}
   void access_floormanage(FloorManage &fm){} 
   void access_cars(Car &cc){}
   void access_bikes(Bike &bb){}

};


int main() {
    //Sublime Necessity
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    std::ios::sync_with_stdio(false);

    cout << "Coded by --> siddharth.mishra@bigohtech.com" << endl << endl;
    
    ParkingManage p("John", 30); // Providing arguments for User constructor

    p.CreateParkingLot(3,2);

    Car c1, c2;
    Bike b1;
    p.Park(&c1);
    p.printParking();

    p.Park(&c2,0,0);
    p.printParking();

    p.Park(&c2);
    p.printParking();

    p.Park(&b1,2,1);
    p.printParking();

    p.leave(&c2);
    p.printParking();

    p.leave(&c1);
    p.printParking();

    p.leave(&b1);
    p.printParking();

    return 0;
}
