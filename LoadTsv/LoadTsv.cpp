// LoadTsv.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <cstring>

using namespace std;
typedef long long int lli;
typedef unsigned long long int llu;

typedef pair<llu, llu> cube;

int save(const char* outputFile, map<cube, string>& map)
{
    ofstream outputStream(outputFile, ios::out | ios::binary);

    if (!outputStream) {
        cout << "Cannot open output file!" << endl;
        return 1;
    }

    auto iter = map.begin();
    while (iter != map.end())
    {
        // Write entry length
        int entrySize = sizeof(iter->first) + iter->second.length();
        outputStream.write((char*)&entrySize, sizeof(entrySize));

        // Write integers
        outputStream.write((char*)&(iter->first), sizeof(iter->first));

        // Write text
        outputStream.write(iter->second.c_str(), iter->second.length());
        ++iter;
    }
    outputStream.close();
}
//
//void load(map<cube, char*>& map) {
//    FILE* f = fopen("cppFromDRPrune.bin", "rb");
//    if (f == NULL) {
//        cout << "error reading file" << endl;
//    }
//    cube key;
//
//    while (!feof(f)) {
//        size_t elements_read1 = fread(&key, sizeof(key), 1, f);
//        if (elements_read1 == 0) {
//            cout << "error" << endl;
//        }
//        map[key] = new char[27];
//        size_t elements_read2 = fread(&map[key], sizeof(char) * 27, 1, f);
//        if (elements_read2 == 0) {
//            cout << "error" << endl;
//        }
//        cout << key.first << endl;
//        cout << key.second << endl;
//        // cout << sizeof(val) << endl;
//        cout << map[key] << endl;
//        // map[key] = val;
//    }
//    fclose(f);
//}

int convertTextToBin(const char* inputFile, const char* outputFile)
{
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

    while (getline(inputStream, myText)) 
    {
        // read file, line by line and parse it
        std::string cubeInts = myText.substr(0, myText.find('\t'));
        std::string int1Str = cubeInts.substr(0, myText.find(' '));
        std::string int2Str = cubeInts.substr(int1Str.length() + 1, cubeInts.length() - int1Str.length() - 1);
        std::string turns = myText.substr(cubeInts.length() + 1, myText.length() - cubeInts.length() - 1);

        // Write entry length
        llu tempInt;
        int entrySize = 2 * sizeof(tempInt) + turns.length();
        outputStream.write((char*)&entrySize, sizeof(entrySize));

        // Write first integer
        tempInt = std::stoull(int1Str);
        outputStream.write((char*)&tempInt, sizeof(tempInt));
        
        // Write second integer
        tempInt = std::stoull(int2Str);        
        outputStream.write((char*)&tempInt, sizeof(tempInt));

        // Write string
        outputStream.write(turns.c_str(), turns.length());
    }

    outputStream.close();
}

int main()
{
    //convertTextToBin("altFromDRPrune.tsv", "altFromDRPrune.bin");

    map<cube, string> map;
    //map.insert({ make_pair(247132686368ull, 407901468851537952ull), "" });
    //map.insert({ make_pair(242833528868ull, 398894268556617760ull), "R2" });
    map.insert({ make_pair(179455494176ull, 336936789371619360ull), "U" });
         
    save("cppFromDRPrune.bin", map);
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