#include "csv-reader.h"
#include <iostream>

int main()
{
    // Tests go here.
    CSV_Reader *reader = new CSV_Reader("test.csv");
    reader->LoadFile();
    
    for (int i = 0; i < reader->numRows; i++) {
        for (int j = 0; j < reader->numCols; j++) {
            std::cout << reader->rows[i][j];
        }

        std::cout << "\n";

    }

}
