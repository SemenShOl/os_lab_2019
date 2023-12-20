#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h> 
#include "parseServers.h"
void parseServers(struct Server* to, unsigned int* servers_num, char* servers) {
  FILE *file = fopen(servers, "r");
  if (file == NULL) {
      perror("Unable to open file");
      return;
  }

  char line[256];
  bool flag = false;

  while (fgets(line, sizeof(line), file)) {
      unsigned int port;
      sscanf(line, "%*[^:]:%d", &to[(*servers_num)++].port);
      
      flag = true;
  }

  fclose(file);

  if (!flag) {
    *servers_num = 1;
    to[0].port = 3000;
  }

  for (int i = 0; i < *servers_num; i++) {
    memcpy(to[i].ip, "127.0.0.1", sizeof("127.0.0.1"));
  }
}