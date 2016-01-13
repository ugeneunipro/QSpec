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

#include "system/GTFile.h"
#include <QDir>

#ifdef Q_OS_WIN

// Microsoft's example of how to change file system permissions is used below.
// See http://msdn.microsoft.com/en-us/library/windows/desktop/aa379283%28v=vs.85%29.aspx for details.

#include <Aclapi.h>

DWORD AddAceToObjectsSecurityDescriptor (
    LPTSTR pszObjName,          // name of object
    SE_OBJECT_TYPE ObjectType,  // type of object
    LPTSTR pszTrustee,          // trustee for new ACE
    TRUSTEE_FORM TrusteeForm,   // format of trustee structure
    DWORD dwAccessRights,       // access mask for new ACE
    ACCESS_MODE AccessMode,     // type of ACE
    DWORD dwInheritance         // inheritance flags for new ACE
    )
{
    DWORD dwRes = 0;
    PACL pOldDACL = NULL;
    PACL pNewDACL = NULL;
    PSECURITY_DESCRIPTOR pSD = NULL;
    EXPLICIT_ACCESS ea;

    if ( NULL == pszObjName ) {
        return ERROR_INVALID_PARAMETER;
    }

    // Get a pointer to the existing DACL.

    dwRes = GetNamedSecurityInfo( pszObjName, ObjectType, DACL_SECURITY_INFORMATION, NULL, NULL,
        &pOldDACL, NULL, &pSD );
    if ( ERROR_SUCCESS != dwRes ) {
        printf( "GetNamedSecurityInfo Error %u\n", dwRes );
        goto Cleanup;
    }

    // Initialize an EXPLICIT_ACCESS structure for the new ACE.

    ZeroMemory( &ea, sizeof( EXPLICIT_ACCESS ) );
    ea.grfAccessPermissions = dwAccessRights;
    ea.grfAccessMode = AccessMode;
    ea.grfInheritance= dwInheritance;
    ea.Trustee.TrusteeForm = TrusteeForm;
    ea.Trustee.ptstrName = pszTrustee;

    // Create a new ACL that merges the new ACE
    // into the existing DACL.

    dwRes = SetEntriesInAcl( 1, &ea, pOldDACL, &pNewDACL );
    if ( ERROR_SUCCESS != dwRes ) {
        printf( "SetEntriesInAcl Error %u\n", dwRes );
        goto Cleanup;
    }

    // Attach the new ACL as the object's DACL.

    dwRes = SetNamedSecurityInfo( pszObjName, ObjectType, DACL_SECURITY_INFORMATION, NULL, NULL,
        pNewDACL, NULL );
    if ( ERROR_SUCCESS != dwRes ) {
        printf( "SetNamedSecurityInfo Error %u\n", dwRes );
        goto Cleanup;
    }

Cleanup:

    if ( pSD != NULL ) {
        LocalFree( static_cast<HLOCAL>( pSD ) );
    }
    if (pNewDACL != NULL) {
        LocalFree( static_cast<HLOCAL>( pNewDACL ) );
    }

    return dwRes;
}

static void qt2WinPermissions( QFile::Permissions p, DWORD &allowedPermissions, DWORD &deniedPermissions )
{
    if ( 0 != ( p & ( QFile::ReadOwner | QFile::ReadUser | QFile::ReadOther | QFile::ReadGroup ) ) ) {
        allowedPermissions |= FILE_GENERIC_READ;
    } else {
        deniedPermissions |= FILE_GENERIC_READ;
    }
    if ( 0 != ( p & ( QFile::WriteOwner | QFile::WriteUser | QFile::WriteOther | QFile::WriteGroup ) ) ) {
        allowedPermissions |= FILE_GENERIC_WRITE;
    } else {
        deniedPermissions |= FILE_GENERIC_WRITE;
    }
    if ( 0 != ( p & ( QFile::ExeOwner | QFile::ExeUser | QFile::ExeOther | QFile::ExeGroup ) ) ) {
        allowedPermissions |= FILE_GENERIC_EXECUTE;
    } else {
        deniedPermissions |= FILE_GENERIC_EXECUTE;
    }
}

#endif

namespace HI {

#define GT_CLASS_NAME "PermissionsSetter"

PermissionsSetter::PermissionsSetter() {
}

PermissionsSetter::~PermissionsSetter() {
    foreach (const QString& path, previousState.keys()) {
        QFile file(path);
        QFile::Permissions p = file.permissions();

        p = previousState.value(path, p);
        setOnce( path, p, false );
    }
}

bool PermissionsSetter::setPermissions(const QString& path, QFile::Permissions perm, bool recursive) {
    if (recursive) {
        return setRecursive(path, perm);
    } else {
        return setOnce(path, perm);
    }
}

#define GT_METHOD_NAME "setReadWrite"
void PermissionsSetter::setReadWrite(GUITestOpStatus &os, const QString &path){
    QFile::Permissions p = QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner | QFile::ReadUser | QFile::WriteUser |
            QFile::ExeUser | QFile::ReadGroup | QFile::WriteGroup | QFile::ExeGroup | QFile::ReadOther | QFile::ExeOther;
    PermissionsSetter setter;
    bool set = setter.setPermissions(path, p);
    GT_CHECK(set, "read-only permission could not be set")
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "setReadOnly"
void PermissionsSetter::setReadOnly(GUITestOpStatus &os, const QString &path){
    QFile::Permissions p = QFile::ReadOwner | QFile::ExeOwner | QFile::ReadUser |
            QFile::ExeUser | QFile::ReadGroup | QFile::ExeGroup | QFile::ReadOther | QFile::ExeOther;
    bool set = setPermissions(path, p);
    GT_CHECK(set, "read-write permission could not be set")
}
#undef GT_METHOD_NAME

bool PermissionsSetter::setRecursive(const QString& path, QFile::Permissions perm) {
    QFileInfo fileInfo(path);
    if (!(fileInfo.exists())) {
        return false;
    }
    if (fileInfo.isSymLink()) {
        return false;
    }

    if (fileInfo.isDir()) {
        QDir dir(path);
        foreach (const QString& entryPath, dir.entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks)) {
            setOnce(path + "/" + entryPath, perm);
            bool res = setRecursive(path + "/" + entryPath, perm);
            if(!res){
                return res;
            }
        }
    }

    bool res = setOnce(path, perm);

    return res;
}

bool PermissionsSetter::setOnce( const QString &path, QFile::Permissions perm, bool savePreviousState ) {
    QFileInfo fileInfo( path );
    if (!(fileInfo.exists())) {
        return false;
    }
    if (fileInfo.isSymLink()) {
        return false;
    }

    QFile file( path );
    QFile::Permissions p = file.permissions( );
    if ( savePreviousState ) {
        previousState.insert( path, p );
    }
    p = perm;

#ifdef Q_OS_WIN
    if ( fileInfo.isRelative( ) && !fileInfo.makeAbsolute( ) ) {
        return false;
    }
    const QString windowsPath = QDir::toNativeSeparators( fileInfo.filePath( ) );

    const int pathLength = windowsPath.size( );
    QScopedArrayPointer<wchar_t> pathString( new wchar_t[pathLength + 1] );

    windowsPath.toWCharArray( pathString.data( ) );
    pathString[pathLength] = '\0';

    DWORD allowed = 0;
    DWORD denied = 0;
    qt2WinPermissions( p, allowed, denied );

    DWORD dwRes = AddAceToObjectsSecurityDescriptor( pathString.data( ), SE_FILE_OBJECT, L"CURRENT_USER",
        TRUSTEE_IS_NAME, allowed, GRANT_ACCESS, NO_INHERITANCE );
    if ( ERROR_SUCCESS == dwRes ) {
        dwRes = AddAceToObjectsSecurityDescriptor( pathString.data( ), SE_FILE_OBJECT, L"CURRENT_USER",
            TRUSTEE_IS_NAME, denied, DENY_ACCESS, NO_INHERITANCE );
    }

    return ERROR_SUCCESS == dwRes;
#else
    return file.setPermissions( p );
#endif
}

#define GT_METHOD_NAME "setReadOnlyFlag"
void PermissionsSetter::setReadOnlyFlag(GUITestOpStatus &os, const QString& path) {
#ifdef Q_OS_WIN
    GT_CHECK(SetFileAttributesW(reinterpret_cast<LPCWSTR>(path.utf16()), FILE_ATTRIBUTE_READONLY), 
        "Read flag could not be set");
#else
    setReadOnly(os, path);
#endif
}
#undef GT_METHOD_NAME
#undef GT_CLASS_NAME

#define GT_CLASS_NAME "GTFile"

const QString GTFile::backupPostfix = "_GT_backup";

#define GT_METHOD_NAME "equals"
bool GTFile::equals(GUITestOpStatus &os, const QString& path1, const QString& path2) {

    QFile f1(path1);
    QFile f2(path2);

    bool ok = f1.open(QIODevice::ReadOnly) && f2.open(QIODevice::ReadOnly);
    GT_CHECK_RESULT(ok, f1.errorString() + " " + f2.errorString(), false);

    QByteArray byteArray1 = f1.readAll();
    QByteArray byteArray2 = f2.readAll();

    GT_CHECK_RESULT((f1.error() == QFile::NoError) && (f2.error() == QFile::NoError), f1.errorString() + " " + f2.errorString(), false);

    return byteArray1 == byteArray2;
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "getSize"
qint64 GTFile::getSize(GUITestOpStatus &os, const QString &path){
    QFile f(path);
    bool ok = f.open(QIODevice::ReadOnly);
    GT_CHECK_RESULT(ok, "file " + path + "not found",-1);

    int size = f.size();
    f.close();
    return size;
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "copy"
void GTFile::copy(GUITestOpStatus &os, const QString& from, const QString& to) {

    QFile f2(to);
    bool ok = f2.open(QIODevice::ReadOnly);
    if (ok) {
        f2.remove();
    }

    bool copied = QFile::copy(from, to);
    GT_CHECK(copied == true, "can't copy <" + from + "> to <" + to + ">");
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "copyDir"
void GTFile::copyDir(GUITestOpStatus &os, const QString& dirToCopy, const QString& dirToPaste) {

    QDir from;
    from.setFilter(QDir::Hidden | QDir::AllDirs | QDir::Files);
    from.setPath(dirToCopy);

    QString pastePath = dirToPaste;
    bool ok = QDir().mkpath(pastePath);
    GT_CHECK(ok, "could not create directory: " + pastePath);

    QFileInfoList list = from.entryInfoList();
    foreach(QFileInfo info, list){
        if(info.fileName()=="." || info.fileName()==".."){
            continue;
        }
        if (info.isFile()){
            copy(os, info.filePath(), pastePath  + '/' + info.fileName());
        }else if(info.isDir()){
            copyDir(os, info.filePath(), pastePath  + '/' + info.fileName());
        }

    }
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "removeDir"
#ifdef Q_OS_WIN
void GTFile::removeDir(QString dirName)
{
    QDir dir(dirName);
    dir.setFilter(QDir::Hidden | QDir::AllDirs | QDir::Files);

    foreach (QFileInfo fileInfo, dir.entryInfoList()) {
        QString fileName = fileInfo.fileName();
        QString filePath = fileInfo.filePath();
        if (fileName != "." && fileName != "..") {
            QFile file(filePath);
            file.setPermissions(QFile::ReadOther | QFile::WriteOther);
            if(!file.remove(filePath)){
                QDir dir(filePath);
                if(!dir.rmdir(filePath)){
                    removeDir(filePath);
                }
            }
        }
    }
    dir.rmdir(dir.absoluteFilePath(dirName));
}
#else
void GTFile::removeDir(QString dirName)
{
    QDir dir(dirName);
    qDebug("GT_DEBUG_MESSAGE removing dir: %s", dirName.toLocal8Bit().constData());

    foreach (QFileInfo fileInfo, dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Hidden)) {
        QString fileName = fileInfo.fileName();
        QString filePath = fileInfo.filePath();
        if (fileName != "." && fileName != "..") {
            if(QFile::remove(filePath))
                continue;
            else{
                QDir dir(filePath);
                if(dir.rmdir(filePath))
                    continue;
                else
                    removeDir(filePath);
            }
        }
    }
    dir.rmdir(dir.absoluteFilePath(dirName));

    qDebug("GT_DEBUG_MESSAGE directory removed: %s", dirName.toLocal8Bit().constData());

}
#endif

#undef GT_METHOD_NAME

#define GT_METHOD_NAME "backup"
void GTFile::backup(GUITestOpStatus &os, const QString& path) {

    copy(os, path, path + backupPostfix);
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "backupDir"
void GTFile::backupDir(GUITestOpStatus &os, const QString& path) {

    copyDir(os, path, path + backupPostfix);
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "restore"
void GTFile::restore(GUITestOpStatus &os, const QString& path) {

    QFile backupFile(path + backupPostfix);

    bool ok = backupFile.open(QIODevice::ReadOnly);
    GT_CHECK(ok, "There is no backup file for <" + path + ">");

    QFile file(path);
    ok = file.open(QIODevice::ReadOnly);
    if (ok) {
        file.remove();
    }

    bool renamed = backupFile.rename(path);
    GT_CHECK(renamed == true, "restore of <" + path + "> can't be done");
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "restoreDir"
void GTFile::restoreDir(GUITestOpStatus &os, const QString& path) {
    QDir backupDir(path + backupPostfix);
    bool exists = backupDir.exists();
    if(!exists){
        return;
    }

    QDir dir(path);
    exists = dir.exists();
    if (exists) {
        removeDir(dir.absolutePath());
    }

    bool renamed = backupDir.rename(path + backupPostfix, path);
    GT_CHECK(renamed == true, "restore of <" + path + "> can't be done");
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "check"
bool GTFile::check(GUITestOpStatus &/*os*/, const QString& path) {
    QFile file(path);
    return file.exists();
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "create"
void GTFile::create(GUITestOpStatus &os, const QString &filePath) {
    Q_UNUSED(os);
    bool success = QFile(filePath).open(QIODevice::WriteOnly);
    GT_CHECK(success, "Can't open file to write");
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "readAll"
QByteArray GTFile::readAll(GUITestOpStatus &os, const QString &filePath) {
    Q_UNUSED(os);
    QFile file(filePath);
    const bool opened = file.open(QFile::ReadOnly);
    GT_CHECK_RESULT(opened, "Can't open file for read", "");

    return file.readAll();
}
#undef GT_METHOD_NAME
#undef GT_CLASS_NAME

} //namespace
