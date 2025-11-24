#include <iostream>
#include <thread>
#include <unistd.h>
#include <mutex>
using namespace std;

mutex lock_var;

void foo(int a) {
    sleep(5);
    lock_var.lock();
    cout << a << endl;
    lock_var.unlock();
}

int main() {
    thread threads[20];

    for (int i = 0; i < 20; i++) {
        threads[i] = thread(foo, i);
    }

    for (int i = 0; i < 20; i++) {
        threads[i].join();
    }
}
