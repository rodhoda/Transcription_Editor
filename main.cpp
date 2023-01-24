#include "transcription.h"

TranscriptionFormatter::TranscriptionFormatter() {}

TranscriptionFormatter::TranscriptionFormatter(std::string guestName, std::string link):
guestFirstName(guestName),fileLink(link) {}

void TranscriptionFormatter::Start() {
    AddtoVector();
    FormatFileLines();
    CreateNewFile();
}

void TranscriptionFormatter::AddtoVector() {
    // Takes the file link, and adds it to an ifstream, which is the class object for files.
    // The while loop goes through each line of the file, and adding the lines that are not
    // blank to the vector

    std::ifstream myfile(fileLink);
    std::string line;

    while (!myfile.eof()) {
        getline(myfile,line);
        if (line.length() == 0)
            continue;
        fileVector.push_back(line);
    }
}

void TranscriptionFormatter::FormatFileLines() {
    std::string newString;
    std::vector<std::string> relevantLines;
    bool pushtoVector = false;

    for (std::string line: fileVector) {
        std::string firstWordPerLine = line.substr(0, line.find(delim));
        std::istringstream newS(line);
        if (firstWordPerLine == hostFirstName || firstWordPerLine == guestFirstName) {

            // Adding each word into the vector individually
            // THIS COULD BE A SEPARATE FUNCTION
            while (getline(newS, newString, delim)) {
                if (!newString.empty())
                    relevantLines.push_back(newString);
            }
            pushtoVector = false;
        }
        else if (!line.empty()) {
            relevantLines.push_back(line);
            pushtoVector = true;
        }
        if (pushtoVector) {
            finalVector.push_back(relevantLines);
            relevantLines.clear();
        }
    }
}

void TranscriptionFormatter::CreateNewFile() {
    std::string newFileName = R"(C:\\Users\\rodho\\CLionProjects\\TranscriptionEditor\\transcription.txt)";
    std::ofstream newFile(newFileName);
    for (int i = 0; i < finalVector.size(); i++)
        if (finalVector[i].size() > 1)
            newFile << "[" <<    finalVector[i][2] << "] " << finalVector[i][0] << " "
            << finalVector[i][1] << "\t" << finalVector[i][3] << "\n" << std::endl;

    newFile.close();
}
