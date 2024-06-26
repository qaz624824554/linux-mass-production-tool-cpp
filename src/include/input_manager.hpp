#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

#include <bits/types/struct_timeval.h>
#include <netinet/in.h>
#include <string>

#define INPUT_TYPE_TOUCH 1
#define INPUT_TYPE_NET 2

class InputEvent {

public:
  struct timeval t_time;
  int type;
  int x;
  int y;
  int pressure;
  char str[1024];
  friend class InputDevice;
  friend class TouchScreen;
  friend class Net;
  friend class Input;
  friend class InputDevice;
};

using InputEventPtr = InputEvent *;

class InputDevice;

using InputDevicePtr = InputDevice *;

class InputDevice {
private:
protected:
  std::string name;

public:
  std::string get_name() { return name; }
  virtual int get_input_event(InputEvent &) = 0;
  InputDevice *next;
};

class Input {
private:
  
public:
  InputDevicePtr input_device_head = nullptr;
  Input();
  int get_input_event(InputEvent &);
};

class Net : public InputDevice {
  int sockfd;
  struct sockaddr_in addr;
public:
  Net(Input *input_ptr);
  ~Net();
  int get_input_event(InputEvent &r) override;
};

class TouchScreen : public InputDevice {
  struct tsdev *ts;

public:
  TouchScreen(Input *input_ptr);
  ~TouchScreen();
  int get_input_event(InputEvent &) override;
};

#endif