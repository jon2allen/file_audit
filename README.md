# file_audit
Simple c++ tool to search for files by extension and write to csv file. 
# Notes
Used chatGPT  to create most of the code via Bing chat.

* Main module file_audit.cpp
* progress.h class

I glued pieces together.

- added part to count all files in dir structure
- updated progress bar
- extra prints

for details. took a few iterations to get it right.
https://www.jibsheet.net/linux/index.php/2023/05/24/chatgpt-creating-a-c-file-search-with-csv-output/

Licsnes is MIT.  Not sure about it.  The code looks like many of the examples out on the internet.



Usage: ./file_audit --dir <directory> --csvfile <csv file> --type <file type>
Options:
  --dir <directory>   Specify the directory to scan recursively
  --csvfile <csv file> Specify the output csv file name
  --type <file type>   Specify the file extension type to filter - use .pdf not pdf - include
  -h                   Show this help message and exit
