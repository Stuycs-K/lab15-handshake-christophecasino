#include "pipe_networking.h"

int main() {
  
  int to_client;
  int from_client;

  to_client = server_setup();
  printf("to_client %d\n", to_client);

  from_client = server_handshake( &to_client );
}
