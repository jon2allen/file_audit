// Include the necessary libraries
#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "progress.h"


// Use the std namespace
using namespace std;

// Define a function to parse the command line arguments and return the values
void parse_args(int argc, char* argv[], string& dir, string& csvfile, string& type) {
    // Loop through the arguments
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-h") {
            // Print the usage message and exit
            cout << "Usage: " << argv[0] << " --dir <directory> --csvfile <csv file> --type <file type>\n";
            cout << "Options:\n";
            cout << "  --dir <directory>   Specify the directory to scan recursively\n";
            cout << "  --csvfile <csv file> Specify the output csv file name\n";
            cout << "  --type <file type>   Specify the file extension type to filter - use .pdf not pdf - include \n";
            cout << "  -h                   Show this help message and exit\n";
            exit(0);
        }
        // Check if the argument is --dir
        if (string(argv[i]) == "--dir") {
            // Check if the next argument exists and is not another option
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                // Assign the next argument to dir
                dir = argv[i + 1];
                // Increment i to skip the next argument
                i++;
            }
            else {
                // Throw an exception if the argument is invalid
                throw invalid_argument("Missing or invalid value for --dir");
            }
        }
        // Check if the argument is --csvfile
        else if (string(argv[i]) == "--csvfile") {
            // Check if the next argument exists and is not another option
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                // Assign the next argument to csvfile
                csvfile = argv[i + 1];
                // Increment i to skip the next argument
                i++;
            }
            else {
                // Throw an exception if the argument is invalid
                throw invalid_argument("Missing or invalid value for --csvfile");
            }
        }
        // Check if the argument is --type
        else if (string(argv[i]) == "--type") {
            // Check if the next argument exists and is not another option
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                // Assign the next argument to type
                type = argv[i + 1];
                // Increment i to skip the next argument
                i++;
            }
            else {
                // Throw an exception if the argument is invalid
                throw invalid_argument("Missing or invalid value for --type");
            }
        }
        else {
            // Throw an exception if the argument is unknown
            throw invalid_argument("Unknown option: " + string(argv[i]));
        }
    }
}

// Define a function to format a file time point as YYYY/MM/DD HH:MM:SS
string format_time(filesystem::file_time_type file_time) {
    // Convert the file time point to system clock time point
    auto sys_time = chrono::time_point_cast<chrono::system_clock::duration>(file_time - filesystem::file_time_type::clock::now() + chrono::system_clock::now());
    // Convert the system clock time point to time_t
    time_t tt = chrono::system_clock::to_time_t(sys_time);
    // Convert the time_t to tm structure
    tm local_tm = *localtime(&tt);
    // Create a string stream to format the output
    stringstream ss;
    // Write the year, month, day, hour, minute and second to the stream with leading zeros and separators
    ss << setw(4) << setfill('0') << local_tm.tm_year + 1900 << "/";
    ss << setw(2) << setfill('0') << local_tm.tm_mon + 1 << "/";
    ss << setw(2) << setfill('0') << local_tm.tm_mday << " ";
    ss << setw(2) << setfill('0') << local_tm.tm_hour << ":";
    ss << setw(2) << setfill('0') << local_tm.tm_min << ":";
    ss << setw(2) << setfill('0') << local_tm.tm_sec;
    // Return the formatted string
    return ss.str();
}

// Define a function to write the output to a csv file
void write_csv(const string& dir, const string& csvfile, const string& type) {
    // Create an output file stream and open the csv file
    ofstream ofs;
    ofs.open(csvfile);
    int num_found = 0;
    int num_search = 0;
    float percent = 0.0;
    ProgressBar bar(100);
    // Check if the file stream is open and ready
    if (ofs.is_open()) {
        // Write the header row to the csv file
        ofs << "File Name,Directory,Size,Date\n";
        // Loop through the directory entries in the given directory recursively
        int file_count = std::distance(filesystem::recursive_directory_iterator(dir), filesystem::recursive_directory_iterator{});
        cout << "Total number of files in directory: " << file_count << endl;
        percent = file_count/100*1.0;
        for (const auto& entry : filesystem::recursive_directory_iterator(dir)) {
            num_search++;    
            // Chck if the entry is a regular file and has the given extension type
            // :cout << entry.path().filename().string() <<  "  " << entry.path().extension() << endl;
            if ( (num_search % (int)percent) == 0 )
            {
                bar.update(1);
                // cout << num_found << endl;
            }

            if (entry.is_regular_file() && entry.path().extension() == type) {
                num_found++;
                // Write the file name, directory, size and date to the csv file with commas as separators and quotes as delimiters
                ofs << "\"" << entry.path().filename().string() << "\",";
                ofs << "\"" << entry.path().parent_path().string() << "\",";
                ofs << "\"" << entry.file_size() << "\",";
                ofs << "\"" << format_time(entry.last_write_time()) << "\"\n";
            }
        }
        // Close the file stream
        cout << "\nNumber of entires matched: " << num_found << endl; 
        ofs.close();
    }
    else {
        // Throw an exception if the file stream is not open or ready
        throw runtime_error("Failed to open or write to " + csvfile);
    }
}

// Define the main function
int main(int argc, char* argv[]) {
    try {
        // Declare variables for directory, csv file and type arguments
        string dir, csvfile, type;
        // Parse the command line arguments and assign values to variables
        parse_args(argc, argv, dir, csvfile, type);
        // Write the output to a csv file with given arguments
        write_csv(dir, csvfile, type);
        // Print a success message to standard output
        cout << "Output written to " << csvfile << "\n";
    }
    catch (const exception& e) {
        // Print an error message to standard error with exception message
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}

