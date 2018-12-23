/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 LibrePCB Developers, see AUTHORS.md for contributors.
 * https://librepcb.org/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************************
 *  Includes
 ******************************************************************************/
#include "filesystemref.h"

/*******************************************************************************
 *  Namespace
 ******************************************************************************/
namespace librepcb {

/*******************************************************************************
 *  Constructors / Destructor
 ******************************************************************************/

FileSystemRef::FileSystemRef(FileSystem& fs, const QString& root) noexcept
  : mFileSystem(&fs), mRoot(root) {
  Q_ASSERT(!mRoot.endsWith('/'));
}

FileSystemRef::FileSystemRef(const FileSystemRef& other) noexcept
  : mFileSystem(other.mFileSystem), mRoot(other.mRoot) {
}

FileSystemRef::~FileSystemRef() noexcept {
}

/*******************************************************************************
 *  File Operations
 ******************************************************************************/

// QString FileSystemRef::getRootName() const noexcept {
//  if (mRoot.isEmpty()) {
//    return mFileSystem->getRootName();
//  } else {
//    return mRoot.section('/', -1);
//  }
//}

QString FileSystemRef::getPrettyPath(const QString& path) const noexcept {
  return mFileSystem->getPrettyPath(getAbsPath(path));
}

QStringList FileSystemRef::getSubDirs(const QString& path) const noexcept {
  return mFileSystem->getSubDirs(getAbsPath(path));
}

QStringList FileSystemRef::getFilesInDir(QString            dir,
                                         const QStringList& filters) const {
  return mFileSystem->getFilesInDir(getAbsPath(dir), filters);
}

bool FileSystemRef::fileExists(const QString& path) const noexcept {
  return mFileSystem->fileExists(getAbsPath(path));
}

QByteArray FileSystemRef::readBinary(const QString& path) const {
  return mFileSystem->readBinary(getAbsPath(path));
}

void FileSystemRef::writeBinary(const QString&    path,
                                const QByteArray& content) {
  mFileSystem->writeBinary(getAbsPath(path), content);
}

FilePath FileSystemRef::createTemporaryFileOnDisk(const QString& path) const {
  return mFileSystem->createTemporaryFileOnDisk(getAbsPath(path));
}

void FileSystemRef::removeFile(const QString& path) {
  mFileSystem->removeFile(getAbsPath(path));
}

void FileSystemRef::removeDirRecursively(const QString& path) {
  mFileSystem->removeDirRecursively(getAbsPath(path));
}

/*******************************************************************************
 *  Operator Overloadings
 ******************************************************************************/

FileSystemRef& FileSystemRef::operator=(const FileSystemRef& rhs) noexcept {
  mFileSystem = rhs.mFileSystem;
  mRoot       = rhs.mRoot;
  return *this;
}

/*******************************************************************************
 *  Private Methods
 ******************************************************************************/

QString FileSystemRef::getAbsPath(const QString& path) const noexcept {
  return mRoot % "/" % path;
}

/*******************************************************************************
 *  End of File
 ******************************************************************************/

}  // namespace librepcb
