#include "input_manager.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h> /* See NOTES */
#include <unistd.h>

#define SERVER_PORT 8888

Net::Net(Input *input_ptr) {
  this->name = "net";
  // 创建socket
  if ((this->sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    throw "socket error";
  }

  // 绑定socket
  memset(&(this->addr), 0, sizeof(this->addr));
  this->addr.sin_port = htons(SERVER_PORT);
  this->addr.sin_family = AF_INET;
  this->addr.sin_addr.s_addr = INADDR_ANY;
  if ((bind(this->sockfd, (struct sockaddr *)&(this->addr),
            sizeof(this->addr))) < 0) {
    throw "bind error";
  }

  this->next = input_ptr->input_device_head;
  input_ptr->input_device_head = this;
}

Net::~Net() { close(sockfd); }

// 改成传引用
int Net::get_input_event(InputEvent & input_event) {
  unsigned int client_addr_len = sizeof(struct sockaddr);
  struct sockaddr_in client_addr;
  char buf[1024];
  // 接收数据并打印
  int recv_len = recvfrom(sockfd, buf, sizeof(buf), 0,
                          (struct sockaddr *)&client_addr, &client_addr_len);

  if (recv_len > 0) {
    buf[recv_len] = '\0';
    input_event.type = INPUT_TYPE_NET;
    strcpy(input_event.str, buf);
    gettimeofday(&input_event.t_time, NULL);
    return 1;
  }
  printf("接收数据失败\n");
  return 0;
}