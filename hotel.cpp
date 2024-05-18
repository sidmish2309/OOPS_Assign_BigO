#include <bits/stdc++.h>
using namespace std;



/*
Architecture:
                                                    HotelManagementSystem
                                                             |
    ----------------------------------------------------------------------------------------------------------------------------
    | (has a)                          | (has a)                          |(has a)                                |(has a)
UserManagement                     BookingManagement                FeedbackManagement                         HotelManagement
    |                                  |                                  |                                       |
    |(has to manage user)              |(has to manage booking)           |(has to manage feedback)               |(has Hotels to manage)
   User                              Booking                           Feedback                                 Hotel



*/
class User {  //have data of a user
public:
    int id;
    string name;
    string password;
    string email;

    User(int id, string name, string password, string email) 
        : id(id), name(name), password(password), email(email) {}

    void modifyDetails(string newEmail) {  //modifying email of user
        this->email = newEmail;
        cout << "User details updated" << endl;
    }
};

class Booking {  //have all details needed while booking
public:
    string bookingId;
    string userId;
    string hotelId;
    string checkinDate;
    string checkoutDate;
    string status;

    Booking(string bid, string uid, string hid, string checkIn, string checkOut) 
        : bookingId(bid), userId(uid), hotelId(hid), checkinDate(checkIn), checkoutDate(checkOut), status("Pending") {}

    void getBookingStatus() {  //to check booking status
        cout << "Booking ID: " << bookingId << " Status: " << status << endl;
    }
};

class Feedback {  //have all things needed to give feedback
public:
    string feedbackId;
    string userId;
    string hotelId;
    int rating;
    string comments;

    Feedback(string fid, string uid, string hid, int rate, string comments) 
        : feedbackId(fid), userId(uid), hotelId(hid), rating(rate), comments(comments) {}

    static void getFeedback(vector<Feedback>& feedbacks, const string& hotelId) {  //function to getfeedback
        for (auto& feedback : feedbacks) {
            if (feedback.hotelId == hotelId)
                cout << "Feedback: " << feedback.comments << " ,Rating: " << feedback.rating << endl;
        }
    }
};

class Hotel {  //have all things about a hotel
public:
    string hotelId;
    string name;
    string location;
    int numberOfRooms;
    vector<string> facilities;
    string status;

    Hotel(string id, string n, string loc, int rooms, vector<string> fac)
        : hotelId(id), name(n), location(loc), numberOfRooms(rooms), facilities(fac), status("pending") {}

};

class UserManagement {   //class to manage users (has a relationship)
private:
    vector<User>& users;  //has a relationship

public:
    UserManagement(vector<User>& users) : users(users) {}

    void registerUser(int id, const string& uname, const string& pwd, const string& mail) { //function to register a user
        users.emplace_back(id, uname, pwd, mail);
        cout << "User Registered" << endl;
    }

    void modifyUserDetails(int userId, const string& newEmail) {   //modifyingUser details
        for (auto& user : users) {
            if (user.id == userId) {
                user.modifyDetails(newEmail);
                return;
            }
        }
        cout << "User not found" << endl;
    }

    void deleteUser(int userId) {  //deleting a particular user
        users.erase(remove_if(users.begin(), users.end(),
            [&](User& user) { return user.id == userId; }), users.end());
        cout << "User deleted" << endl;
    }
};

class HotelManagement {  //class to manage hotels
private:
    vector<Hotel>& hotels;  //has a relationship of hotel

public:
    HotelManagement(vector<Hotel>& hotels) : hotels(hotels) {}

    //function to add hotel
    void addHotel(const string& hotelId, const string& name, const string& location, int numberOfRooms, const vector<string>& facilities) {
        hotels.emplace_back(hotelId, name, location, numberOfRooms, facilities);
        cout << "Hotel Added" << endl;
    }

    //function to update hotel
    void updateHotel(const string& hotelId, const string& newName, const string& newLocation, int newRooms, const vector<string>& newFacilities) {
        for (auto& hotel : hotels) {
            if (hotel.hotelId == hotelId) {
                hotel.name = newName;
                hotel.location = newLocation;
                hotel.numberOfRooms = newRooms;
                hotel.facilities = newFacilities;
                cout << "Hotel details updated" << endl;
                return;
            }
        }
        cout << "Hotel not found" << endl;
    }

    //displaying all hotels
    void listHotels() const {
        for (const auto& hotel : hotels) {
            cout << "Hotel ID: " << hotel.hotelId << ", Name: " << hotel.name << ", Location: " << hotel.location << ", Rooms: " << hotel.numberOfRooms << endl;
        }
    }
};


class FeedbackManagement { //class to manage feedback 
private:
    vector<Feedback>& feedbacks;  //has a relationship of feedback

public:
    FeedbackManagement(vector<Feedback>& feed) : feedbacks(feed) {}

    //function to submit feedback
    void submitFeedback(const string& feedbackId, const string& userId, const string& hotelId, int rating, const string& comments) {
        feedbacks.emplace_back(feedbackId, userId, hotelId, rating, comments);
        cout << "Feedback Submitted" << endl;
    }

    //function to get feedback
    void getFeedback(const string& hotelId) {
        Feedback::getFeedback(feedbacks, hotelId);
    }
};

//Class to manage Booking
class BookingManagement {
private:
    vector<Booking>& bookings; //has a relationship of Booking Class

public:
    BookingManagement(vector<Booking>& bookings) : bookings(bookings) {}

    //function to booking a room
    void bookRoom(const string& bookingId, const string& userId, const string& hotelId, const string& checkIn, const string& checkOut) {
        bookings.emplace_back(bookingId, userId, hotelId, checkIn, checkOut);
        cout << "Room Booked for User: " << userId << " at hotel: " << hotelId << endl;
    }

    //function to get booking status
    void getBookingStatus(const string& bookingId) {
        for (auto& b : bookings) {
            if (b.bookingId == bookingId) {
                b.getBookingStatus();
                return;
            }
        }
        cout << "No Booking Found" << endl;
    }
};

//Main HotelManagementSystem class to access entire system
class HotelManagementSystem {
private:
    vector<User> users;
    vector<Booking> bookings;
    vector<Feedback> feedbacks;
    vector<Hotel> hotels;

    UserManagement userManagement;
    BookingManagement bookingManagement;
    FeedbackManagement feedbackManagement;
    HotelManagement hotelManagement;

public:
    HotelManagementSystem()
        : userManagement(users), bookingManagement(bookings), feedbackManagement(feedbacks), hotelManagement(hotels) {}

    UserManagement& getUserManagement() { return userManagement; }

    BookingManagement& getBookingManagement() { return bookingManagement; }

    FeedbackManagement& getFeedbackManagement() { return feedbackManagement; }

    HotelManagement& getHotelManagement() { return hotelManagement; }
};

int main() {
    HotelManagementSystem hms; //singleton class object

    // Register a new user
    string uname = "sid_mish";
    string pwd = "4105";
    string email = "sidmish007@gmail.com";
    hms.getUserManagement().registerUser(1, uname, pwd, email);

    // Modify user details
    string newEmail = "sidnew007@gmail.com";
    hms.getUserManagement().modifyUserDetails(1, newEmail);

    // Book a room for the user
    string bookingId = "B001";
    string hotelId = "H001";
    string checkIn = "2024-06-01";
    string checkOut = "2024-06-05";
    hms.getBookingManagement().bookRoom(bookingId, "1", hotelId, checkIn, checkOut);

    // Check booking status
    hms.getBookingManagement().getBookingStatus(bookingId);

    // Submit feedback for the hotel
    string feedbackId = "F001";
    int rating = 5;
    string comments = "Excellent service!";
    hms.getFeedbackManagement().submitFeedback(feedbackId, "1", hotelId, rating, comments);

    // Retrieve feedback for the hotel
    hms.getFeedbackManagement().getFeedback(hotelId);

    return 0;
}
