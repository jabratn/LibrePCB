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

#ifndef LIBREPCB_EDITOR_CMDLIBRARYELEMENTEDIT_H
#define LIBREPCB_EDITOR_CMDLIBRARYELEMENTEDIT_H

/*******************************************************************************
 *  Includes
 ******************************************************************************/
#include "cmdlibrarybaseelementedit.h"

#include <librepcb/core/library/libraryelement.h>

#include <QtCore>

/*******************************************************************************
 *  Namespace / Forward Declarations
 ******************************************************************************/
namespace librepcb {
namespace editor {

/*******************************************************************************
 *  Class CmdLibraryElementEdit
 ******************************************************************************/

/**
 * @brief The CmdLibraryElementEdit class
 */
class CmdLibraryElementEdit : public CmdLibraryBaseElementEdit {
public:
  // Constructors / Destructor
  CmdLibraryElementEdit() = delete;
  CmdLibraryElementEdit(const CmdLibraryElementEdit& other) = delete;
  explicit CmdLibraryElementEdit(LibraryElement& element,
                                 const QString& text) noexcept;
  virtual ~CmdLibraryElementEdit() noexcept;

  // Setters
  void setCategories(const QSet<Uuid>& uuids) noexcept;
  void setResources(const ResourceList& resources) noexcept;

  // Operator Overloadings
  CmdLibraryElementEdit& operator=(const CmdLibraryElementEdit& rhs) = delete;

protected:  // Methods
  /// @copydoc ::librepcb::editor::UndoCommand::performExecute()
  virtual bool performExecute() override;

  /// @copydoc ::librepcb::editor::UndoCommand::performUndo()
  virtual void performUndo() override;

  /// @copydoc ::librepcb::editor::UndoCommand::performRedo()
  virtual void performRedo() override;

private:  // Data
  LibraryElement& mElement;

  QSet<Uuid> mOldCategories;
  QSet<Uuid> mNewCategories;
  ResourceList mOldResources;
  ResourceList mNewResources;
};

/*******************************************************************************
 *  End of File
 ******************************************************************************/

}  // namespace editor
}  // namespace librepcb

#endif
