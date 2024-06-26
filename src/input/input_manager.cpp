#include "input_manager.hpp"
#include <iostream>
#include <pthread.h>

#define CYCLE_BUFFER_SIZE 20
static int read_index;
static int write_index;
static InputEvent InputEventBuf[CYCLE_BUFFER_SIZE];

static int isFull(void) {
  return read_index == (write_index + 1) % CYCLE_BUFFER_SIZE;
}
static int isEmpty(void) { return read_index == write_index; }

static void putData(InputEventPtr input_event_ptr) {
  if (!isFull()) {
    InputEventBuf[write_index] = *input_event_ptr;
    write_index = (write_index + 1) % CYCLE_BUFFER_SIZE;
  }
}

static int getData(InputEventPtr input_event_ptr) {
  if (!isEmpty()) {
    *input_event_ptr = InputEventBuf[read_index];
    read_index = (read_index + 1) % CYCLE_BUFFER_SIZE;
    return 0;
  }
  return -1;
}

static pthread_mutex_t mutex;
static pthread_cond_t cond;

void *thread_handler(void *data) {
  auto input_device_ptr = static_cast<InputDevicePtr>(data);
  std::cout << input_device_ptr->get_name() << "创建线程成功" << std::endl;

  InputEvent input_event;

  while (1) {
    if (input_device_ptr->get_input_event(input_event)) {
      continue;
    };
    pthread_mutex_lock(&mutex);
    putData(&input_event);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

Input::Input() {
  new Net(this);
  new TouchScreen(this);

  InputDevicePtr tmp_p = this->input_device_head;
  int ret;
  pthread_t pid;

  while (tmp_p) {
    if (ret < 0) {
      std::cout << tmp_p->get_name() << "设备注册失败" << std::endl;
      return;
    }
    pthread_create(&(pid), NULL, thread_handler, tmp_p);
    tmp_p = tmp_p->next;
  }
}

int Input::get_input_event(InputEvent & input_event) {
  pthread_mutex_lock(&mutex);
  int ret;
  // 有数据，释放锁，无数据，让出锁，休眠，等待唤醒
  if ((ret = getData(&input_event)) == 0) {
    pthread_mutex_unlock(&mutex);
    return ret;
  } else {
    pthread_cond_wait(&cond, &mutex);
    if ((ret = getData(&input_event)) == 0) {
    }
    pthread_mutex_unlock(&mutex);
  }
  return ret;
}