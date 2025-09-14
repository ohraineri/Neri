#include <neri/net/socket.h>

int create_socket()
{
    int socket_fd, new_socket, opt = 1;
    ssize_t valread;
    struct sockaddr_in address;
    socklen_t addtlen = sizeof(address);
    char buffer[1024] = { 0 };

    if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("\e[41m ERROR \e[49m The socket could not be created");
        exit(EXIT_FAILURE); 
    }

    if ((setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if(bind(socket_fd, (struct sockaddr *)&address, addtlen) < 0) {
        perror("\e[41m ERROR \e[49m The socket bind could not be created");
        exit(EXIT_FAILURE); 
    }

    if((listen(socket_fd, 3)) < 0) {
        perror("\e[41m ERROR \e[49m The listen could not be created");
        exit(EXIT_FAILURE);
    }

    while(1) {
    if((new_socket = accept(socket_fd, (struct sockaddr *)&address, &addtlen)) < 0) {
        perror("\e[41m ERROR \e[49m The accept could not be created");
        exit(EXIT_FAILURE);
    }
    valread = read(new_socket, buffer, 1024 - 1);
    send(new_socket, "test", 4, 0);
    close(new_socket);
    }
    close(socket_fd);
}

