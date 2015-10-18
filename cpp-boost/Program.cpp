#include <string>
#include <fstream>
#include <algorithm>
#include "WordChain.h"

using namespace std;

int main(int c, char **argv) {
    if (c != 4) {
        cout << "Usage:" << endl << "Program <dictionary file> <start word> <end word>" << endl;
        return 0;
    }

    string file = argv[1];
    string beginning = argv[2];
    string end = argv[3];    

    set<string>* dict = new set<string>;
    std::ifstream infile(file);
    
    string word;
    while (infile >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        dict->insert(word);
    }

    cout << "Passing in dictionary..." << endl;
    auto chain = WordChain::create(dict, beginning, end);
    chain.print();

    return 0;
}
