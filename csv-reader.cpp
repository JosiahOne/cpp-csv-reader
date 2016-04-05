#include "csv-reader.h"
#include <fstream>
#include <sstream>

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

        std::stringstream strStream;
        strStream << mainFile.rdbuf(); //read the file
        std::string data = strStream.str(); //str holds the content of the file

        GenerateCols(data);

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

LocationIndex CSV_Reader::findString(std::string value)
{
	return findString(value, -1, -1, -1, -1);
}

bool CSV_Reader::GenerateCols(std::string data)
{
    char DOUBLE_QUOTE_CHAR = 34;
    char COMMA_CHAR = 44;
    char END_LINE = '\n';

    std::vector< std::string > col;
    std::string currentCollected = "";
    bool escaping = false;

    for (unsigned int i = 0; i < data.length(); i++) {
      char currentChar = data.at(i);

      if ((currentChar != END_LINE && currentChar != DOUBLE_QUOTE_CHAR && currentChar != COMMA_CHAR)
          || (currentChar == COMMA_CHAR && escaping)
          || (currentChar == END_LINE && escaping)) {
        currentCollected += currentChar;
      } else if ((currentChar == END_LINE && !escaping)) {
        // End of row.
        // If we didn't write out data already, write out the remainder.
        col.push_back(currentCollected);
        numCols = col.size();
        rows.push_back(col);
        col.clear();
        currentCollected = "";
      } else if (currentChar == COMMA_CHAR && !escaping) {
        // End of cell.
        col.push_back(currentCollected);
        currentCollected = "";
      } else if (currentChar == DOUBLE_QUOTE_CHAR && !escaping) {
        // We need to start escaping.
        escaping = true;
      } else if (currentChar == DOUBLE_QUOTE_CHAR && escaping) {
        // If the next char is also a DOUBLE_QUOTE_CHAR, then we want to push a DOUBLE_QUOTE_CHAR.
        if (i < data.length() - 1 && data.at(i+1) == DOUBLE_QUOTE_CHAR) {
          currentCollected += currentChar;
        } else {
          // If not, then this is the end of the escaping period.
          escaping = false;
        }
      }
    }

    if (col.size() != 0) {
      col.push_back(currentCollected);
      rows.push_back(col);
    }

    return true;
}
