#include "pipe_networking.h"

static void sighandler(int signo){
  if(signo == SIGINT){
    char path[] = "/tmp/mario";
    remove(path);
    exit(0);
  }
  if(signo == SIGPIPE){
    printf("\n");
  }
}

int main() {
  signal(SIGINT, sighandler);
  signal(SIGPIPE, sighandler);
  srand(time(NULL));
  int to_client; // Private
  int from_client; // WKP
  int WKPfd;

  while(1){
    to_client = server_setup();
    WKPfd = to_client;
    pid_t p;
    p = fork();
    if(p<0){
      perror("fork fail");
      exit(1);
    } else {
      from_client = server_handshake( &to_client );

      while(1){
        int random = (rand() % 101);
        char sent_int[20];
        sprintf(sent_int, "%d", random);
        int n = write(to_client, sent_int, sizeof(sent_int));
        if(n < 0){
          close(to_client);
          to_client = WKPfd;
          break;
        }
        sleep(1);
      }
      exit(0);
    }
  }
}
