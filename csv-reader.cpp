#include "csv-reader.h"
#include <fstream>

CSV_Reader::CSV_Reader(std::string aFileLoc)
{
    fileLoc = aFileLoc;
}

CSV_Reader::~CSV_Reader()
{
    
}

bool CSV_Reader::LoadFile()
{
    if (fileLoc == "") {
        return false
    } else {
        ifstream mainFile;
        mainFile.open(fileLoc);
        
        std::string line;
        while (getline(mainFile, line)) {
           rows.push_back(GenerateCols(line));
        }   
    }
}

std::vector<std::string> GenerateCols(std::string line)
{
    
}
