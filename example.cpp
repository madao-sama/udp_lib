#include <iostream>
#include "udp_lib.hpp"

udp_client_server::udp_cs udp_socket = {8080};
using namespace std;

int main(){
    cout<<udp_socket.get_server_addr()<< " " << udp_socket.get_server_port() <<endl;
    char* rx_msg;
    rx_msg = new char[DEF_BUFFER_SIZE];
    while(1){
        udp_socket.get(rx_msg);
        cout<<udp_socket.get_client_addr()<<" "<<udp_socket.get_client_port()<<endl;
        cout<<rx_msg<<endl;
        udp_socket.send(rx_msg);
    }
}