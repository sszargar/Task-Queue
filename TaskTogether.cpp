#include <iostream>
#include <math.h>
using namespace std;

///////////////////////////////////////////////////////////////////////////
//
// Class: TaskQueue
//

#ifndef TASKQUEUE_H
#define TASKQUEUE_H

struct Task {
  enum TaskType { LAUNDRY, DISHES, MAKE_BED, VACUUM, MOP_FLOOR, ECE150 };

  TaskType type;         // LAUNDRY, DISHES, etc.
  int      taskID;       // Unique ID per task
  char*    description;  // Task description
};

class TaskQueue {
public:
  bool        enqueue(const Task& t);               // Add a new task
  Task*       dequeue();                            // Remove current task
  const Task* peek() const;                         // What is current task?
  const Task* next(const Task::TaskType& t) const;  // Return next task of type t
  bool        isFull() const;                       // Queue is full
  bool        isEmpty() const;                      // Queue is empty
  bool        quarterFull() const;                  // Queue is < quarter full    
  bool        doubleQueueSize();                    // Double queue size
  bool        halveQueueSize();                     // Halve queue size

  TaskQueue();
  ~TaskQueue();

 private:
  static const int INITIAL_TASKQUEUE_SIZE = 10;

  int   _front;
  int   _back;
  int   _numItems;
  int   _queueSize;  // Current size of _tasks
  Task* _tasks;      // Wrap-around array
};

#endif


/////////////////////////////////PUBLIC METHODS///////////////////////////////////////
bool TaskQueue::enqueue(const Task & t) { // Add a new task
  if (_numItems == _queueSize) {
    return false;
  } else { //_numItems < _queueSize
    _tasks[_back] = t;
    _numItems++;
    if (_back == _queueSize - 1) { //if the back is actually at the back, you need to make the array circular so go back to front
      _back = 0;
    } else {
      _back++;
    }
    return true;
  }
}

Task * TaskQueue::dequeue() { // Remove current task
  if (_numItems == 0) { //the queue is empty
    return 0;
  }

  _front++; //the task at the front is replaced by the task after it
  _numItems--;
  return &_tasks[_front - 1]; //& sends location, not value
}

const Task * TaskQueue::peek() const { // What is current task?
  if (_numItems == 0) { //the queue is empty
    return 0;
  }

  return &_tasks[_front];

}

const Task * TaskQueue::next(const Task::TaskType & t) const { // Return next task of type t
  for (int i = 0; i < _numItems; i++) {
    if (t == _tasks[i].type) {
      return &_tasks[i];
    }
  }

  return 0;
}

bool TaskQueue::isFull() const { // Queue is full
  if (_numItems == _queueSize) {
    return true;
  }

  return false;
}

bool TaskQueue::isEmpty() const { // Queue is empty
  if (_numItems == 0) {
    return true;
  }

  return false;
}

bool TaskQueue::quarterFull() const { // Queue is < quarter full   
  if (_numItems <= ((_queueSize) / 4)) {
    return true;
  }

  return false;
}

bool TaskQueue::doubleQueueSize() { // Double queue size
  Task * _doubleTasks = new(std::nothrow) Task[2 * (_queueSize)]; // make a new queue that's 2x as big

  if (_doubleTasks == 0) { //we can't do it
    return false;
  } else {
    for (int i = 0; i <= _queueSize; i++) { //fill new queue with old tasks
      _doubleTasks[i] = _tasks[i];
    }

    delete[] _tasks; //get rid of old queue
    _tasks = _doubleTasks;
    _queueSize = 2 * (_queueSize);

    return true;
  }

}

bool TaskQueue::halveQueueSize() { // Halve queue size
  Task * _halveTasks = new(std::nothrow) Task[1 / 2 * (_queueSize)];

  if (_halveTasks == 0) { //we can't do it
    return false;
  }

  if (_numItems <= 1 / 2 * (_queueSize)) {
    for (int i = 0; i <= 1 / 2 * _queueSize; i++) { //fill new queue with old tasks
      _halveTasks[i] = _tasks[i];
    }

    delete[] _tasks;
    _tasks = _halveTasks;
    _queueSize = 1 / 2 * (_queueSize);

    return true;
  } else {
    return false;
  }

}

///////////////////////////////////CONSTRUCTORS AND DESTRUCTORS///////////////////////////////
TaskQueue::TaskQueue() { //constructor

  _queueSize = INITIAL_TASKQUEUE_SIZE;
  _front = 0;
  _back = 0;
  _numItems = 0;
  _tasks = new(std::nothrow) Task[_queueSize];

  if (_tasks == 0) {
    _numItems = -1;
  }

}
TaskQueue::~TaskQueue() { //destructor

  _queueSize = 0;
  delete[] _tasks;

}
