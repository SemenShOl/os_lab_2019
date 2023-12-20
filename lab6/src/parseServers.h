struct Server {
  char ip[255];
  int port;
};
void parseServers(struct Server* to, unsigned int* servers_num, char* servers);