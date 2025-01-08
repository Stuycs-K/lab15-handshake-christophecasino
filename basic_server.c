#include "pipe_networking.h"

int main() {
  srand(time(NULL));
  int to_client;
  int from_client;

  to_client = server_setup();

  from_client = server_handshake( &to_client );
  char path_prefix[100] = "/tmp/";
  char private_path[100];
  sprintf(private_path, "%s%d", path_prefix, to_client);
  int fd = open(private_path, O_WRONLY);
  if(fd == -1) {
    printf("%s\n",strerror(errno));
    exit(1);
  }
  while(1){
    int random = (rand() % 101);
    char sent_int[20];
    sprintf(sent_int, "%d", random);
    write(fd, sent_int, sizeof(sent_int));
    sleep(1);
  }
}
