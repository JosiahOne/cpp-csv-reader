#include "csv-reader.h"
#include <iostream>

int main()
{
    // Tests go here.
    CSV_Reader *reader = new CSV_Reader("test.csv");
    reader->LoadFile();

    for (int i = 0; i < reader->getNumRows(); i++) {
        for (int j = 0; j < reader->getNumCols(); j++) {
            std::cout << "|" << i << "|" << reader->rows[i][j];
        }

        std::cout << "\n";

    }
    delete reader;

    CSV_Reader *reader2 = new CSV_Reader("test2.csv");
    reader2->LoadFile();

    for (int i = 0; i < reader2->getNumRows(); i++) {
        for (int j = 0; j < reader2->getNumCols(); j++) {
          std::cout << "|" << i << "|" << reader2->rows[i][j];
        }

        std::cout << "\n";

    }
}
