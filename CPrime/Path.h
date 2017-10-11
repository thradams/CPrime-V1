#pragma once
#include "StringEx.h"
#include <stdbool.h>


#define CPRIME_MAX_DRIVE 255
#define CPRIME_MAX_DIR 255
#define CPRIME_MAX_FNAME 255
#define CPRIME_MAX_EXT 255
#define CPRIME_MAX_PATH 260

void GetFullPath(const char* fileName, String* out);
void GetFullDir(const char* fileName, String* out);
bool IsFullPath(const char * path);
bool IsInPath(const char * filePath, const char* path);
bool FileExists(const char* fullPath);
void SplitPath(const char* path, char* drv, char* dir, char* name, char* ext);
void MakePath(char* path, char* drv, char* dir, char* name, char* ext);
