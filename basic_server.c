#include "pipe_networking.h"

int main() {
  srand(time(NULL));
  int to_client; // Private
  int from_client; // WKP

  to_client = server_setup();
  from_client = server_handshake( &to_client );

  while(1){
    int random = (rand() % 101);
    char sent_int[20];
    sprintf(sent_int, "%d", random);
    write(to_client, sent_int, sizeof(sent_int));
    sleep(1);
  }
}
