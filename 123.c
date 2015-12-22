#include <sys/types.h>
#include <sys/socket.h>

ssize_t recv(int s, void *bug, size_t len,int flags);
ssize_t recvfrom(int s, void *buf, size_t len, int flags,
struct sockaddr *from, socklen_t *fromlen);
