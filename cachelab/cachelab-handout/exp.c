#include <stdio.h>
#include <time.h>

int main() {
    time_t current_time;
    
    // 获取当前时间
    current_time = time(NULL);
    
    if (current_time == -1) {
        perror("time");
        return 1;
    }
    
    printf("Current time: %ld seconds since the Epoch\n", current_time);
    return 0;
}
