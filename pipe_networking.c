#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  int from_client = 0;
  char path[] = "/tmp/mario";
  remove(path);
  int n = mkfifo(path, 0777);
  if(n == -1) {
    printf("%s\n",strerror(errno));
    exit(1);
  }
  int fd = open(path, O_RDONLY);
  if(fd == -1) {
    printf("%s\n",strerror(errno));
    exit(1);
  }
  from_client = fd;
  return from_client;
}

/*=========================
  server_handshake 
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake_half(int *to_client) {
  int from_client;
  srand(time(NULL));

  // Get client pid.
  char private[100];
  int private_pipe_PID;
  read(*to_client, private, sizeof(private));
  printf("syn %s\n", private);
  sscanf(private, "%d", &private_pipe_PID);

  // Open Private Pipe to client.
  char path_prefix[100] = "/tmp/";
  char private_path[100];
  sprintf(private_path, "%s%d", path_prefix, private_pipe_PID);
  int fd = open(private_path, O_WRONLY);
  if(fd == -1) {
    printf("%s\n",strerror(errno));
    exit(1);
  }
  *to_client = fd;

  // Send acknowledgement of connection through Private Pipe.
  int random = (rand() % 100000);
  char syn_ack[20];
  sprintf(syn_ack, "%d", random);
  write(fd, syn_ack, sizeof(syn_ack));

  // Get second acknowlegdment.
  char ack[100];
  char path[] = "/tmp/mario";
  int df = open(path, O_RDONLY);
  if(df == -1) {
    printf("%s\n",strerror(errno));
    exit(1);
  }
  read(df, ack, sizeof(ack));
  printf("ack %s\n", ack);
  
  from_client = df;
  return from_client;
}

int server_handshake(int *to_client) {
  server_handshake_half(to_client);
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server;
  char WKP_path[] = "/tmp/mario";

  // Open Well Known Pipe to server.
  int fd = open(WKP_path, O_WRONLY);
  if(fd == -1) {
    printf("%s\n",strerror(errno));
    exit(1);
  }

  // Create a Private Pipe.
  int pid = getpid();
  char path_prefix[100] = "/tmp/";
  char private_path[100];
  char private_pid[100];
  sprintf(private_pid, "%d", pid);
  sprintf(private_path, "%s%d", path_prefix, pid);
  remove(private_path);
  int n = mkfifo(private_path, 0777);
  if(n == -1) {
    printf("%s\n",strerror(errno));
    exit(1);
  }

  // Send file descriptor of Private Pipe to the server via WKP.
  write(fd, private_pid, sizeof(private_pid));

  // Wait for syn_ack from server on Private Pipe.
  int df = open(private_path, O_RDONLY);
  if(df == -1) {
    printf("%s\n",strerror(errno));
    exit(1);
  }
  remove(private_path);
  char syn_ack[100];
  read(df, syn_ack, sizeof(syn_ack));
  printf("syn_ack %s\n", syn_ack);

  // Send ack to server on WKP with pid+1.
  int change_num;
  sscanf(syn_ack, "%d", &change_num);
  change_num++;
  char ack[100];
  sprintf(ack, "%d", change_num);
  write(fd, ack, sizeof(ack));
  
  from_server = df;
  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}


