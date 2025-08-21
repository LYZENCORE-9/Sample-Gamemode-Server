/*
 *			FileEngine INI Library
 *			https://github.com/LYZENCORE-9/FileEngine
 *
 *	Creator     : LYZENCORE-9
 *  Maintainer  : LYZENCORE-9
 *	Date	    : 30 7 2025 (31 Decembre 2024 the date of idea and prototype)
 *	Update      : 1 8 2025
 *
 *	Under MIT License
 *
 *	Feel free to ask me in discord (distroxyde/lyzencore9_official)
 *	or follow me in github (https://github.com/LYZENCORE-9)
 ****************************************************
 */
#include <cstdint>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#if !defined(_FILEENGINE_INI_LIB_H_) || !defined(_FILEENGINE_INI_H_)
#define _FILEENGINE_INI_LIB_H_
#define _FILEENGINE_INI_H_



namespace FileEngine::INI {

enum INIReturnedValues
{
    E_INI_SUCCESS = 0,
    E_INI_FILE_NOT_FOUND = -1,
    E_INI_KEY_NOT_FOUND = -2,
    E_INI_KEY_OR_VALUE_PASSED_BUFFER_SIZE = -3,
    E_INI_WRITEBOOL_WRONG_VALUE = -4,
    E_INI_SECTION_NOT_FOUND = -5,
    E_INI_SECTION_PASSED_BUFFER_SIZE = -6,
    E_INI_READBOOL_WRONG_VALUE = -4,
    E_INI_SECTION_CLASS_NOT_FOUND = -7
};


class Settings
{
public:
    static const int MAX_FILE_LINES = 512;
    static const int MAX_BUFFER_SIZE = 1024;
    static const int MAX_FILENAME_SIZE = 128;
    static const int MAX_SECTIONS = 512;
    static const int MAX_FILE_HANDLES = 2;

    static const int MAX_SECTION_SIZE = 128;
    static const int MAX_KEY_SIZE = 256;
    static const int MAX_VALUE_SIZE = 256;
    static const int MAX_COMMENT_SIZE = 128; 

};


class File {
public:
    char m_filename[Settings::MAX_FILENAME_SIZE] = {0};
    char m_fileextension[Settings::MAX_FILENAME_SIZE] = {0};
    char m_sectionname[Settings::MAX_SECTION_SIZE] = {0};
    char m_sectionclass[Settings::MAX_SECTION_SIZE] = {0};

    File() { }
    File(char *filename, char *extension);


    bool Create();
    bool Exists();
    bool Delete();
    bool Rename(char* new_name);
    bool Copy(char* newfilename);
    bool Move(char *path);

    void SetCurrentSection(char *section);
    void SetCurrentClass(char *class_buffer);
    ~File() { }
};

namespace Writter
{

class Simple_Structure 
{
private:
    int PrivateWrite(char *key, char* string);
public:
    File file;
    Simple_Structure(File *file_class);
    // Writes an short (primitive signed types) to the file (does not support Sections)
    int WriteShort(char *key, short *value);
    // Writes an int (primitive signed types) to the file (does not support Sections)
    int WriteInt(char *key, int *value);
    // Writes an long (primitive signed types) to the file (does not support Sections)
    int WriteLong(char *key, long *value);
   // Writes an long long (primitive signed types) to the file (does not support Sections)
    int WriteLongLong(char *key, long long *value);
    // Writes an float (primitive signed types) to the file (does not support Sections)
    int WriteFloat(char *key, float *value);
    // Writes an double (primitive signed types) to the file (does not support Sections)
    int WriteDouble(char *key, double *value);
    // Writes an bool (primitive signed types) to the file (does not support Sections)
    int WriteBool(char *key, bool *value);

    // signed writters now (they are same like above but we need handle types)
    // only decimals

    // Writes an int8_t (primitive signed types) to the file (does not support Sections)
    int WriteInt8(char* key, int8_t *value);
    // Writes an int16_t (primitive signed types) to the file (does not support Sections)
    int WriteInt16(char *key, int16_t *value);
    // Writes an int32_t (primitive signed types) to the file (does not support Sections)
    int WriteInt32(char *key, int32_t *value);
    // Writes an int64_t (primitive signed types) to the file (does not support Sections)
    int WriteInt64(char *key, int64_t *value); // if you built the library on 32bit mod , int64_t will be 32bit not 64bit i guess

    // unsigned writters now

    // Writes an uint8_t (primitive unsigned types) to the file (does not support Sections)
    int WriteUint8(char *key, uint8_t *value);
    // Writes an uint16_t (primitive unsigned types) to the file (does not support Sections)
    int WriteUint16(char *key, uint16_t *value);
    // Writes an uint32_t (primitive unsigned types) to the file (does not support Sections)
    int WriteUint32(char *key, uint32_t *value);
    // Writes an uint64_t (primitive unsigned types) to the file (does not support Sections)
    int WriteUint64(char *key, uint64_t *value); 

    // Characters and Strings

    // Writes an char (primitive signed types) to the file (does not support Sections)
    int WriteChar(char *key, char value[1]);
    // Writes an char string (char* or char[]) (primitive signed types) to the file (does not support Sections)
    int WriteCString(char *key, char *value);
    // Writes an std::string (reference signed types) to the file (does not support Sections)
    int WriteString(char *key, std::string *value);

    ~Simple_Structure() {}
};

class Section_Structure
{
private:
    int PrivateWrite(char *key, char* string);
public:
    File file;

    Section_Structure(File* file_class);
    // Writes an short (primitive signed types) to the file (supports Sections)
    int WriteShort(char *key, short *value);
    // Writes an int (primitive signed types) to the file (supports Sections)
    int WriteInt(char *key, int *value);
    // Writes an long (primitive signed types) to the file (supports Sections)
    int WriteLong(char *key, long *value);
    // Writes an long long (primitive signed types) to the file (supports Sections);
    int WriteLongLong(char *key, long long *value);
    // Writes an float (primitive signed types) to the file (supports Sections)
    int WriteFloat(char *key, float *value);
    // Writes an double (primitive signed types) to the file (supports Sections)
    int WriteDouble(char *key, double *value);
    // Writes an bool (primitive signed types) to the file (supports Sections)
    int WriteBool(char *key, bool *value);

    // signed writters now (they are same like above but we need handle types)
    // only decimals

    // Writes an int8_t (primitive signed types) to the file (supports Sections)
    int WriteInt8(char* key, int8_t *value);
    // Writes an int16_t (primitive signed types) to the file (supports Sections)
    int WriteInt16(char *key, int16_t *value);
    // Writes an int32_t (primitive signed types) to the file (supports Sections)
    int WriteInt32(char *key, int32_t *value);
    // Writes an int64_t (primitive signed types) to the file (supports Sections)
    int WriteInt64(char *key, int64_t *value); // if you built the library on 32bit mod , int64_t will be 32bit not 64bit i guess

    // unsigned writters now

    // Writes an uint8_t (primitive unsigned types) to the file (supports Sections)
    int WriteUint8(char *key, uint8_t *value);
    // Writes an uint16_t (primitive unsigned types) to the file (supports Sections)
    int WriteUint16(char *key, uint16_t *value);
    // Writes an uint32_t (primitive unsigned types) to the file (supports Sections)
    int WriteUint32(char *key, uint32_t *value);
    // Writes an uint64_t (primitive unsigned types) to the file (supports Sections)
    int WriteUint64(char *key, uint64_t *value); 

    // Characters and Strings

    // Writes an char (primitive signed types) to the file (supports Sections)
    int WriteChar(char *key, char value[1]);
    // Writes an char string (char* or char[]) (primitive signed types) to the file (supports Sections)
    int WriteCString(char *key, char *value);
    // Writes an std::string (reference types) to the file (supports Sections)
    int WriteString(char *key, std::string *value);
    ~Section_Structure() { }
};

class SectionClasses_Structure
{
private:
     int PrivateWrite(char *key, char *string);
public:
    File file;
    SectionClasses_Structure(File* file_class);
    // Writes an short (primitive signed types) to the file (supports Sections)
    int WriteShort(char *key, short *value);
    // Writes an int (primitive signed types) to the file (supports Sections)
    int WriteInt(char *key, int *value);
    // Writes an long (primitive signed types) to the file (supports Sections)
    int WriteLong(char *key, long *value);
    // Writes an long long (primitive signed types) to the file (supports Sections);
    int WriteLongLong(char *key, long long *value);
    // Writes an float (primitive signed types) to the file (supports Sections)
    int WriteFloat(char *key, float *value);
    // Writes an double (primitive signed types) to the file (supports Sections)
    int WriteDouble(char *key, double *value);
    // Writes an bool (primitive signed types) to the file (supports Sections)
    int WriteBool(char *key, bool *value);

    // signed writters now (they are same like above but we need handle types)
    // only decimals

    // Writes an int8_t (primitive signed types) to the file (supports Sections)
    int WriteInt8(char* key, int8_t *value);
    // Writes an int16_t (primitive signed types) to the file (supports Sections)
    int WriteInt16(char *key, int16_t *value);
    // Writes an int32_t (primitive signed types) to the file (supports Sections)
    int WriteInt32(char *key, int32_t *value);
    // Writes an int64_t (primitive signed types) to the file (supports Sections)
    int WriteInt64(char *key, int64_t *value); // if you built the library on 32bit mod , int64_t will be 32bit not 64bit i guess

    // unsigned writters now

    // Writes an uint8_t (primitive unsigned types) to the file (supports Sections)
    int WriteUint8(char *key, uint8_t *value);
    // Writes an uint16_t (primitive unsigned types) to the file (supports Sections)
    int WriteUint16(char *key, uint16_t *value);
    // Writes an uint32_t (primitive unsigned types) to the file (supports Sections)
    int WriteUint32(char *key, uint32_t *value);
    // Writes an uint64_t (primitive unsigned types) to the file (supports Sections)
    int WriteUint64(char *key, uint64_t *value); 

    // Characters and Strings

    // Writes an char (primitive signed types) to the file (supports Sections)
    int WriteChar(char *key, char value[1]);
    // Writes an char string (char* or char[]) (primitive signed types) to the file (supports Sections)
    int WriteCString(char *key, char *value);
    // Writes an std::string (reference types) to the file (supports Sections)
    int WriteString(char *key, std::string *value);
    ~SectionClasses_Structure() { }
};

}

namespace Reader
{
class Simple_Structure {
private:
    int PrivateRead(char *key, char *value);
public:
    File file;
    Simple_Structure(File *file_class);
    int test_PrivateRead(char *key, char *value);
    // Reads an short (primitive signed types) from the file
    int ReadShort(char *key, short *value);
    // Reads an int (primitive signed types) from the file
    int ReadInt(char *key, int *value);
    // Reads an long (primitive signed types) from the file
    int ReadLong(char *key, long *value);
    // Reads an long long (primitive signed types) from the file
    int ReadLongLong(char *key, long long *value);
    // Reads an float (primitive signed types) from the file
    int ReadFloat(char *key, float *value);
    // Reads an double (primitive signed types) from the file
    int ReadDouble(char *key, double *value);
    // Reads an bool (primitive signed types) from the file
    int ReadBool(char *key, bool *value);
    

    // signed writters now (they are same like above but we need handle types)
    // only decimals

    // Reads an int8_t (signed types) from the file
    int ReadInt8(char* key, int8_t *value);
    // Reads an int16_t (signed types) from the file
    int ReadInt16(char *key, int16_t *value);
    // Reads an int32_t (signed types) from the file
    int ReadInt32(char *key, int32_t *value);
    // Reads an int64_t (signed types) from the file
    int ReadInt64(char *key, int64_t *value); // if you built the library on 32bit mod , int64_t will be 32bit not 64bit i guess

    // unsigned writters now

    // Reads an uint8_t (unsigned types) from the file
    int ReadUint8(char *key, uint8_t *value);
    // Reads an uint16_t (unsigned types) from the file
    int ReadUint16(char *key, uint16_t *value);
    // Reads an uint32_t (unsigned types) from the file
    int ReadUint32(char *key, uint32_t *value);
    // Reads an uint64_t (unsigned types) from the file
    int ReadUint64(char *key, uint64_t *value); 

    // Characters and Ststatic rings

    // Reads an char (int8_t) (signed types) from the file
    int ReadChar(char *key, char value[1]);
    // Reads an char array or pointer (string) (signed types) from the file
    int ReadCString(char *key, char *value);
    // Reads an std::string (reference types) from the file
    int ReadString(char *key, std::string *value);

    ~Simple_Structure() { }
};

class Section_Structure {
private:
    int PrivateRead(char *key, char *value);
public:
    File file;
    Section_Structure(File *file_class);

    // Reads an short (primitive signed types) from the file
    int ReadShort(char *key, short *value);
    // Reads an int (primitive signed types) from the file
    int ReadInt(char *key, int *value);
    // Reads an long (primitive signed types) from the file
    int ReadLong(char *key, long *value);
    // Reads an long long (primitive signed types) from the file
    int ReadLongLong(char *key, long long *value);
    // Reads an float (primitive signed types) from the file
    int ReadFloat(char *key, float *value);
    // Reads an double (primitive signed types) from the file
    int ReadDouble(char *key, double *value);
    // Reads an bool (primitive signed types) from the file
    int ReadBool(char *key, bool *value);
    

    // signed writters now (they are same like above but we need handle types)
    // only decimals

    // Reads an int8_t (signed types) from the file
    int ReadInt8(char* key, int8_t *value);
    // Reads an int16_t (signed types) from the file
    int ReadInt16(char *key, int16_t *value);
    // Reads an int32_t (signed types) from the file
    int ReadInt32(char *key, int32_t *value);
    // Reads an int64_t (signed types) from the file
    int ReadInt64(char *key, int64_t *value); // if you built the library on 32bit mod , int64_t will be 32bit not 64bit i guess

    // unsigned writters now

    // Reads an uint8_t (unsigned types) from the file
    int ReadUint8(char *key, uint8_t *value);
    // Reads an uint16_t (unsigned types) from the file
    int ReadUint16(char *key, uint16_t *value);
    // Reads an uint32_t (unsigned types) from the file
    int ReadUint32(char *key, uint32_t *value);
    // Reads an uint64_t (unsigned types) from the file
    int ReadUint64(char *key, uint64_t *value); 

    // Characters and Ststatic rings

    // Reads an char (int8_t) (signed types) from the file
    int ReadChar(char *key, char value[1]);
    // Reads an char array or pointer (string) (signed types) from the file
    int ReadCString(char *key, char *value);
    // Reads an std::string (reference types) from the file
    int ReadString(char *key, std::string *value);

    ~Section_Structure() { }
};

class SectionClasses_Structure {
private:
    int PrivateRead(char *key, char *value);
public:
    File file;
    SectionClasses_Structure(File *file_class);
    // Reads an short (primitive signed types) from the file
    int ReadShort(char *key, short *value);
    // Reads an int (primitive signed types) from the file
    int ReadInt(char *key, int *value);
    // Reads an long (primitive signed types) from the file
    int ReadLong(char *key, long *value);
    // Reads an long long (primitive signed types) from the file
    int ReadLongLong(char *key, long long *value);
    // Reads an float (primitive signed types) from the file
    int ReadFloat(char *key, float *value);
    // Reads an double (primitive signed types) from the file
    int ReadDouble(char *key, double *value);
    // Reads an bool (primitive signed types) from the file
    int ReadBool(char *key, bool *value);
    

    // signed writters now (they are same like above but we need handle types)
    // only decimals

    // Reads an int8_t (signed types) from the file
    int ReadInt8(char* key, int8_t *value);
    // Reads an int16_t (signed types) from the file
    int ReadInt16(char *key, int16_t *value);
    // Reads an int32_t (signed types) from the file
    int ReadInt32(char *key, int32_t *value);
    // Reads an int64_t (signed types) from the file
    int ReadInt64(char *key, int64_t *value); // if you built the library on 32bit mod , int64_t will be 32bit not 64bit i guess

    // unsigned writters now

    // Reads an uint8_t (unsigned types) from the file
    int ReadUint8(char *key, uint8_t *value);
    // Reads an uint16_t (unsigned types) from the file
    int ReadUint16(char *key, uint16_t *value);
    // Reads an uint32_t (unsigned types) from the file
    int ReadUint32(char *key, uint32_t *value);
    // Reads an uint64_t (unsigned types) from the file
    int ReadUint64(char *key, uint64_t *value); 

    // Characters and Ststatic rings

    // Reads an char (int8_t) (signed types) from the file
    int ReadChar(char *key, char value[1]);
    // Reads an char array or pointer (string) (signed types) from the file
    int ReadCString(char *key, char *value);
    // Reads an std::string (reference types) from the file
    int ReadString(char *key, std::string *value);

    ~SectionClasses_Structure() { }
};
}


class Key {
public:
    Key() { }

    static int Create(char *filename, char *key);
    static int Remove(char *filename, char *key);
    static int Rename(char *filename, char *oldname_key, char *newname_key);
    static int Exists(char *filename, char *key);
    static int GenerateValue(char *filename, char *key);

    ~Key() { }
};

class Comment
{
public:
    //static int AddKeyComment(char *filename, char *key, char *comment); untill release of v 1.0.0-
    //static int EditKeyComment(char *filename, char *key, char *new_comment);
    //static int DeleteKeyComment(char *filename, char *key);

    static int AddComment(char *filename, char *comment);
    static int EditComment(char *filename, char *old_comment, char *new_comment);
    static int DeleteComment(char *filename, char* comment);
};

class Section
{
public:
    static int Create(char *filename, char* section_name);
    static int Delete(char *filename, char* section_name);
    static int Rename(char *filename, char* section_name);
};

}

#endif
