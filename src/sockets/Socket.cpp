#include "sockets.h"
#include <unistd.h>

Socket::~Socket() {
  close(this->sd);
}