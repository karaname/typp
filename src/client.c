#include <stdio.h>
#include <error.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void send_msg_to_server(const char *nickname, int npm, int err, int m, int s)
{
  char buf[64];
  int client_sock;
  struct sockaddr_in servaddr;

  /* Create client socket */
  if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    error(0, 0, "socket() returned negative value");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));

  /* Assign IP, PORT */
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("5.63.158.181");
  servaddr.sin_port = htons(8012);

  /* Connect the client socket to server socket */
  if (connect(client_sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
    error(0, 0, "connect() returned not zero");
    exit(EXIT_FAILURE);
  }

  sprintf(buf, "%s %d %d %.2d:%.2d", nickname, npm, err, m, s);
  write(client_sock, buf, 64);
  close(client_sock);
}
