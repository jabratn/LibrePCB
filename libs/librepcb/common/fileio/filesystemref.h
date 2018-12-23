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

#ifndef LIBREPCB_FILESYSTEMREF_H
#define LIBREPCB_FILESYSTEMREF_H

/*******************************************************************************
 *  Includes
 ******************************************************************************/
#include "filesystem.h"

#include <QtCore>

/*******************************************************************************
 *  Namespace / Forward Declarations
 ******************************************************************************/

namespace librepcb {

/*******************************************************************************
 *  Class FileSystemRef
 ******************************************************************************/

class FileSystemRef final : public FileSystem {
  Q_DECLARE_TR_FUNCTIONS(FileSystemRef)

public:
  // Constructors / Destructor
  FileSystemRef() = delete;
  FileSystemRef(const FileSystemRef& other) noexcept;
  FileSystemRef(FileSystem& fs, const QString& root = "") noexcept;
  ~FileSystemRef() noexcept;

  // File Operations
  // QString getRootName() const noexcept override;
  QString     getPrettyPath(const QString& path = "") const noexcept override;
  QStringList getSubDirs(const QString& path = "") const noexcept override;
  QStringList getFilesInDir(QString dir = "", const QStringList& filters =
                                                  QStringList()) const override;
  bool        fileExists(const QString& path) const noexcept override;
  QByteArray  readBinary(const QString& path) const override;
  void     writeBinary(const QString& path, const QByteArray& content) override;
  FilePath createTemporaryFileOnDisk(const QString& path) const override;
  void     removeFile(const QString& path) override;
  void     removeDirRecursively(const QString& path) override;

  // Operator Overloadings
  FileSystemRef& operator=(const FileSystemRef& rhs) noexcept;

private:  // Methods
  QString getAbsPath(const QString& path) const noexcept;

private:  // Data
  FileSystem* mFileSystem;
  QString     mRoot;
};

/*******************************************************************************
 *  End of File
 ******************************************************************************/

}  // namespace librepcb

#endif  // LIBREPCB_FILESYSTEMREF_H