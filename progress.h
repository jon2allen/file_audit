#include <iostream>
#include <string>
#ifdef _WIN32
 // #include <unistd.h>
#else
#include <unistd.h>
#endif

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
    //************
    // call close to force 100% if needed
    //
    ////************
    void close() {
         int diff;
         if ( current != total ) {
             // std::cout << "status below 100%\n";
         
             diff = total - current;
             update(diff);
         }
    }

    

private:
    int total;
    int current;
};
