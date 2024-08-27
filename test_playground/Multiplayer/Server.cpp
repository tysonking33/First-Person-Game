#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <fcntl.h>

#define PORT 8080

int main()
{
    int socket_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in dest_addr;
    socklen_t addrlen = sizeof(dest_addr);
    char buffer[128];

    // Initialize server_addr
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 1. create UDP socket
    if ((socket_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        std::cerr << "failed to create server socket" << std::endl;
        return 1;
    }

    int flags = fcntl(socket_fd, F_GETFL, 0);
    fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK);

    // 2. bind socket to server address
    if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << "failed to bind server socket" << std::endl;
        close(socket_fd);
        return 1;
    }

    // 3. wait for datagram packet to arrive from client
    bool wait = true;
    while (wait)
    {
        memset(buffer, 0, sizeof(buffer)); // Clear buffer before receiving

        int recv_len;
        if ((recv_len = recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&dest_addr, &addrlen)) < 0)
        {
            std::cerr << "failed to receive value" << std::endl;
            continue;
        }

        buffer[127] = '\0'; // Ensure null-termination
        std::string str(buffer);
        buffer[recv_len] = '\0';
        std::cout << "recieved string: " << str << std::endl;

        if (str.compare("EXIT") == 0)
        {
            wait = false;
        }
        else
        {
            const char bean[] = "beans";
            if (sendto(socket_fd, bean, strlen(bean), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0)
            {
                std::cerr << "failed to send beans" << std::endl;
            }
        }
    }

    if (close(socket_fd) < 0)
    {
        std::cerr << "failed to close socket" << std::endl;
    }

    return 0;
}
