Here’s a concise summary of C++ threading APIs with a markdown table at the end:

---

### **1. `std::thread` (`<thread>`)**
- **Purpose**: Create and manage threads.
- **Key Methods**:
  - `join()`: Wait for the thread to finish.
  - `detach()`: Let the thread run independently.
  - `get_id()`: Get the thread ID.
  - `hardware_concurrency()`: Get the number of supported threads (static).

**Example**:
```cpp
std::thread t([] { std::cout << "Hello from thread!"; });
t.join();
```

---

### **2. `std::mutex` (`<mutex>`)**
- **Purpose**: Mutual exclusion for critical sections.
- **Key Methods**:
  - `lock()`: Acquire the lock (blocking).
  - `unlock()`: Release the lock.
  - `try_lock()`: Attempt to lock (non-blocking).

**Example**:
```cpp
std::mutex mtx;
mtx.lock();
// Critical section
mtx.unlock();
```

---

### **3. `std::lock_guard` (`<mutex>`)**
- **Purpose**: RAII wrapper for `std::mutex` (automatically unlocks).
- **Key Methods**:
  - Constructor: Locks the mutex.
  - Destructor: Unlocks the mutex.

**Example**:
```cpp
std::mutex mtx;
{
  std::lock_guard<std::mutex> lock(mtx);
  // Critical section
}
```

---

### **4. `std::shared_mutex` (`<shared_mutex>`, C++17)**
- **Purpose**: Reader-writer lock (shared read, exclusive write).
- **Key Methods**:
  - `lock_shared()`: Acquire shared (read) lock.
  - `unlock_shared()`: Release shared lock.
  - `lock()`: Acquire exclusive (write) lock.
  - `unlock()`: Release exclusive lock.

**Example**:
```cpp
std::shared_mutex rw_mutex;
{
  std::shared_lock lock(rw_mutex); // Shared read access
}
{
  std::unique_lock lock(rw_mutex); // Exclusive write access
}
```

---

### **5. `std::condition_variable` (`<condition_variable>`)**
- **Purpose**: Block threads until a condition is met.
- **Key Methods**:
  - `wait(lock, predicate)`: Wait until `predicate` is `true`.
  - `notify_one()`: Wake one waiting thread.
  - `notify_all()`: Wake all waiting threads.

**Example**:
```cpp
std::mutex mtx;
std::condition_variable cv;
bool ready = false;

// Waiter thread
std::unique_lock<std::mutex> lock(mtx);
cv.wait(lock, [] { return ready; });

// Notifier thread
ready = true;
cv.notify_one();
```

---

### **6. `std::unique_lock` (`<mutex>`)**
- **Purpose**: Flexible RAII wrapper (supports deferred locking and manual control).
- **Key Methods**:
  - `lock()`: Acquire the lock.
  - `unlock()`: Release the lock.
  - `try_lock()`: Non-blocking lock attempt.
  - `owns_lock()`: Check if the lock is held.

**Example**:
```cpp
std::mutex mtx;
std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
lock.lock(); // Manual control
```

---

### **Markdown Summary Table**

| **Class**                  | **Header**                  | **Purpose**                                  | **Key Methods/Features**                                                                 |
|----------------------------|-----------------------------|----------------------------------------------|------------------------------------------------------------------------------------------|
| `std::thread`              | `<thread>`                  | Thread management                            | `join()`, `detach()`, `get_id()`, `hardware_concurrency()`                               |
| `std::mutex`               | `<mutex>`                   | Mutual exclusion                             | `lock()`, `unlock()`, `try_lock()`                                                       |
| `std::lock_guard`          | `<mutex>`                   | RAII mutex wrapper                           | Automatic lock/unlock in scope                                                           |
| `std::shared_mutex`        | `<shared_mutex>` (C++17)    | Reader-writer lock                           | `lock_shared()`, `unlock_shared()`, `lock()`, `unlock()`                                 |
| `std::condition_variable`  | `<condition_variable>`      | Block threads until a condition is met       | `wait()`, `notify_one()`, `notify_all()`                                                 |
| `std::unique_lock`         | `<mutex>`                   | Flexible RAII wrapper with manual control    | `lock()`, `unlock()`, `try_lock()`, `owns_lock()`, `defer_lock` argument                 |

---

### **Key Notes**
- **RAII**: Use `std::lock_guard` for simple scoped locking and `std::unique_lock` for advanced scenarios (e.g., with condition variables).
- **Thread Safety**: Always pair `std::condition_variable` with a `std::mutex` or `std::unique_lock`.
- **Shared Access**: Use `std::shared_mutex` for read-heavy workloads to improve concurrency.