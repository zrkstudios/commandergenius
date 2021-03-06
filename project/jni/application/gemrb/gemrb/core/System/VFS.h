/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2003 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 */

/**
 * @file VFS.h
 * Compatibility layer for file and dir access functions on Un*x and MS Win
 * @author The GemRB Project
 */

#ifndef VFS_H
#define VFS_H

#ifndef _MAX_PATH
#ifdef WIN32
#define _MAX_PATH 260
#else
#define _MAX_PATH FILENAME_MAX
#endif
#endif

#include "exports.h"
#include "globals.h"

#include <string>
#include <sys/stat.h>

#ifdef WIN32
#include <direct.h>
#include <io.h>
#include <windows.h>
#endif

#ifndef R_OK
#define R_OK 04
#endif

#ifdef WIN32

typedef struct _FILE {
	HANDLE hFile;
} _FILE;

GEM_EXPORT _FILE* _fopen(const char* filename, const char* mode);
GEM_EXPORT size_t _fread(void* ptr, size_t size, size_t n, _FILE* stream);
GEM_EXPORT size_t _fwrite(const void* ptr, size_t size, size_t n,
	_FILE* stream);
GEM_EXPORT size_t _fseek(_FILE* stream, long offset, int whence);
GEM_EXPORT int _fgetc(_FILE* stream);
GEM_EXPORT long int _ftell(_FILE* stream);
GEM_EXPORT int _feof(_FILE* stream);
GEM_EXPORT int _fclose(_FILE* stream);
#define mkdir(path, rights)  _mkdir(path)
#define ResolveFilePath(p)

#else  // ! WIN32

#define _FILE FILE
#define _fopen fopen
#define _fread fread
#define _fwrite fwrite
#define _fseek fseek
#define _fgetc fgetc
#define _ftell ftell
#define _feof feof
#define _fclose fclose

/** Handle ~ -> $HOME mapping and do initial case-sensitity check */
GEM_EXPORT void ResolveFilePath(char* FilePath);
GEM_EXPORT void ResolveFilePath(std::string& FilePath);

#endif  // ! WIN32

#ifdef WIN32
const char PathDelimiter = '\\';
const char PathListSeparator = ';';
#else
const char PathDelimiter = '/';
const char PathListSeparator = ':';
#endif
const char SPathDelimiter[] = { PathDelimiter, '\0' };
const char SPathListSeparator[] = { PathListSeparator, '\0' };

/**
 * Finds a file matching a glob.
 *
 * @param[out] target name of matching file
 * @param[in] Dir directory to look in
 * @param[in] glob pattern to match
 * @return true if match is found
 */
GEM_EXPORT bool FileGlob(char *target, const char* Dir, const char* glob);
GEM_EXPORT bool dir_exists(const char* path);
GEM_EXPORT bool file_exists(const char* path);

/**
 * Joins NULL-terminated list of directories and copies it to 'target'.
 *
 * @param[out] target Joined path.
 * @param[in] base Properly cased path to join to.
 * @param[in] ... NULL terminated list of paths to join.
 *
 * This does a case-sensitive look up for all path components after the first and
 * properly handles the case when paramater contain slashes.
 *
 * NOTE: This no longer handles target==base.
 *
 * Example:
 * char filepath[_MAX_PATH];
 * PathJoin( filepath, core->GUIScriptsPath, core->GameType, 'GUIDefines.py', NULL );
 */
GEM_EXPORT bool PathJoin (char* target, const char* base, ...);
GEM_EXPORT bool PathJoinExt (char* target, const char* dir, const char* file, const char* ext = NULL);
GEM_EXPORT void FixPath (char *path, bool needslash);

GEM_EXPORT void ExtractFileFromPath(char *file, const char *full_path);

class GEM_EXPORT DirectoryIterator {
public:
	/**
	 * @param[in] path Path to directory to search.
	 *
	 * WARNING: the lifetime of path must be longer than the lifetime
	 * of DirectoryIterator.
	 */
	DirectoryIterator(const char *path);
	~DirectoryIterator();
	bool IsDirectory();
	/**
	 * Returns name of current entry.
	 *
	 * The returned string is only valid until the iterator is advanced.
	 * FIXME: This should return a const char*
	 */
	char *GetName();
	void GetFullPath(char *);
	DirectoryIterator& operator++();
#include "operatorbool.h"
	OPERATOR_BOOL(DirectoryIterator,void,Entry)
	bool operator !() { return !Entry; }
	void Rewind();
private:
	void* Directory;
	void* Entry;
	const char *Path;
};

#endif  // !VFS_H
