//
//  Customer.h
//  project
//
//  Created by Pegah Zargarian on 11/12/21.
//

#ifndef Customer_h
#define Customer_h

#include<string>

using std::string;



class Customer
{
private:

    string  cosNum;
    string    name;
    string    city;
    string   state;
    string     zip;
    int    YTDsale;

public:
    //constructors
    Customer() {
        cosNum = ""; name = ""; city = "";
        state = ""; zip = ""; YTDsale = -1;
    };
    Customer(string cos, string n, string c, string st, string z, int y) {
        cosNum = cos;
        name = n;
        city = c;
        state = st;
        zip = z;
        YTDsale = y;
    }
    //setters

    void setCusNum(string cn) { cosNum = cn; }
    void setName(string nm) { name = nm; }
    void setCity(string cy) { city = cy; }
    void setState(string st) { state = st; }
    void setZip(string zp) { zip = zp; }
    void setYTD(int ytd) { YTDsale = ytd; }

    //getters

    string getCusNum() const { return cosNum; }
    string getName() const { return name; }
    string getCity() const { return city; }
    string getState() const { return state; }
    string getZip() const { return zip; }
    int    getYTD() const { return YTDsale; }


    //other functions they can be more
    bool operator<(Customer aCollege) const { return name < aCollege.getName(); }
    bool operator>(Customer aCollege) const { return name > aCollege.getName(); }
    bool operator==(Customer aCollege) const { return cosNum == aCollege.getCusNum(); }
};


#endif