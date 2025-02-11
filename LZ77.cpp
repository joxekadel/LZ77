#include <iostream>
#include <string>
#include <cstring>
#include"functions.h"
#include"structures.h"
using namespace std;


int main(int argc, char* argv[]) {
    if (argc < 7) {
        printUsage();
        return 1;
    }
    string inputFile, outputFile, mode;
    int bufferSize, historySize;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) inputFile = argv[++i];
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) outputFile = argv[++i];
        else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) mode = argv[++i];
        else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) bufferSize = stoi(argv[++i]);
        else if (strcmp(argv[i], "-k") == 0 && i + 1 < argc) historySize = stoi(argv[++i]);
        else {
            printUsage();
            return 1;
        }
    }

    if (mode == "c") {
        compress(inputFile, outputFile, historySize, bufferSize);
    }
    else if (mode == "d") {
        decompress(inputFile, outputFile);
    }
    else {
        printUsage();
        return 1;
    }
    return 0;
}
