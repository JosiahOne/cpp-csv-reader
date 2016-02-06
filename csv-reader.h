/* CSV_Reader
 * CSV_Reader does NOT store large amounts of data.
 * It works by reading a file, and finds the size of the data (rows + cols)
 * Data is accessed "on demand" so we don't need to store anything.
 *
 * Note: Currently all information is stored as std::string.
 */

#pragma once
#include <string>
#include <vector>

class CSV_Reader
{
private:
    int numRows;
    int numCols;
    std::string fileLoc;
    std::vector<std::vector<std::string>> rows;  

    std::vector<std::string> GenerateCols(std::string line);

public:
    CSV_Reader(std::string aFileLoc);
    ~CSV_Reader();
    bool LoadFile();
}