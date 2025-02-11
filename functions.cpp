#include<iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include"functions.h"
#include"structures.h"
using namespace std;

void printUsage() {
    cout << "Usage: lz77 -i <input file> -o <output file> -t <mode> [-n <buffer size>] [-k <history size>]" << endl;
    cout << "Modes: c (compress), d (decompress)" << endl;
}
void compress(const string& inputFile, const string& outputFile, int historySize, int bufferSize) {
    ifstream in(inputFile, ios::in | ios::binary);
    ofstream out(outputFile, ios::out | ios::binary);
    if (!in || !out) {
        cerr << "Error opening files." << endl;
        return;
    }

    string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    vector<Token> compressed;
    size_t pos = 0;
    int bestOffset = 0, bestLength = 0;
    size_t start;
    int matchLength;
    char nextChar;
    while (pos < data.size()) {
        bestOffset = 0, bestLength = 0;
        start = (pos > historySize) ? pos - historySize : 0;
        for (size_t i = start; i < pos; i++) {
            matchLength = 0;
            while (matchLength < bufferSize && pos + matchLength < data.size() &&
                data[i + matchLength] == data[pos + matchLength]) {
                matchLength++;
            }
            if (matchLength > bestLength) {
                bestOffset = pos - i;
                bestLength = matchLength;
            }
        }
        nextChar = (pos + bestLength < data.size()) ? data[pos + bestLength] : '\0';
        compressed.push_back({ (char)(bestOffset), (char)bestLength, nextChar });
        pos += bestLength + 1;
    }

    for (const auto& token : compressed) {
        out.write(reinterpret_cast<const char*>(&token), sizeof(Token));
    }
	cout << "File compressed successfully" << endl;
}

void decompress(const string& inputFile, const string& outputFile) {
    ifstream in(inputFile, ios::in | ios::binary);
    ofstream out(outputFile, ios::out | ios::binary);
    if (!in || !out) {
        cerr << "Error opening files." << endl;
        return;
    }

    vector<char> decompressed;
    Token token;
    while (in.read(reinterpret_cast<char*>(&token), sizeof(Token))) {
        int start = decompressed.size() - ((int)token.offset);
        for (int i = 0; i < ((int)token.length); i++) {
            decompressed.push_back(decompressed[start + i]);
        }
        if (token.nextChar != '\0') {
            decompressed.push_back(token.nextChar);
        }
    }

    out.write(decompressed.data(), decompressed.size());
	cout << "File decompressed successfully" << endl;
}
