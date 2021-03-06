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
#include "circle.h"

#include <QtCore>

/*******************************************************************************
 *  Namespace
 ******************************************************************************/
namespace librepcb {

/*******************************************************************************
 *  Constructors / Destructor
 ******************************************************************************/

Circle::Circle(const Circle& other) noexcept
  : mUuid(other.mUuid),
    mLayerName(other.mLayerName),
    mLineWidth(other.mLineWidth),
    mIsFilled(other.mIsFilled),
    mIsGrabArea(other.mIsGrabArea),
    mCenter(other.mCenter),
    mDiameter(other.mDiameter) {
}

Circle::Circle(const Uuid& uuid, const Circle& other) noexcept : Circle(other) {
  mUuid = uuid;
}

Circle::Circle(const Uuid& uuid, const GraphicsLayerName& layerName,
               const UnsignedLength& lineWidth, bool fill, bool isGrabArea,
               const Point& center, const PositiveLength& diameter) noexcept
  : mUuid(uuid),
    mLayerName(layerName),
    mLineWidth(lineWidth),
    mIsFilled(fill),
    mIsGrabArea(isGrabArea),
    mCenter(center),
    mDiameter(diameter) {
}

Circle::Circle(const SExpression& node)
  : mUuid(Uuid::createRandom()),  // backward compatibility, remove this some
                                  // time!
    mLayerName(node.getValueByPath<GraphicsLayerName>("layer", true)),
    mLineWidth(node.getValueByPath<UnsignedLength>("width")),
    mIsFilled(node.getValueByPath<bool>("fill")),
    mIsGrabArea(false),
    mCenter(0, 0),
    mDiameter(1) {
  if (node.getChildByIndex(0).isString()) {
    mUuid = node.getChildByIndex(0).getValue<Uuid>();
  }
  if (node.tryGetChildByPath("grab_area")) {
    mIsGrabArea = node.getValueByPath<bool>("grab_area");
  } else {
    // backward compatibility, remove this some time!
    mIsGrabArea = node.getValueByPath<bool>("grab");
  }
  if (node.tryGetChildByPath("position")) {
    mCenter = Point(node.getChildByPath("position"));
  } else {
    // backward compatibility, remove this some time!
    mCenter = Point(node.getChildByPath("pos"));
  }
  if (node.tryGetChildByPath("diameter")) {
    mDiameter = node.getValueByPath<PositiveLength>("diameter");
  } else if (node.tryGetChildByPath("dia")) {
    // backward compatibility, remove this some time!
    mDiameter = node.getValueByPath<PositiveLength>("dia");
  } else if (node.tryGetChildByPath("size")) {
    // backward compatibility, remove this some time!
    mDiameter = Point(node.getChildByPath("size")).getX();
  } else {
    // backward compatibility, remove this some time!
    mDiameter = node.getValueByPath<Length>("rx") * 2;
  }
}

Circle::~Circle() noexcept {
}

/*******************************************************************************
 *  Setters
 ******************************************************************************/

void Circle::setLayerName(const GraphicsLayerName& name) noexcept {
  if (name == mLayerName) return;
  mLayerName = name;
  foreach (IF_CircleObserver* object, mObservers) {
    object->circleLayerNameChanged(mLayerName);
  }
}

void Circle::setLineWidth(const UnsignedLength& width) noexcept {
  if (width == mLineWidth) return;
  mLineWidth = width;
  foreach (IF_CircleObserver* object, mObservers) {
    object->circleLineWidthChanged(mLineWidth);
  }
}

void Circle::setIsFilled(bool isFilled) noexcept {
  if (isFilled == mIsFilled) return;
  mIsFilled = isFilled;
  foreach (IF_CircleObserver* object, mObservers) {
    object->circleIsFilledChanged(mIsFilled);
  }
}

void Circle::setIsGrabArea(bool isGrabArea) noexcept {
  if (isGrabArea == mIsGrabArea) return;
  mIsGrabArea = isGrabArea;
  foreach (IF_CircleObserver* object, mObservers) {
    object->circleIsGrabAreaChanged(mIsGrabArea);
  }
}

void Circle::setCenter(const Point& center) noexcept {
  if (center == mCenter) return;
  mCenter = center;
  foreach (IF_CircleObserver* object, mObservers) {
    object->circleCenterChanged(mCenter);
  }
}

void Circle::setDiameter(const PositiveLength& dia) noexcept {
  if (dia == mDiameter) return;
  mDiameter = dia;
  foreach (IF_CircleObserver* object, mObservers) {
    object->circleDiameterChanged(mDiameter);
  }
}

/*******************************************************************************
 *  Transformations
 ******************************************************************************/

Circle& Circle::translate(const Point& offset) noexcept {
  mCenter += offset;
  return *this;
}

/*******************************************************************************
 *  General Methods
 ******************************************************************************/

void Circle::registerObserver(IF_CircleObserver& object) const noexcept {
  mObservers.insert(&object);
}

void Circle::unregisterObserver(IF_CircleObserver& object) const noexcept {
  mObservers.remove(&object);
}

void Circle::serialize(SExpression& root) const {
  root.appendChild(mUuid);
  root.appendChild("layer", mLayerName, false);
  root.appendChild("width", mLineWidth, true);
  root.appendChild("fill", mIsFilled, false);
  root.appendChild("grab_area", mIsGrabArea, false);
  root.appendChild("diameter", mDiameter, false);
  root.appendChild(mCenter.serializeToDomElement("position"), false);
}

/*******************************************************************************
 *  Operator Overloadings
 ******************************************************************************/

bool Circle::operator==(const Circle& rhs) const noexcept {
  if (mUuid != rhs.mUuid) return false;
  if (mLayerName != rhs.mLayerName) return false;
  if (mLineWidth != rhs.mLineWidth) return false;
  if (mIsFilled != rhs.mIsFilled) return false;
  if (mIsGrabArea != rhs.mIsGrabArea) return false;
  if (mCenter != rhs.mCenter) return false;
  if (mDiameter != rhs.mDiameter) return false;
  return true;
}

Circle& Circle::operator=(const Circle& rhs) noexcept {
  mUuid       = rhs.mUuid;
  mLayerName  = rhs.mLayerName;
  mLineWidth  = rhs.mLineWidth;
  mIsFilled   = rhs.mIsFilled;
  mIsGrabArea = rhs.mIsGrabArea;
  mCenter     = rhs.mCenter;
  mDiameter   = rhs.mDiameter;
  return *this;
}

/*******************************************************************************
 *  End of File
 ******************************************************************************/

}  // namespace librepcb
