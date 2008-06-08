////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2008 by Alexander Galanin                               //
//  gaa.nnov@mail.ru                                                      //
//                                                                        //
//  This program is free software; you can redistribute it and/or modify  //
//  it under the terms of the GNU Library General Public License as       //
//  published by the Free Software Foundation; either version 3 of the    //
//  License, or (at your option) any later version.                       //
//                                                                        //
//  This program is distributed in the hope that it will be useful,       //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//  GNU General Public License for more details.                          //
//                                                                        //
//  You should have received a copy of the GNU Library General Public     //
//  License along with this program; if not, write to the                 //
//  Free Software Foundation, Inc.,                                       //
//  51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA               //
////////////////////////////////////////////////////////////////////////////

#ifndef FILE_NODE_H
#define FILE_NODE_H

#include "types.h"
#include "bigBuffer.h"

class FileNode {
private:
    BigBuffer *buffer;
    FuseZipData *data;
    bool saving;
    int open_count;

    void parse_name(char *fname);
    void attach();
public:
    FileNode(FuseZipData *_data, const char *fname, int id = -2);
    ~FileNode();

    void detach();
    void rename(char *fname);
    void rename_wo_reparenting(char *new_name);

    int open();
    int read(char *buf, size_t size, off_t offset) const;
    int write(const char *buf, size_t size, off_t offset);
    int close();
    int save();
    int truncate(off_t offset);

    char *name, *full_name;
    bool is_dir;
    int id;
    nodelist_t childs;
    FileNode *parent;

    bool changed;
    struct zip_stat stat;
};
#endif

