#include "pipe_networking.h"

int main() {
  srand(time(NULL));
  int to_client;
  int from_client;

  to_client = server_setup();

  from_client = server_handshake( &to_client );
  while(1){
    int random = (rand() % 101);
    char path_prefix[100] = "/tmp/";
    char private_path[100];
    sprintf(private_path, "%s%d", path_prefix, *to_client);
    sleep(1);
  }
}
