#ifndef CARWASHSTATION_H
#define CARWASHSTATION_H
#include <vector>
#include <algorithm>
#include "BST.h"
#include "Queue.h"
#include "Booking.h"
#include "Service.h"

template <typename T>
class CarWashStation {
private:
    BST<T> serviceTree;
    Queue<Booking> bookingQueue;
    std::vector<Booking> confirmedBookings;
    double totalRevenue;

public:
    CarWashStation() : totalRevenue(0.0) {}

    void addService(const T& service) {
        serviceTree.insert(service);
        std::cout << "Service added: " << service.getServiceDetails() << std::endl;
    }

    void removeService(const std::string& serviceID) {
        Service dummyService(serviceID, "", 0.0, 0);  // dummy means 'base' object
        if (serviceTree.search(dummyService)) {
            Service actualService = serviceTree.find(dummyService); //actual service available
            serviceTree.remove(actualService);
            std::cout << "Service removed: " << actualService.getServiceDetails() << std::endl;
        }
        else {
            std::cout << "Service not found!" << std::endl;
        }
    }

    void processBooking(const Booking& booking) {
        bookingQueue.enqueue(booking);
        confirmBooking(booking);
        std::cout << "Booking processed: " << booking.getBookingID() << std::endl;
    }

    void confirmBooking(const Booking& booking) {
        Service service(booking.getServiceID(), "", 0.0, 0);
        if (serviceTree.search(service)) {
            Service actualService = serviceTree.find(service);
            confirmedBookings.push_back(booking);
            totalRevenue += actualService.getPrice();
        }
        else {
            std::cout << "Service not found for booking: " << booking.getBookingID() << std::endl;
        }
    }

    double getTotalRevenue() const {
        return totalRevenue;
    }

    size_t getTotalBookings() const {
        return confirmedBookings.size();
    }

    void displayAllServices() const {
        std::cout << "Available Services:\n";
        serviceTree.inOrderTraversal([](const Service& service) {
            std::cout << service.getServiceDetails() << "\n";
            });
    }
};

#endif