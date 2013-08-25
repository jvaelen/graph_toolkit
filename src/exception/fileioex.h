/*
 Author: Balazs Nemeth
 Description: this exception class is used when fileIO fails or there is some problem regarding fileIO
     */
#ifndef FILEIOEX_H
#define FILEIOEX_H

#include <string>
#include "baseex.h"

using namespace std;

class FileIOEx : public BaseEx
{
public:
    FileIOEx(const string& path, string  extraInfo = "", int priority = 5);
    void setPath(const string& path);
    string getPath() const {return _path;}
    // this is the function that is reimplemented when deriving from BaseEx
    string getMessage() const;
private:
    string _path; // this is the path of the file that gave the IO exception

};

#endif // FILEIOEX_H
