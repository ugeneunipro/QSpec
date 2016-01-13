/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2016 UniPro <ugene@unipro.ru>
 * http://ugene.unipro.ru
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#ifndef _HI_GT_FILE_H_
#define _HI_GT_FILE_H_

#include "GTGlobals.h"
#include <QFile>

namespace HI {

class HI_EXPORT PermissionsSetter {
    // If UGENE crash in the test, permissions won't be restored.
public:
    PermissionsSetter();
    ~PermissionsSetter();


    static void setReadWrite(GUITestOpStatus &os, const QString& path);
    void setReadOnly(GUITestOpStatus &os, const QString& path);

    void setReadOnlyFlag(GUITestOpStatus &os, const QString& path);
private:
    bool setPermissions(const QString& path, QFile::Permissions perm, bool recursive = true);
    bool setRecursive(const QString& path, QFile::Permissions perm);
    bool setOnce(const QString& path, QFile::Permissions perm, bool savePreviousState = true);

    QMap<QString, QFile::Permissions> previousState;
};

class HI_EXPORT GTFile {
public:
    static bool equals(GUITestOpStatus &os, const QString&, const QString&);

    static qint64 getSize(GUITestOpStatus &os, const QString&);

    // backup file to the file with backupPostfix. fail the given file can't be opened
    static void backup(GUITestOpStatus &os, const QString&);

    // backup directory to the file with backupPostfix
    static void backupDir(GUITestOpStatus &os, const QString&);

    // copy file removing target file if exist
    static void copy(GUITestOpStatus &os, const QString& from, const QString& to);

    // copy directory entries removing target file if exist
    static void copyDir(GUITestOpStatus &os, const QString& dirToCopy, const QString& dirToPaste);

    // copy file removing target file if exist
    static void removeDir(QString dirName);

    // restores file and deletes backup. fail if there is no backup or can't write to the given file
    static void restore(GUITestOpStatus &os, const QString&);

    // restores file and deletes backup. fail if there is no backup or can't write to the given file
    static void restoreDir(GUITestOpStatus &os, const QString&);

    // checks if file exists
    static bool check(GUITestOpStatus &os, const QString&);

    // creates a new empty file, rewrite the file if it already exists
    static void create(GUITestOpStatus &os, const QString &filePath);

    static QByteArray readAll(GUITestOpStatus &os, const QString &filePath);

    static const QString backupPostfix;
};

} //namespace

#endif
