#include "../inc/Manager.hpp"
/* Menu lớn */
Manager::Manager(){
    int read_result = file_manager.LogData(ROOM_CSV_PATH,ROOM_CSV);
    if(read_result == FILE_EMPTY) UI::displayMessage("chưa có thông tin danh sách phòng");
    else if(read_result == FAIL)  UI::displayMessage("Tải danh sách dịch vụ thất bai");
    else                          UI::displayMessage("Tải danh sách phòng thành công");
    read_result = file_manager.LogData(SERVICE_CSV_PATH,SERVICE_CSV);
    if(read_result == FILE_EMPTY) UI::displayMessage("chưa có thông tin dịch vụ phòng");
    else if(read_result == FAIL)  UI::displayMessage("Tải danh sách dịch vụ thất bại");
    else                          UI::displayMessage("Tải danh sách dịch vụ thành công");
    read_result = file_manager.LogData(EMPLOYEE_CSV_PATH,EMMPLOYEE_CSV);
    if(read_result == FILE_EMPTY) UI::displayMessage("chưa có thông tin nhân viên");
    else if(read_result == FAIL)  UI::displayMessage("Tải danh sách nhân viên thất bai");
    else                          UI::displayMessage("Tải danh sách nhân viên thành công");
  
}
void Manager::ShowManagerMenu()
{
    
    Menu mainmenu{"Quan Ly", {{1,"Quản lý nhân viên", [this](){ manageEmployee(); }},
                              {2, "Quản lý phòng", [this](){ manageRoom(); }},
                              {3, "Quản lý dịch vụ", [this](){ manageService(); }},
                              {4, "Lưu trữ thông tin", [this](){ SaveDataCSV(); }},
                              {0, "quay lại", [](){ UI::displayMessage("Vui lòng chọn tính năng"); }}}};
    mainmenu.showMenu();
}

void Manager::manageEmployee() {
    Menu employeeMenu("Quản lý nhân viên", {
        {1, "Thêm nhân viên", [this]() { addEmployee(); }},
        {2, "Sửa thông tin nhân viên", [this]() { editEmployee(); }},
        {3, "Xóa nhân viên", [this]() { deleteEmployee(); }},
        {4, "Xem danh sách nhân viên", [this]() { listEmployees(); }},
        {5, "Set ca làm cho nhân viên",[this](){setWorkShift();}},
        {6, "Thời gian làm việc",[this](){TableSchedule();}},
        {0, "Quay lại", []() { UI::displayMessage("Quay lại"); }}
    });

    employeeMenu.showMenu();  // Hiển thị menu quản lý nhân viên
}

void Manager::addEmployee() {
   
    while (true) {
        UI::displayMessage("=== Thêm Nhân Viên ===");

        user_input:
        // Nhập thông tin từ người dùng
        std::string name = UI::getUserInput("Nhập tên nhân viên: ");
        std::string phoneNumber = UI::getUserInput("Nhập số điện thoại (ID): ");
        std::string position = UI::getUserInput("Nhập vị trí công việc (Tạp vụ/Bảo vệ/Đầu bếp/Lễ Tân): ");

        // Thêm nhân viên mới vào danh sách
        if(employeeManage.addEmployee(accountList, name, phoneNumber, position) == FAIL){
            UI::displayMessage("vui lòng nhập lại thông tin: ");
            goto user_input;
        }

        // In ra tên của nhân viên mới
        UI::displayMessage("Thêm thành công nhân viên " + name);

        // Tự động đăng ký tài khoản cho nhân viên với mật khẩu mặc định
        UI::displayMessage("----------------------------");
        inputvalidchoice:
        UI::displayMessage("1.Thêm nhân viên khác");
        UI::displayMessage("0.Quay lai");
        // Hiển thị tùy chọn để thêm nhân viên khác
        int choice = UI::getUserChoice("vui lòng chọn tính năng: ");        
        if (choice == 0) {
            system("cls");
            break;  // Quay lại nếu người dùng chọn 0
        }
        else
        {
            if (choice != 1){
                system("cls");
                UI::displayMessage("Lua chon khong hop le, vui long nhap lai");
                goto inputvalidchoice;
            }
        }
    }
    
}

void Manager::editEmployee() {
    while(1){
        UI::displayMessage("Sửa thông tin nhân viên...");
        // Danh sách nhân viên
        employeeManage.listEmployees();

        //nhập thông tin chỉnh sửa
        UI::displayMessage("Vui lòng nhập tên của nhân viên muốn sửa thông tin: ");
        std::string id = UI::getUserInput("Nhập ID: ");
        std::string newname = UI::getUserInput("Nhập tên mới: ");
        std::string newposition= UI::getUserInput("Nhập công việc mới: ");
    
        //thực hiện cập nhật thông tin nhân viên
        employeeManage.editEmployeeById(id,newname,newposition);

        UI::displayMessage("1.Tiếp tục sửa thông tin");
        UI::displayMessage("0.Quay lại");
        int choice = UI::getUserChoice("nhập lựa chọn: ");
        if(choice == 0){
            system("cls");
            break;
        }
    }
}

void Manager::deleteEmployee() {
    while(1){
        UI::displayMessage("Xóa nhân viên...");
        employeeManage.listEmployees();
        UI::displayMessage("------------------");
        std::string id = UI::getUserInput("Nhập ID của nhân viên muốn xóa: ");
        employeeManage.deleteEmployeeById(id);

        UI::displayMessage("0.Quay lại");
        option:
        int choice = UI::getUserChoice("Nhấn 0 để quay lại: ");
        if(choice == 0){
            system("cls");
            break;
        }
        else{
            UI::displayMessage("Lua chon khong hop le vui long nhap lai");
            goto option;
        }
            
    }
}

void Manager::listEmployees() {
    while(1){
        UI::displayMessage("=== Danh Sách Nhân Viên ===");

        employeeManage.listEmployees();

        UI::displayMessage("------------------");
        option:
        int choice = UI::getUserChoice("Quay lai (0): ");
        if(choice == 0){
            system("cls");
            break;
        }
        else{
            UI::displayMessage("Lua chon khong hop le vui long nhap lai");
            goto option;
        }
    }
}

void Manager::setWorkShift(){
    UI::displayMessage("------------------SET CA LÀM CHO NHÂN VIÊN--------------------");
    while(1){
        employeeManage.listEmployees();
        UI::displayMessage("-------------------------");
        setschedule:
        string id = UI::getUserInput("Nhập id của nhân viẹn muốn set ca làm: ");
        UI::displayMessage(" Vui lòng nhập ca làm việc trong tuần tương ứng với định dạng như sau \n( Thứ - Buổi, Thứ - Buổi, Thứ - Buổi): 2-S, 2-C, 3-C, 4-T, 5-C, 6-S ");
        string workShift = UI::getUserInput("Thứ - Buổi:");
        employeeManage.setWorkShift(id,workShift);
        UI::displayMessage("-------------------------");
        UI::displayMessage("1.Tiếp tục set ca làm việc");
        UI::displayMessage("0. Quay lại");
        int choice = UI::getUserChoice("vui lòng chọn tính năng: ");
        if(choice == 0){
            system("cls");
            break;
        }
        goto setschedule;
    }
}

void Manager::TableSchedule(){
    while(1){
    UI::displayMessage("-------Thời gian làm việc của nhân viên-------");
       employeeManage.ShowWorkshiftTable();
       int choice = UI::getUserChoice("Chọn 0 để quay lại: ");
       if(choice == 0){
          system("cls");
          break; 
       }
    }

}

                                    /* QUẢN LÝ PHÒNG */
void Manager::manageRoom()
{
    Menu Roommenu{"Quản lý phòng", {{1, "thêm phòng", [this](){ AddRoom(); }},
                                    {2, "xóa phòng", [this](){ DeleteRoom(); }},
                                    {3, "xem trạng thái phong", [this](){ ShowListRoom(); }},
                                    {0, "quay lại", [](){ UI::displayMessage("vui lòng chọn tính năng"); }}}};
    Roommenu.showMenu();
}
void Manager::AddRoom()
{
    UI::displayMessage("---------THEM PHONG---------");
    while (1)
    {
        inputvalidroom:
        int new_room = UI::getUserChoice("Nhap phong can them:");
        if(roomManage.IsRoomDefaultExist(new_room) == NOT_EXIST){
            UI::displayMessage("phong khong ton tai, vui long nhap phong khac");
            goto inputvalidroom;
        }
        if(roomManage.AddRoom(new_room) == FAIL)
        {
            UI::displayMessage("phong da duoc them, vui long nhap phong khac");
            goto inputvalidroom;
        }
        
        UI::displayMessage("them phong thanh cong");
        inputvalidchoice:
        UI::displayMessage("1.tiep tuc them");
        UI::displayMessage("0.Quay lai");
        int choice = UI::getUserChoice("Vui long nhap lua chon:");
        UI::displayMessage("--------------------------------");
        if (choice == 0){
            system("cls");
            break;
        } 
        else{
            if(choice != 1){
                UI::displayMessage("Lua chon khong hop le");
                goto inputvalidchoice;
            }
        }
    }
}
void Manager::ShowListRoom()
{
    UI::displayMessage("---------XEM TRANG THAI PHONG---------");
    while (1)
    {
        roomManage.ShowListRoomDefault();
        UI::displayMessage("\nU:\tUnavailable");
        UI::displayMessage("A:\tAvailable");
        inputvalidchoice:
        UI::displayMessage("\n1.Xem thong tin phong");
        UI::displayMessage("0.Quay lai");
        int choice = UI::getUserChoice("\nVui long lua chon:");
        if (choice == 0){
            system("cls");
            break;
        }
        else if (choice == 1)
        {
            UI::displayMessage("---------XEM THONG TIN PHONG---------");
            inputvalidroom:
            int room = UI::getUserChoice("vui long nhap so phong:");
            if (RoomManager::IsRoomAvailableExist(room) == EXIST)
            {
                if (roomManage.RoomInfo(room) == FAIL)
                {
                    UI::displayMessage("Khong co thong tin khach");  
                }
                inputvalidchoice1:
                UI::displayMessage("1.tiep tuc xem thong tin cac phong");
                UI::displayMessage("0.Quay lai");
                int choice = UI::getUserChoice("\nvui long nhap lua chon:");
                if (choice == 0){
                    system("cls");
                    break;
                }
                else if(choice == 1){
                    system("cls");
                    goto inputvalidroom;
                }
                else{
                    system("cls");
                    UI::displayMessage("Lua chon khong hop le");
                    goto inputvalidchoice1;
                }
            }
            else
            {
                system("cls");
                UI::displayMessage("Phong khong co san");
                goto inputvalidchoice1;
            }
        }
        else
        {
            system("cls");
            UI::displayMessage("Lua chon khong hop le, vui long nhap lai");
            goto inputvalidchoice;
        }
    }
}
void Manager::DeleteRoom()
{
    UI::displayMessage("---------XOA PHONG---------");
    while (1)
    {
        roomManage.ShowListRoomDefault();
        int room_delete = UI::getUserChoice("Nhap phong can xoa:");
        roomManage.deleteRoom(room_delete);
        UI::displayMessage("\n1.tiep tuc xoa");
        UI::displayMessage("0.Quay lai");
        inputvalidchoice:
        int choice = UI::getUserChoice("Vui long nhap lua chon:");
        if (choice == 0){
            system("cls");
            break;
        }
        else
        {
            if (choice != 1){
                system("cls");
                UI::displayMessage("Lua chon khong hop le, vui long nhap lai");
                goto inputvalidchoice;
            }
        }
    }
}
                                           /* QUẢN LÝ DỊCH VỤ */
void Manager::manageService()
{
    //doc danh sach dich vu tu file csv

    Menu Roommenu{"Dich vu", {{1, "them dich vu", [this](){ AddService(); }},
                              {2, "xoa dich vu", [this](){ DeleteService(); }},
                              {3, "danh sach dich vu", [this](){ ShowListService(); }},
                              {0, "quay lai", [](){ UI::displayMessage("vui long chon tinh nang"); }}}};
    Roommenu.showMenu();
}
void Manager::AddService()
{
    UI::displayMessage("---------THEM DICH VU---------");
    while (1)
    {
        UI::displayMessage("Dich vu co san");
        UI::displayMessage("----------------------------");
        UI::displayMessage("1.phong gym\n2.to chuc sinh nhat\n3.cho thue xe\n4.cham soc thu cung\n5.dat do an\n6.spa va massage");
        UI::displayMessage("----------------------------");
        InputValidService:
        int service_number = UI::getUserChoice("Nhap so thu tu cua dich vu can them:");
        
        //kiem tra dich vu co hop le khong
        auto IsServiceInputValid = [service_number]()
        {
            return (service_number < TOTAL_SERVICE) ? true : false;
        };

        if (!IsServiceInputValid())
        {
            UI::displayMessage("vui long nhap lua chon hop le");
            goto InputValidService;
        }

        int price = UI::getUserChoiceFloat("Nhap gia dich vu VND:");

        if(serviceManage.AddService(service_number, price) == FAIL)
        {
            UI::displayMessage("dich vu da co san, vui long chon dich vu khac");
        }
        else UI::displayMessage("\nThem dich vu thanh cong");
        UI::displayMessage("1.Tiep tuc them dich vu");
        UI::displayMessage("0.Quay lai");
        inputvalidchoice:
        int choice = UI::getUserChoice("Vui long nhap lua chon:");
        UI::displayMessage("--------------------------------");
        if (choice == 0){
            system("cls");
            break;
        }
        else
        {
            if (choice != 1){
                system("cls");
                UI::displayMessage("Lua chon khong hop le, vui long nhap lai");
                goto inputvalidchoice;
            }
        }
        system("cls");
    }
}
void Manager::DeleteService()
{
    UI::displayMessage("---------XOA DICH VU---------");
    while (1)
    {

        int service_number = UI::getUserChoice("Vui long nhap so thu tu cua dich vu can xoa:");
        if (serviceManage.deleteService(service_number) == FAIL)
        {
            UI::displayMessage("Khong co dich can xoa");
        }
        else UI::displayMessage("\nXoa dich vu thanh cong");
        UI::displayMessage("1.Tiep tuc xoa dich vu");
        UI::displayMessage("0.Quay lai");
        inputvalidchoice:
        int choice = UI::getUserChoice("Vui long nhap lua chon:");
        if (choice == 0){
            system("cls");
            break;
        }
        else
        {
            if (choice != 1){
                system("cls");
                UI::displayMessage("Lua chon khong hop le, vui long nhap lai");
                goto inputvalidchoice;
            }
        }
    }
}
void Manager::ShowListService()
{
    UI::displayMessage("---------DANH SACH DICH VU---------");
    while (1)
    {
        if (serviceManage.ShowListService() == FAIL)
        {
            UI::displayMessage("Khong co san dich vu");
        }
        UI::displayMessage("0.Quay lai");
        inputvalidchoice:
        int choice = UI::getUserChoice("Vui long nhap lua chon:");
        if (choice == 0){
            system("cls");
            break;
        }
        else
        {
            if (choice != 1){
                system("cls");
                UI::displayMessage("Lua chon khong hop le, vui long nhap lai");
                goto inputvalidchoice;
            }
        }
    }
}

void Manager::SaveDataCSV(){
    UI::displayMessage("---------LUU TRU THONG TIN----------");
    while(1){
        intputvalidchoice:
        UI::displayMessage("1.luu tru danh sach phong");
        UI::displayMessage("2.luu tru danh sach dich vu");
        UI::displayMessage("3.Luu tru danh sach thong tin nhan vien");
        int choice = UI::getUserChoice("Vui long nhap lua chon:");
        bool save_result;
        if(choice == 1) {
            save_result = file_manager.SaveData(ROOM_CSV_PATH,ROOM_CSV);
            if(save_result == SUCCESS)  UI::displayMessage("luu tru thanh cong");
            else UI::displayMessage("khong co thong tin");
        }
        else if(choice == 2) {
            save_result = file_manager.SaveData(SERVICE_CSV_PATH,SERVICE_CSV);
            if(save_result == SUCCESS) UI::displayMessage("luu tru thanh cong");
            else UI::displayMessage("khong co thong tin");
        }
        else if(choice == 3){
            save_result = file_manager.SaveData(EMPLOYEE_CSV_PATH,EMMPLOYEE_CSV);
            if(save_result == SUCCESS) UI::displayMessage("luu tru thanh cong");
            else UI::displayMessage("khong co thong tin");
        }
        else{
            system("cls");
            UI::displayMessage("lựa chọn không hợp lệ, vui lòng nhập lại");
            goto intputvalidchoice;
        }
        UI::displayMessage("1.tiếp tục lưu trữ:");
        UI::displayMessage("0.Quay lại");
        choice = UI::getUserChoice("Vui lòng nhập lựa chọn: ");
        if(choice == 0){
            system("cls");
            break;
        }
        goto intputvalidchoice;
    }

}
