// LoadTsv.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <cstring>
#include <chrono>

using namespace std;
using namespace std::chrono;

typedef long long int lli;
typedef unsigned long long int llu;

typedef pair<llu, llu> cube;

map<string, unsigned char> convertStringToInt = { {"U2",18},{"U",1},{"U'",2},
{"R",3},{"R'",4},{"R2",5},
{"L",6},{"L'",7},{"L2",8},
{"D2",9},{"D",10},{"D'",11},
{"F2",12},{"B2",13},
{"F",14},{"F'",15},{"B",16},{"B'",17} };

map<int, string> convertIntToString = { {18,"U2"},{1,"U"},{2,"U'"},
{3,"R"},{4,"R'"},{5,"R2"},
{6,"L"},{7,"L'"},{8,"L2"},
{9,"D2"},{10,"D"},{11,"D'"},
{12,"F2"},{13,"B2"},
{14,"F"},{15,"F'"},{16,"B"},{17,"B'"} };

//int saveOld(const char* outputFile, map<cube, string>& map)
//{
//    ofstream outputStream(outputFile, ios::out | ios::binary);
//
//    if (!outputStream) {
//        cout << "Cannot open output file!" << endl;
//        return 1;
//    }
//
//    // Write number of entries
//    int fileSize = map.size();
//    outputStream.write((char*)&fileSize, sizeof(fileSize));
//
//    auto iter = map.begin();
//    while (iter != map.end())
//    {
//        // Write entry length
//        int entrySize = sizeof(iter->first) + iter->second.length();
//        outputStream.write((char*)&entrySize, sizeof(entrySize));
//
//        // Write cube
//        outputStream.write((char*)&(iter->first), sizeof(iter->first));
//
//        // Write text
//        outputStream.write(iter->second.c_str(), iter->second.length());
//        ++iter;
//    }
//    outputStream.close();
//}
//
//int loadOld(const char* inputFile, map<cube, string>& map)
//{
//    ifstream inputStream(inputFile, ios::in | ios::binary);
//    if (!inputStream) {
//        cout << "Cannot open input file!" << endl;
//        return 1;
//    }
//
//    // Read number of entries
//    int fileSize;
//    inputStream.read((char*)&fileSize, sizeof(fileSize));
//
//    cube cube;
//    char buf[256];
//
//    while (fileSize--)
//    {
//        // Read entry length
//        int entrySize;
//        inputStream.read((char*)&entrySize, sizeof(entrySize));
//
//        // Read cube
//        inputStream.read((char*)&cube, sizeof(cube));
//
//        // Read text
//        entrySize -= sizeof(cube);
//        inputStream.read(buf, entrySize);
//        string turns(buf, entrySize);
//        
//        map.insert({ cube, turns });
//    }
//
//    inputStream.close();
//}
    

//int convertTextToBinOld(const char* inputFile, const char* outputFile)
//{
//    ifstream inputStream(inputFile);
//    if (!inputStream) {
//        cout << "Cannot open input file!" << endl;
//        return 1;
//    }
//
//    ofstream outputStream(outputFile, ios::out | ios::binary);
//    if (!outputStream) {
//        cout << "Cannot open output file!" << endl;
//        return 1;
//    }
//
//    string myText;
//
//    // Write number of entries
//    int fileSize = 0;
//    outputStream.write((char*)&fileSize, sizeof(fileSize));
//
//    while (getline(inputStream, myText))
//    {
//        // read file, line by line and parse it
//        std::string cubeInts = myText.substr(0, myText.find('\t'));
//        std::string int1Str = cubeInts.substr(0, myText.find(' '));
//        std::string int2Str = cubeInts.substr(int1Str.length() + 1, cubeInts.length() - int1Str.length() - 1);
//        std::string turns = myText.substr(cubeInts.length() + 1, myText.length() - cubeInts.length() - 1);
//
//        // Write entry length
//        llu tempInt;
//        int entrySize = 2 * sizeof(tempInt) + turns.length();
//        outputStream.write((char*)&entrySize, sizeof(entrySize));
//
//        // Write first integer
//        tempInt = std::stoull(int1Str);
//        outputStream.write((char*)&tempInt, sizeof(tempInt));
//
//        // Write second integer
//        tempInt = std::stoull(int2Str);
//        outputStream.write((char*)&tempInt, sizeof(tempInt));
//
//        // Write string
//        outputStream.write(turns.c_str(), turns.length());
//
//        ++fileSize;
//    }
//
//    outputStream.seekp(0);
//    outputStream.write((char*)&fileSize, sizeof(fileSize));
//
//    inputStream.close();
//    outputStream.close();
//}


int convertTextToBin(const char* inputFile, const char* outputFile)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ifstream inputStream(inputFile);
    if (!inputStream) {
        cout << "Cannot open input file!" << endl;
        return 1;
    }

    ofstream outputStream(outputFile, ios::out | ios::binary);
    if (!outputStream) {
        cout << "Cannot open output file!" << endl;
        return 1;
    }

    string myText;

    // Write number of entries
    int fileSize = 0;
    outputStream.write((char*)&fileSize, sizeof(fileSize));

    while (getline(inputStream, myText))
    {
        // read file, line by line and parse it
        std::string cubeInts = myText.substr(0, myText.find('\t'));
        std::string int1Str = cubeInts.substr(0, myText.find(' '));
        std::string int2Str = cubeInts.substr(int1Str.length() + 1, cubeInts.length() - int1Str.length() - 1);
        std::string turns = myText.substr(cubeInts.length() + 1, myText.length() - cubeInts.length() - 1);

        // Convert string to array of ints
        int startS = 0;
        unsigned char moves[10];
        unsigned char lenMoves = 0;
        memset(moves, 0, sizeof(moves));
        for (int i = 0;i < turns.size();i++) {
            if (turns[i] == ' ') {

                string ttemp = turns.substr(startS, (i)-startS);
                startS = i + 1;
                moves[lenMoves] = convertStringToInt[ttemp];
                lenMoves++;
            }
        }
        string ttemp = turns.substr(startS, turns.size() - startS); // last move
        moves[lenMoves++] = convertStringToInt[ttemp];

        llu tempInt;

        // Write first integer
        tempInt = std::stoull(int1Str);
        outputStream.write((const char*)&tempInt, sizeof(tempInt));

        // Write second integer
        tempInt = std::stoull(int2Str);
        outputStream.write((const char*)&tempInt, sizeof(tempInt));

        // Write number of moves
        outputStream.write((const char*)&lenMoves, sizeof(unsigned char));

        // Write moves
        outputStream.write((const char*)moves, lenMoves * sizeof(unsigned char));

        ++fileSize;
    }

    outputStream.seekp(0);
    outputStream.write((char*)&fileSize, sizeof(fileSize));

    inputStream.close();
    outputStream.close();
    return 0;
}

int load(const char* inputFile, map<cube, vector<unsigned char>>& map)
{
    ifstream inputStream(inputFile, ios::in | ios::binary);
    if (!inputStream) {
        cout << "Cannot open input file!" << endl;
        return 1;
    }

    // Read number of entries
    int fileSize;
    inputStream.read((char*)&fileSize, sizeof(fileSize));

    cube cube;
    // int buf[10];
    unsigned char moves[10];

    while (fileSize--)
    {
        // Read cube
        inputStream.read((char *)&cube, sizeof(cube));

        // Read number of moves
        unsigned char lenMoves;
        inputStream.read((char *)&lenMoves, sizeof(unsigned char));

        // Read text
        inputStream.read((char*)moves, lenMoves * sizeof(unsigned char));
        // int turns(buf, entrySize);
        // memset(map[cube],*turns,sizeof(turns));
        vector<unsigned char> turns(moves, moves + lenMoves);

        map.insert({ cube, turns });
    }

    inputStream.close();
    return 0;
}


int main()
{
    // Conversion
    //int ans = convertTextToBin("altFromDRPrune.tsv", "altFromDRPrune.bin");

    // Read converted file
    auto start = high_resolution_clock::now();

    map<cube, vector<unsigned char>> map1;
    int ans = load("altFromDRPrune.bin", map1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Size: " << map1.size() << " read in " << duration.count() << "ms" << endl;
    //cube ccube = make_pair(247132686368ull, 407901468851537952ull);
    //int* moves = map1[ccube];
    //for (int i = 0;i < sizeof(moves) / sizeof(int);i++) {
    //    cout << moves[i] << " ";
    //}
    //cout << endl;


    // Read converted file
    //map<cube, string> map1;
    //load("altFromDRPrune.bin", map1);
    //cout << "Size: " << map1.size() << endl;

    // Conversion
    //convertTextToBin("altFromDRPrune.tsv", "altFromDRPrune.bin");


    // Demo
    //map<cube, string> map1;
    //map1.insert({ make_pair(247132686368ull, 407901468851537952ull), "" });
    //map1.insert({ make_pair(242833528868ull, 398894268556617760ull), "R2" });
    //map1.insert({ make_pair(179455494176ull, 336936789371619360ull), "U" });
    //     
    //save("cppFromDRPrune.bin", map1);

    //map<cube, string> map2;
    //load("cppFromDRPrune.bin", map2);


    //auto iter1 = map1.begin();
    //while (iter1 != map1.end())
    //{
    //    cout << iter1->first.first << ' ' << iter1->first.second << '\t' << iter1->second << endl;
    //    ++iter1;
    //}
    //cout << endl;
    //auto iter2 = map2.begin();
    //while (iter2 != map2.end())
    //{
    //    cout << iter2->first.first << ' ' << iter2->first.second << '\t' << iter2->second << endl;
    //    ++iter2;
    //}

    return 0;
}

//int main2()
//{
//
//    //std::cout << "Hello World!\n";
//
//    ifstream inputfile;
//
//    inputfile.open("altFromDRPrune.tsv");
//    string line = "";
//    map<cube, char*> d;
//    while (getline(inputfile, line)) {
//
//        cube c;
//        string tempstring1;
//
//        stringstream inputString(line);
//
//        getline(inputString, tempstring1, ' ');
//        c.first = atoll(tempstring1.c_str());
//        getline(inputString, tempstring1, '\t');
//        c.second = atoll(tempstring1.c_str());
//        getline(inputString, tempstring1, '\n');
//
//        d[c] = new char[27];
//        copy(tempstring1.begin(), tempstring1.end(), d[c]);
//        line = "";
//    }
//
//    inputfile.close();
//    cube test;
//    test.first = 242833528868;
//    test.second = 398894268556617760;
//    cout << d[test] << endl;
//    cube test2;
//    test2.first = 208477978663;
//    test2.second = 407894871781777440;
//    cout << d[test2] << endl;
//    save(d);
//
//    // Load file. All above is saving
//    map<cube, char*> e;
//    load(e);
//    cout << e.size() << endl;
//
//
//    return 0;
//}