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

#ifndef LIBREPCB_CORE_BI_BASE_H
#define LIBREPCB_CORE_BI_BASE_H

/*******************************************************************************
 *  Includes
 ******************************************************************************/
#include <QtCore>
#include <QtWidgets>

/*******************************************************************************
 *  Namespace / Forward Declarations
 ******************************************************************************/
namespace librepcb {

class Board;
class Circuit;
class Point;
class Project;

/*******************************************************************************
 *  Class BI_Base
 ******************************************************************************/

/**
 * @brief The Board Item Base (BI_Base) class
 */
class BI_Base : public QObject {
  Q_OBJECT

public:
  // Constructors / Destructor
  BI_Base() = delete;
  BI_Base(const BI_Base& other) = delete;
  BI_Base(Board& board) noexcept;
  virtual ~BI_Base() noexcept;

  // Getters
  Project& getProject() const noexcept;
  Circuit& getCircuit() const noexcept;
  Board& getBoard() const noexcept { return mBoard; }
  virtual bool isAddedToBoard() const noexcept { return mIsAddedToBoard; }

  // General Methods
  virtual void addToBoard();
  virtual void removeFromBoard();

  // Operator Overloadings
  BI_Base& operator=(const BI_Base& rhs) = delete;

protected:
  Board& mBoard;

private:
  // General Attributes
  bool mIsAddedToBoard;
};

/*******************************************************************************
 *  End of File
 ******************************************************************************/

}  // namespace librepcb

#endif
