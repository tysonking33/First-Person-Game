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

    // Initialize dest_addr
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);
    dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 1. create UDP socket
    if ((socket_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        std::cerr << "failed to create client socket" << std::endl;
        return 1;
    }

    int flags = fcntl(socket_fd, F_GETFL, 0);
    fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK);

    for (int i = 0; i < 100000; i++)
    {
        // 2. send message to the server
        std::string bongBongStr = "Bing Bong " + std::to_string(i);
        const char *bongBong = bongBongStr.c_str();

        if (sendto(socket_fd, bongBong, strlen(bongBong), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0)
        {
            std::cerr << "failed to send bongBong" << std::endl;
        }

        // 3. wait for a server message
        memset(buffer, 0, sizeof(buffer)); // Clear buffer before receiving

        if (recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&dest_addr, &addrlen) < 0)
        {
            std::cerr << "failed to receive value" << std::endl;
        }

        // 4. process and wait
        buffer[127] = '\0'; // Ensure null-termination
        std::string outputString(buffer);
        std::cout << "outputString: " << outputString << std::endl;
    }

    std::string goodByeString = "EXIT";
    const char *goodbye = goodByeString.c_str();

    if (sendto(socket_fd, goodbye, strlen(goodbye), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0)
    {
        std::cerr << "failed to send goodbye" << std::endl;
    }

    // 5. close socket
    if (close(socket_fd) < 0)
    {
        std::cerr << "failed to close socket" << std::endl;
    }

    return 0;
}
