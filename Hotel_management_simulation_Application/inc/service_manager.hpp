#ifndef __SERVICE_MANAGER_HPP__
#define __SERVICE_MANAGER_HPP__

#include "Std_Types.hpp"
#include "service.hpp"
#include "UI.hpp"
#include <iomanip>

#define SERVICE_EXISTS 0 // Service exists code for functions
#define SERVICE_NOT_EXISTS 1 // Service not exists code for functions
#define SERVICE_NOT_FOUND 2 // Service not found code for functions

class ServiceManager {
    private : 
        bool IsServiceExists(const service_option& name_service); // Checks if the service exists in the list
    
    public :
        bool AddService (const int& service_number, const int &price);
        bool deleteService (const int& service_number); // Deletes the service with the given service number
        bool ShowListService() ; // Displays the list of services

};
extern vector<Service> list_service;
extern vector<string> list_service_name; // List of service names



#endif // __SERVICE_MANAGER_HPP__