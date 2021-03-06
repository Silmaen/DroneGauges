/**
 * @file Adi.cpp
 * @author damien.lachouette 
 * @date 23/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "gauge/pfd/Adi.h"
#include "base/base.h"

#ifndef M_PI
#define M_PI 3.14159265359
#endif

namespace dg::ui::gauge::pfd {


void ADI::init(double scale) {
    DisplayElement::init(scale);
    _itemBack= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_back.svg");
    _itemBack->setCacheMode(QGraphicsItem::NoCache);
    _itemBack->setZValue(0);
    _itemBack->setScale(getScale());
    _itemBack->setTransformOriginPoint(_originalBackPos);
    _itemBack->moveBy(-_originalBackPos.x(), -_originalBackPos.y());
    getScene()->addItem(_itemBack);

    _itemLadd= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_ladd.svg");
    _itemLadd->setCacheMode(QGraphicsItem::NoCache);
    _itemLadd->setZValue(10);
    _itemLadd->setScale(getScale() * _scaleLow);
    _itemLadd->setTransformOriginPoint(_originalLaddPos);
    _itemLadd->moveBy(-_originalLaddPos.x(), -_originalLaddPos.y());
    getScene()->addItem(_itemLadd);

    _itemRoll= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_roll.svg");
    _itemRoll->setCacheMode(QGraphicsItem::NoCache);
    _itemRoll->setZValue(30);
    _itemRoll->setScale(getScale() * _scaleLow);
    _itemRoll->setTransformOriginPoint(_originalRollPos);
    _itemRoll->moveBy(-_originalRollPos.x(), -_originalRollPos.y());
    getScene()->addItem(_itemRoll);

    _itemMask= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_mask.svg");
    _itemMask->setCacheMode(QGraphicsItem::NoCache);
    _itemMask->setZValue(60);
    _itemMask->setScale(getScale() * _scaleLow);
    _itemMask->moveBy(-getScale() * _scaleLow * _originalMaskPos.x(), -getScale() * _scaleLow * _originalMaskPos.y());
    getScene()->addItem(_itemMask);
}

void ADI::update(double scale) {
    DisplayElement::update(scale);
    updateBackView();
    updateLadderView();
    updateRollView();
}

void ADI::updateBackView(){
    double roll_rad= M_PI * _roll / 180.0;
    _itemBack->setRotation(-_roll);
    double deltaBack= core::base::clamp(_originalPixPerDeg * _pitch, _deltaBack_min, _deltaBack_max);
    deltaBack*= getScale() * _scaleLow;
    QPointF roll(std::sin(roll_rad), std::cos(roll_rad));
    roll*= deltaBack;
    roll-= _originalBackPos;
    _itemBack->setPos(roll);
}

void ADI::updateLadderView(){
    double delta   = _originalPixPerDeg * _pitch;
    double roll_rad= M_PI * _roll / 180.0;
    _itemLadd->setRotation(-_roll);
    QPointF roll(std::sin(roll_rad), std::cos(roll_rad));
    roll*= getScale() * _scaleLow * delta;
    roll-= _originalLaddPos;
    _itemLadd->setPos(roll);
}

void ADI::updateRollView(){
    _itemRoll->setRotation(-_roll);
}

void ADI::setRoll(double roll) {
    _roll= core::base::clamp(roll, -180, 180);
}

void ADI::setPitch(double pitch) {
    _pitch= core::base::clamp(pitch, -90, 90);
}

}// namespace dg::ui::gauge::pfd
