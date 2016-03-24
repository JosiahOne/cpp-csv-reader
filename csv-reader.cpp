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
        return false;
    } else {
        std::ifstream mainFile;
        mainFile.open(fileLoc.c_str());
        
        std::string line;
        while (getline(mainFile, line)) {
           rows.push_back(GenerateCols(line));
        }

        mainFile.close();
        numRows = rows.size();
    }

    return true;
}

int CSV_Reader::getNumRows()
{
	return this->numRows;
}

int CSV_Reader::getNumCols()
{
	return this->numCols;
}

/*
 * This function locates the index of the *first* matching value container.
 * Searches rows between: startRow and endRow and
 * Columns between: startCol and endCol.
 * 
 * Negatives values for the indices indicate no value. i.e. startRow == -1 implies startRow = 0 and
 * endRow == -1 implies endRow = LAST_ROW_INDEX
 */
LocationIndex CSV_Reader::findString(std::string value, int startRow, int endRow, int startCol, int endCol)
{
	if (startRow < 0) {
		startRow = 0;
	}

	if (endRow < 0) {
		endRow = this->getNumRows() - 1;
	}

	if (startCol < 0) {
		startCol = 0;
	}

	if (endCol < 0) {
		endCol = this->getNumCols() - 1;
	}

	// Search

	LocationIndex index;
	index.valid = false;

	for (int i = startRow; i <= endRow; i++) {
		for (int j = startCol; j <= endCol; j++) {
			if (this->rows[i][j] == value) {
				index.row = i;
				index.col = j;
				index.valid = true;
			}
		}
	}

	return index;
}

std::vector<std::string> CSV_Reader::GenerateCols(std::string line)
{
    char DOUBLE_QUOTE_CHAR = 34;
    char COMMA_CHAR = 44;

    std::vector<std::string> cols;
    std::string currentCollected = "";
    bool escaping = false;

    for (unsigned int i = 0; i < line.length(); i++) {
        if (!escaping) {
            if (line.at(i) != DOUBLE_QUOTE_CHAR && line.at(i) != COMMA_CHAR) {
                // Append to collected
                currentCollected += line.at(i);
            } else if (line.at(i) == DOUBLE_QUOTE_CHAR) {
                escaping = true;
            } else if (line.at(i) == COMMA_CHAR) {
                // Write out current data
                cols.push_back(currentCollected);
                currentCollected = "";
            }
        } else {
            if (line.at(i) != DOUBLE_QUOTE_CHAR) {
                currentCollected += line.at(i);
            } else {
                if (line.at(i + 1) == DOUBLE_QUOTE_CHAR) {
                    // Escape
                    currentCollected += line.at(i);
                    i++; // Skip next char
                } else {
                    escaping = false;
                }
            }
        }
    }

    // If we didn't write out data already, write out the remainder.
    if (currentCollected != "") {
        cols.push_back(currentCollected);
    }
    
    numCols = cols.size();
    return cols;    
}
