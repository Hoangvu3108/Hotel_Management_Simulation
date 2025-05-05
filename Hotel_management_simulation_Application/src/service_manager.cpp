#include "../inc/service_manager.hpp"
vector<string> list_service_name = {"khong su dung dich vu","tap gym mien phi","to chuc sinh nhat","do xe","cham soc thu cung","dat do an","spa va massage"};
vector<Service> list_service;
bool ServiceManager::IsServiceExists(const service_option& option){
    for(auto& service : list_service){
        for(auto& service_ : service.getService()){
            if(service_.first == option)
                return SERVICE_EXISTS;
        }
    }
    return SERVICE_NOT_EXISTS;
}
bool ServiceManager::AddService(const int& service_number,const int& price){
    service_option option = static_cast<service_option>(service_number);
    if(IsServiceExists(option) == SERVICE_NOT_EXISTS){
        list_service.emplace_back(option,price);
        return SUCCESS;
    }
    return FAILURE;
}
bool ServiceManager::deleteService(const int& service_number){
    service_option option = static_cast<service_option>(service_number);
    for(auto& service : list_service){
        for(auto& service_ : service.getService()){
            if(service_.first == option){
                service.deleteService(option);
                return SUCCESS;
            }
        }
    }
    return FAILURE;
}
bool ServiceManager::ShowListService(){
    if(list_service.empty()){    
        return FAILURE;
    }
    cout << left << setw(20) << "ten dich vu" << setw(20) << "gia dich vu" << endl;
    // Dòng kẻ ngang
    cout << setfill('-') << setw(50) << "-" << endl;

    // Reset fill về mặc định (space)
    cout << setfill(' ');

    for(const auto& service : list_service){
        for(const auto& service_ : service.getService())
            cout << left << setw(20) << list_service_name[service_.first] << setw(2) << to_string(service_.second) << " $"  << endl;
    }
    return SUCCESS;
}