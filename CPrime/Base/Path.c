#include "Path.h"


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "StrBuilder.h"
#include <Shlwapi.h>
#include <ctype.h>

//#define _MAX_DRIVE 255
//#define _MAX_DIR 255
//#define _MAX_FNAME 255
//#define _MAX_EXT 255
//#define MAX_PATH 260

/*
 char drive[_MAX_DRIVE];
 char dir[_MAX_DIR];
 char fname[_MAX_FNAME];
 char ext[_MAX_EXT];
 SplitPath(buffer, drive, dir, fname, ext); // C4996
*/
void SplitPath(const char* path, char* drv, char* dir, char* name, char* ext)
{
	const char* end; /* end of processed string */
	const char* p;      /* search pointer */
	const char* s;      /* copy pointer */

						/* extract drive name */
	if (path[0] && path[1] == ':') {
		if (drv) {
			*drv++ = *path++;
			*drv++ = *path++;
			*drv = '\0';
		}
	}
	else if (drv)
		*drv = '\0';

	/* search for end of string or stream separator */
	for (end = path; *end && *end != ':'; )
		end++;

	/* search for begin of file extension */
	for (p = end; p>path && *--p != '\\' && *p != '/'; )
		if (*p == '.') {
			end = p;
			break;
		}

	if (ext)
		for (s = end; (*ext = *s++); )
			ext++;

	/* search for end of directory name */
	for (p = end; p>path; )
		if (*--p == '\\' || *p == '/') {
			p++;
			break;
		}

	if (name) {
		for (s = p; s<end; )
			*name++ = *s++;

		*name = '\0';
	}

	if (dir) {
		for (s = path; s<p; )
			*dir++ = *s++;

		*dir = '\0';
	}
}


/*
char drive[_MAX_DRIVE];
char dir[_MAX_DIR];
char fname[_MAX_FNAME];
char ext[_MAX_EXT];
SplitPath(buffer, drive, dir, fname, ext); // C4996
*/
void MakePath(char* path, char* drv, char* dir, char* name, char* ext)
{
  if (drv && drv[0] != '\0')
  {
    while (*drv)
    {
      *path = *drv;
      path++;
      drv++;
    }
    //*path = ':';
    //path++;
   // *path = '\\';
   // path++;
  }

  if (dir && dir[0] != '\0')
  {
    while (*dir)
    {
      *path = *dir;
      path++;
      dir++;
    }
  //  *path = '\\';
   // path++;
  }

  while (*name)
  {
    *path = *name;
    path++;
    name++;
  }
  
  //*path = '.';
  //path++;

  while (*ext)
  {
    *path = *ext;
    path++;
    ext++;
  }
  *path = '\0';
}

bool IsInPath(const char * filePath, const char* path)
{
	while (*path)
	{
		if (toupper(*path) != toupper(*filePath))
		{
			return false;
		}

		if (*path == '\0')
			break;

		path++;
		filePath++;
	}

	return true;
}

bool IsFullPath(const char*  path)
{
	if (path != NULL)
	{
		if ((path[0] >= 'a' && path[0] <= 'z') ||
			(path[0] >= 'A' && path[0] <= 'Z'))
		{
			if (path[1] == ':')
			{
				if (path[2] == '\\')
				{
					//Ve se tem pontos ..\ 
					const char* p = &path[2];

					while (*p)
					{
						if (*p == '.' && *(p - 1) == '\\')
						{
							return false;
						}

						p++;
					}

					return true;
				}
			}
		}
	}

	return false;
}

bool FileExists(const char* fullPath)
{
	bool bFileExists = false;
	FILE* fp = fopen(fullPath, "rb");

	if (fp)
	{
		bFileExists = true;
		fclose(fp);
	}

	return bFileExists;
}


void GetFullDir(const char* fileName, String* out)
{
	char buffer[MAX_PATH];
	/*DWORD r =*/ GetFullPathNameA(
		fileName,
		sizeof(buffer),
		buffer,
		NULL
	);
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	SplitPath(buffer, drive, dir, fname, ext); // C4996
	StrBuilder s;// = STRBUILDER_INIT;
	StrBuilder_Init(&s, 100);
	StrBuilder_Append(&s, drive);
	StrBuilder_Append(&s, dir);
	String_Attach(out, StrBuilder_Release(&s));
	StrBuilder_Destroy(&s);
}


void GetFullPath(const char* fileName, String* out)
{
	char buffer[MAX_PATH];
	/*DWORD r =*/ GetFullPathNameA(
		fileName,
		sizeof(buffer),
		buffer,
		NULL
	);
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	SplitPath(buffer, drive, dir, fname, ext); // C4996
	StrBuilder s = STRBUILDER_INIT;
	// StrBuilder_Init(&s, 100);
	StrBuilder_Append(&s, drive);
	StrBuilder_Append(&s, dir);
	StrBuilder_Append(&s, fname);
	StrBuilder_Append(&s, ext);
	String_Attach(out, StrBuilder_Release(&s));
	StrBuilder_Destroy(&s);
}
