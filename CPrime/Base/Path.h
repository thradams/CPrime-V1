#pragma once
#include "StringEx.h"
#include <stdbool.h>

void GetFullPath(const char* fileName, String* out);
void GetFullDir(const char* fileName, String* out);
bool IsFullPath(const char * path);
bool IsInPath(const char * filePath, const char* path);
bool FileExists(const char* fullPath);
void SplitPath(const char* path, char* drv, char* dir, char* name, char* ext);
void MakePath(char* path, char* drv, char* dir, char* name, char* ext);
