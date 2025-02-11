#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
using namespace std;

void compress(const string& inputFile, const string& outputFile, int historySize, int bufferSize);
void decompress(const string& inputFile, const string& outputFile);
void printUsage();
#endif