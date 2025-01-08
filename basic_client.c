#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  while(1){
    char recieved_int[100];
    read(from_server, recieved_int, sizeof(recieved_int));
    printf("recieved_int %s\n", recieved_int);
    sleep(1);
  }
}
