#include <iostream>
using namespace std;

class Customer
{
private:
    int id;
    int arrivalTime;
    int serviceTime;

public:
    Customer(int id, int arrival, int service)
    {
        this->id = id;
        arrivalTime = arrival;
        serviceTime = service;
    }

    int getId()
    {
        return id;
    }

    int getArrivalTime()
    {
        return arrivalTime;
    }

    int getServiceTime()
    {
        return serviceTime;
    }
};

int main()
{
    Customer c1(1, 4, 3);

    cout << "Customer ID: " << c1.getId() << endl;
    cout << "Arrival Time: " << c1.getArrivalTime() << endl;
    cout << "Service Time: " << c1.getServiceTime() << endl;

    return 0;
}
