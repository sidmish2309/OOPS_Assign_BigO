#include <bits/stdc++.h>
using namespace std;

/*
                                ATM--->topup(), totalamountavailable()
                              /     \
                             /       \ 
              Demonetization         Withraw----> isPossible()  
               (has a)               (has a)
                                       
*/

//Forward declaration of classes
class Demonetization;
class Withdraw;

//comparator sort for set of possibilities
bool comp(const vector<int>& a, const vector<int>& b) {
    return a.size() < b.size();
}

set<vector<int>, decltype(comp)*> possibility(comp);

//Recursion technique to generate all possibilities for particular amount to withdraw
void solve(int i, vector<int>& arr, int A, int n, vector<int> ans) {
    if (A < 0) return;
    if (i == n) {
        if (A == 0) {
            possibility.insert(ans);
            return;
        }
        return;
    }

    ans.push_back(arr[i]);
    solve(i + 1, arr, A - arr[i], n, ans);
    ans.pop_back();
    solve(i + 1, arr, A, n, ans);
}

set<int> denominations;
map<int, int> cashData;

class Demonetization {  //Class ATM has a Demonetization system
public:

    //Removing the denominations from entire system and adding newNotes
    void find(int TM, int noteBanned, vector<pair<int, int>>& newNotes) {
        totalmoney = TM;
        totalmoney -= (noteBanned * cashData[noteBanned]);
        denominations.erase(noteBanned);
        cashData.erase(noteBanned);

        // Putting New notes in ATM
        for (auto t : newNotes) { // {notes, times}
            totalmoney += (t.first * t.second);
            denominations.insert(t.first);
            cashData[t.first] = t.second;
        }
    }

private:
    int totalmoney;
};

class Withdraw{ //Class ATM has a Withdraw system
public:

    //Function to withdraw the best option (i.e, denominations of high value)
    void withDraw(int withdrawAmount) {
    possibility.clear();
    vector<int> arr;

    // Putting data in array
    for (auto c : cashData) {
        int times = c.second;
        while (times--) arr.push_back(c.first);
    }

    vector<int> ans;

    solve(0, arr, withdrawAmount, arr.size(), ans);

    //Showing the possibilities--> Although No need just showing
    for(auto x:possibility)
    {
        for(auto y:x) cout<<y<<" ";
        cout<<endl;
    }

    // Writing comparator to sort set of vectors
    vector<int> gg = *(possibility.begin());

    map<int, int> options;
    cout << endl<<"Collect your Cash Amount as :" << endl;
    for (auto d : gg) options[d]++;

    for (auto d : options) cout << d.first << "->" << d.second << endl;
    cout << endl;
}

    //function to check if particular amount is possible or NOT
    bool isPossible(int K) {
    // Checking if amount(K) is a factor of denominations
    int flag = 0;
    for (auto c : cashData) {
        if (K % c.first == 0) flag = 1;
    }
    return (totalmoney >= K && flag == 1);
}

    private:
    int totalmoney;
};

class ATM {
public:
    ATM() : demonetization(), wd(), totalmoney(0) {}

    //using classes which are accessed by object of ATM Class
    Demonetization& getdemon();
    Withdraw& getwithdraw();

    //function in ATM class to check current total available amount
    int totalamountAvailable() {
        totalmoney = 0;
        for (auto d : denominations) totalmoney += (d * cashData[d]);
        return totalmoney;
    }

    //function declaration for topping up money
    void topupMoney(vector<pair<int, int>>& topUps);

private:

    Demonetization demonetization; //Demonetization class object
    Withdraw wd;  //Withdraw Class object
    int totalmoney;
};

//returns a reference to the Demonetization class object 
Demonetization& ATM::getdemon() {
    return demonetization;
}

//returns a reference to the Withdraw class object 
Withdraw& ATM::getwithdraw(){
    return wd;
}

//This is the function of ATM class for toppingup amount
void ATM::topupMoney(vector<pair<int, int>>& topUps) {
    for (auto t : topUps) { // {notes, times}
        totalmoney += t.first * t.second;
        denominations.insert(t.first);
        cashData[t.first] = t.second;
    }
}

int main() {

    // Sublime Necessity
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    std::ios::sync_with_stdio(false);

    cout<<"Coded by-->siddharth.mishra@bigohtech.com"<<endl<<endl;

    ATM a; //singleton class object for accessing all other classes

    denominations.insert(100);
    cashData[100] = 5;

    denominations.insert(200);
    cashData[200] = 3;

    denominations.insert(500);
    cashData[500] = 6;

    denominations.insert(2000);
    cashData[2000] = 8;

    int totalCash = a.totalamountAvailable();
    cout << "Total Amount Available= " << totalCash << endl;

    // Demonetization system
    vector<pair<int, int>> MODIfication; // New Notes that are added
    MODIfication.push_back({5,1});
    MODIfication.push_back({1,1});
    MODIfication.push_back({2,5});

    //accessing demonetization class through object of ATM class
    a.getdemon().find(totalCash, 2000, MODIfication);
    totalCash = a.totalamountAvailable();
    cout << "Total Amount Available after= " << totalCash << endl;


    //accessing Withdraw class through object of ATM class for using withdraw()
    a.getwithdraw().withDraw(1600);

    //accessing withdraw class through object of ATM class for using isPossible()
    bool check=a.getwithdraw().isPossible(22222);
    if(check) cout<<"Desired Amount is Possible, You can Proceed with the request"<<endl;
    else cout<<"Sorry! We can't proceed for desired amount"<<endl<<endl;

    //showing the topup functionality
    vector<pair<int,int>>addtopup;
    addtopup.push_back({50,10});
    a.topupMoney(addtopup);
    cout<<"Available amount after topup :"<<a.totalamountAvailable()<<endl;
    
    return 0;
}
