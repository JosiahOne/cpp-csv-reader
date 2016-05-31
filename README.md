# cpp-csv-reader
A very simplisitic .CSV file reader. It reads in the file and allows you to access the data like a table.

## Example

    CSVReader reader("test.csv");
    reader.LoadFile();

    for (int i = 0; i < reader.getNumRows(); i++) {
        for (int j = 0; j < reader.getNumCols(); j++) {
            std::cout << reader.rows[i][j] << " ";
        }

        std::cout << "\n";
    }
