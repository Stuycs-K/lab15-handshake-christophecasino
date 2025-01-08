#include "pipe_networking.h"

static void sighandler(int signo){
  if(signo == SIGINT){
    char path_prefix[100] = "/tmp/";
    char private_path[100];
    char private_pid[100];
    int pid = getpid();
    sprintf(private_pid, "%d", pid);
    sprintf(private_path, "%s%d", path_prefix, pid);
    remove(private_path);
    printf("CLIENT SIGINT");
    exit(0);
  }
}

int main() {
  signal(SIGINT, sighandler);

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
