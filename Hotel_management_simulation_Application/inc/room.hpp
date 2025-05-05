#ifndef __ROOM_HPP
#define __ROOM_HPP
#include "Std_Types.hpp"

typedef enum {
    Unavailable,
    Available 
} default_room_status; // Trạng thái phòng: 0 - không có sẵn, 1 - có sẵn
typedef enum {
    Empty ,
    Reserved,
}available_room_status;

typedef int room_number; // Số phòng
typedef map <room_number, available_room_status>room_available_dtype;
typedef map <room_number,default_room_status>room_default_dtype;

class Room {
    private:
        room_available_dtype room_available; // Số phòng và trạng thái có sẵn
        room_default_dtype room_default; // Số phòng và trạng thái mặc định
        public:
        //hàm tạo để thêm phòng bởi manager
        Room(const room_available_dtype& room_available) : room_available(room_available){}
        //trả về danh sách phòng đã thêm 
        room_available_dtype getRoomAvailable() const {return room_available;} 
        //thay đổi trạng thái phòng được gọi bởi employee khi đặt hoặc trả phòng cho khách 
        void CheckInRoom(const int& number){room_available[number] = Reserved;}
        void CheckOutRoom(const int& number){room_available[number] = Empty;}
};
#endif