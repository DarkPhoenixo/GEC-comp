#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

class TextAnalyzer {
private:
    int lineCount;
    int wordCount;
    int charCount;

public:
    TextAnalyzer() : lineCount(0), wordCount(0), charCount(0) {}

    void analyzeText() {
        string inputText;
        cout << "Enter text (type 'END' on a new line to finish):" << endl;

        while (true) {
            getline(cin, inputText);
            if (inputText == "END") {
                break;
            }

            lineCount++;
            charCount += inputText.length();

            stringstream ss(inputText);
            string word;
            while (ss >> word) {
                wordCount++;
            }
        }
    }

    void displayResults() const {
        cout << "\n" << setfill('-') << setw(38) << "-" << setfill(' ') << endl;
        cout << "|"<< left << setw(25) << "Number of lines" 
             << right << setw(10) << lineCount << " |" << endl;
        
        cout << setfill('-') << setw(38) << "-" << setfill(' ') << endl;
        cout <<"|"<< left << setw(25) << "Number of words" 
             << right << setw(10) << wordCount << " |" << endl;

        cout << setfill('-') << setw(38) << "-" << setfill(' ') << endl;
        cout <<"|"<< left << setw(25) << "Number of characters" 
             << right << setw(10) << charCount << " |" << endl;
        cout <<"|"<< setfill('-') << setw(38) << "-" << setfill(' ') << endl;
    }
};

int main() {
    TextAnalyzer analyzer;
    analyzer.analyzeText();
    analyzer.displayResults();
    return 0;
}
