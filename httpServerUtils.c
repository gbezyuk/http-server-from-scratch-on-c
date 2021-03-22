fileDescriptor createServerSocket () {
  fileDescriptor server;
  if ((server = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("server file descriptor creation failed");
    exit(EXIT_FAILURE);
  }
  printf("INIT: server socket created (#%d)\n", server);
  return server;
}

void initLocalhostAddress (internetAddress *address) {
  address->sin_family = AF_INET;
  address->sin_addr.s_addr = INADDR_ANY;
  address->sin_port = htons(PORT);
  memset(address->sin_zero, '\0', sizeof address->sin_zero);
  printf("INIT: localhost address initialized\n");
}

void bindServerToLocalhostAddress (fileDescriptor server, internetAddress *address) {
  if (bind(server, (struct sockaddr *)address, sizeof(*address))<0) {
      perror("INIT FAILURE: server socket binding failed");
      exit(EXIT_FAILURE);
  }
  printf("INIT: server bound to the address\n");
}

void startListening (fileDescriptor server) {
  if (listen(server, LISTENING_MODE) < 0) {
      perror("INIT FAILURE: server listening start failed");
      exit(EXIT_FAILURE);
  }
  printf("INIT: listening started\n");
}

fileDescriptor acceptNewInternetConnection (fileDescriptor server, internetAddress *address, size_t *addrlen) {
  fileDescriptor socket = accept(server, (struct sockaddr *)address, (socklen_t*)addrlen);
  if (socket < 0) {
    perror("FAILURE: accepting incoming connection failed");
    exit(EXIT_FAILURE);
  }
  printf("Incoming connection accepted (socket #%d)\n", socket);
  return socket;
}
