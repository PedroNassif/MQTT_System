#include <Arduino.h>
#include <LittleFS.h>
#include "FS.h"

#ifndef _LTTLEFS_FUNCTIONS_H
#define _LITTLEFS_FUNCTIONS_H

void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
void createDir(fs::FS &fs, const char * path);
void removeDir(fs::FS &fs, const char * path);
String readFile(fs::FS &fs, const char * path);
void writeFile(fs::FS &fs, const char * path, const char * message);
void appendFile(fs::FS &fs, const char * path, const char * message);
void renameFile(fs::FS &fs, const char * path1, const char * path2);
void deleteFile(fs::FS &fs, const char * path);
void writeFile2(fs::FS &fs, const char * path, const char * message);
void deleteFile2(fs::FS &fs, const char * path);
void testFileIO(fs::FS &fs, const char * path);
void LittleFSbegins();

#endif