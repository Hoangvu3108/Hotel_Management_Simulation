#include "../inc/employee.hpp"
Employee::Employee()
{
        int read_result = file_Employee.LogData(GUESS_CSV_PATH,GUESS_CSV);
        if(read_result == FILE_EMPTY) UI::displayMessage("chưa có thông tin khách đặt phòng");
        else if(read_result== FAIL)  UI::displayMessage("tải thông tin khách thất bại");
        else                         UI::displayMessage("tải thông tin khách thành công");
}
void Employee::ShowEmployeeMenu(const string& user_name){
    if(ReturnPosition(user_name) == "LỄ TÂN"){
        Menu menu{"------" + ReturnPosition(user_name) + "------", {
                    {1, "xem ca lam", [this,user_name](){ ReviewWorkshift(user_name);}},
                    {2, "sua thong tin", [this,user_name](){ EditInfoEmployee(user_name);}},
                    {3, "dat phong cho khach", [this](){ BookRoom(); }},
                    {4, "tra phong cho khach", [this](){ UnbookRoom(); }},
                    {5, "danh sach phong", [this](){ ShowRoom(); }},
                    {6, "luu tru thong tin khach", [this](){ SaveGuessInfo(); }},
                    {0, "quay lai", [](){ UI::displayMessage("vui long chon tinh nang"); }}}};
        menu.showMenu();
    }
    else{
        Menu menu{"------" + ReturnPosition(user_name) + "------", {
                    {1, "xem ca lam", [this,user_name](){ ReviewWorkshift(user_name);}},
                    {2, "sua thong tin", [this,user_name](){ EditInfoEmployee(user_name); }},
                    {0, "quay lai", [](){ UI::displayMessage("vui long chon tinh nang"); }}}};
        menu.showMenu();
    }
}
void Employee::ReviewWorkshift(const string& user_name)
{       UI::displayMessage("--------CA LÀM VIỆC--------");
        while(1){
            EmployeeManager::ShowWorkshiftTablebyPhone(user_name);
            inputvalidchoice:
            int choice = UI::getUserChoice("Nhập 0 để quay lại: ");
            if(choice == 0){
                system("cls");
                break;
            }
            else{
                UI::displayMessage("Lựa chọn không hợp lệ");
                goto inputvalidchoice;
            }
        }
}
void Employee::EditInfoEmployee(const string& user_name)
{
    UI::displayMessage("--------SỬA THÔNG TIN--------");
    while(1){
        UI::displayMessage("Vui lòng nhập mật khẩu có 6 chữ số");
        UI::displayMessage("----------------------------------");
        string old_password = UI::getUserInput("vui lòng nhập mật khẩu cũ: ");
        string new_password =  UI::getUserInput("vui lòng nhập mật khẩu mới: ");

        //kiểm tra mật khẩu mới có hợp không và mật khẩu cũ có khớp với sdt của nhân viên hiện tại không
        if(EmployeeManager::editEmployeePassword(accountList,user_name,old_password,new_password) == FAIL){
            UI::displayMessage("mật khẩu không đúng hoặc không hợp lệ");
        }
        UI::displayMessage("\nthay đổi mật khẩu thành cồng");
        UI::displayMessage("------------------------------");
        inputvalidchoice:
        UI::displayMessage("1.Tiếp tục sửa thông tin");
        UI::displayMessage("0.Quay lại");
        int choice = UI::getUserChoice("Vui lòng chọn tính năng: ");
        if (choice == 0) {
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

void Employee::BookRoom()
{
    UI::displayMessage("--------DAT PHONG CHO KHACH--------");
    while (1)
    {
        if (guessEmp.ShowListRoomAvailable() == FAIL)
        {
            UI::displayMessage("Chua co phong nao duoc them");
        }
        UI::displayMessage("X.dang su dung");
        UI::displayMessage("O.dang trong");
        InputValidRoom:
        int room = UI::getUserChoice("Vui long chon phong:");
        if (RoomManager::IsRoomAvailableExist(room) == NOT_EXIST)
        {
            UI::displayMessage("phong khong co san, vui long nhap lai");
            goto InputValidRoom;
        }
        string name = UI::getUserInput("Vui long nhap ten khach:");
        string phone = UI::getUserInput("Vui long nhap sdt khach:");
        string checkin = UI::getUserInput("Vui long nhap ngay checkin:");
        if (guessEmp.BookRoom(room, name, phone, checkin) == SUCCESS)
        {
            UI::displayMessage("Dat phong cho khach thanh cong");
        }
        else
        {
            UI::displayMessage("Phong da duoc dat, vui long chon phong khac");
            goto InputValidRoom;
        }

        UI::displayMessage("1.Tiep tuc dat phong");
        UI::displayMessage("0.Quay lai");
        inputvalidchoice:
        int choice = UI::getUserChoice("Vui long nhap lua chon:");
        UI::displayMessage("--------------------------------");
        if (choice == 0) {
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
void Employee::UnbookRoom()
{
    UI::displayMessage("--------TRA PHONG CHO KHACH--------");
    while (1)
    {
        if(guessEmp.ShowListGuess() == FAIL){
            UI::displayMessage("Chua co khach dat phong");
            return;
        }
        InputValidPhone:
        string phone = UI::getUserInput("vui long nhap sdt:");
        Guess *guess = guessEmp.GuessInfo(phone);
        if (guess == NULL)
        {
            UI::displayMessage("Khong tim thay khach voi sdt" + phone);
            goto InputValidPhone;
        }
        else
        {
            string checkout = UI::getUserInput("Vui long nhap ngay checkout:");
            guessEmp.UnbookRoom(*guess,checkout);
            guessEmp.ServiceFeedbackInfo(*guess);
            UI::displayMessage("Tra phong cho khach thanh cong");
            UI::displayMessage("------------------------------------");
            UI::displayMessage("1.Tiep tuc tra phong");
            UI::displayMessage("0.Quay lai");
            UI::displayMessage("--------------------------------");
            inputvalidchoice:
            int choice = UI::getUserChoice("Vui long nhap lua chon:");
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
}
void Employee::ShowRoom()
{
    UI::displayMessage("--------Danh SACH PHONG--------");
    while (1)
    {
        if (guessEmp.ShowListRoomAvailable() == FAIL)
        {
            UI::displayMessage("Chua co phong nao duoc them");
        }
        UI::displayMessage("X.dang su dung");
        UI::displayMessage("O.dang trong");
        UI::displayMessage("-----------------------------");
        UI::displayMessage("0.Quay lai");
        inputvalidchoice:
        int choice = UI::getUserChoice("Vui long nhap lua chon:");
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

void Employee::SaveGuessInfo(){
    UI::displayMessage("---------LUU TRU THONG TIN----------");
    while(1){
        inputvalidchoice:
        UI::displayMessage("1.luu danh sach khach dat phong");
        UI::displayMessage("0.Quay lai");
        int choice = UI::getUserChoice("Vui long nhap lua chon:");
        if(choice == 1) {
            bool save_result = file_Employee.SaveData(GUESS_CSV_PATH,GUESS_CSV);
            if(save_result == SUCCESS)    {UI::displayMessage("luu tru thanh cong");}
            else                         {UI::displayMessage("khong co thong tin");}
            break;
        }
        else if (choice == 0){
            system("cls");
            break;
        }
        else
        {
            if (choice != 1){
                UI::displayMessage("Lua chon khong hop le, vui long nhap lai");
                goto inputvalidchoice;
            }
        }
    }
}

string Employee::ReturnPosition(const string& user_name){
    //duyệt qua danh sách nhân viên
    for(auto& employee : list_employee){
        //so sánh account và sdt của nhân viên hiện tại
        if(employee.getPhoneNumber() == user_name){
            string position = employee.getPosition();
            if(position == "BV")      {position ="BẢO VỆ";}
            else if(position == "LT") {position = "LỄ TÂN";}
            else if(position == "DB") {position = "ĐẦU BẾP";}
            else if(position == "TV") {position = "TẠP VỤ";}
            else                      {position = "NHÂN VIÊN";}
            return position;
        }
    }
    return string("không hợp lệ");
}