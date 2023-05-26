#include <iostream>
#include <string>
#include <unistd.h>

class ProgressBar {
public:
    ProgressBar(int total) : total(total), current(0) {}

    void update(int amount) {
        current += amount;

        int percent = (int)(((float)current / (float)total) * 100);

        // calculate the length of the progress bar
        int length = (int)((float)percent / 100.0f * 20.0f);

        // output the progress bar to the terminal
        std::cout << "\r[";
        for (int i = 0; i < length; i++) {
            std::cout << "#";
        }
        for (int i = 0; i < 20 - length; i++) {
            std::cout << " ";
        }
        std::cout << "] " << percent << "%" << std::flush;
    }

private:
    int total;
    int current;
};

int main() {
    ProgressBar bar(100);

    for (int i = 0; i < 100; i++) {
        bar.update(1);
        // simulate doing some work
        usleep(100000);
    }

    std::cout << "\nDone." << std::endl;

    return 0;
}

