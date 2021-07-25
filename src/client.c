#include <stdio.h>
#include <error.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

bool send_res_to_server(int ln, const char *nickname, int npm, int err, int m, int s)
{
  struct sockaddr_in servaddr;
  char user_val[128];
  int client_sock;

  /* Create client socket */
  if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    error(0, 0, "socket() returned negative value");
    return false;
  }

  memset(&servaddr, 0, sizeof(servaddr));

  /* Assign IP, PORT */
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("5.63.158.181");
  servaddr.sin_port = htons(8012);

  /* Connect the client socket to server socket */
  if (connect(client_sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
    error(0, 0, "connect() returned not zero");
    return false;
  }

  sprintf(user_val, "%d %s %d %d %.2d:%.2d\n", ln, nickname, npm, err, m, s);
  if (write(client_sock, user_val, sizeof(user_val)) == -1) {
    error(0, 0, "write() returned negative value");
    return false;
  }
  close(client_sock);

  return true;
}
