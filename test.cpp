#include "csv-reader.h"
#include <iostream>

int main()
{
  // Tests go here.
  CSVReader *reader = new CSVReader("test.csv");
  reader->LoadFile();

  for (int i = 0; i < reader->get_num_rows(); i++) {
    for (int j = 0; j < reader->get_num_cols(); j++) {
      std::cout << "|" << i << "|" << reader->rows[i][j];
    }

    std::cout << "\n";

  }
  delete reader;

  CSVReader *reader2 = new CSVReader("test2.csv");
  reader2->LoadFile();

  for (int i = 0; i < reader2->get_num_rows(); i++) {
    for (int j = 0; j < reader2->get_num_cols(); j++) {
      std::cout << "|" << i << "|" << reader2->rows[i][j];
    }

    std::cout << "\n";

  }
}
