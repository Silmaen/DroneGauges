/**
 * @file hdg.cpp
 * @author damien.lachouette 
 * @date 25/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "gauge/pfd/Hdg.h"
#include "base/base.h"
#include "gauge/pfd/color.h"
#include "gauge/pfd/font.h"

namespace dg::ui::gauge::pfd {

void HDG::init(double scale) {
    DisplayElement::init(scale);

    _itemBack= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_hdg_back.svg");
    _itemBack->setCacheMode(QGraphicsItem::NoCache);
    _itemBack->setZValue(70);
    _itemBack->setScale(getScale());
    _itemBack->setTransformOriginPoint(backPos);
    _itemBack->setPos(-backPos + getScale() * getPosition());
    _itemBack->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    getScene()->addItem(_itemBack);

    _itemScale= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_hdg_scale.svg", _itemBack);
    _itemScale->setCacheMode(QGraphicsItem::NoCache);
    _itemScale->setZValue(77);
    _itemScale->setPos(-scalePos);

    _itemFrame= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_hdg_frame.svg");
    _itemFrame->setCacheMode(QGraphicsItem::NoCache);
    _itemFrame->setZValue(80);
    _itemFrame->setScale(getScale());
    _itemFrame->setTransformOriginPoint(framePos);
    _itemFrame->setPos(-framePos + getScale() * getPosition());
    _itemFrame->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    getScene()->addItem(_itemFrame);

    _itemHeading= new QGraphicsTextItem(QString("    0"), _itemFrame);
    _itemHeading->setCacheMode(QGraphicsItem::NoCache);
    _itemHeading->setZValue(120);
    _itemHeading->setDefaultTextColor(white);
    _itemHeading->setFont(Font::medium());
    _itemHeading->setPos(headingPos);

}

void HDG::update(double scale) {
    DisplayElement::update(scale);
    updateView();
}

void HDG::setYaw(double yaw) {
    _heading= yaw;
    while(_heading < 0) _heading+= 360.0;
    while(_heading >= 360) _heading-= 360.0;
}

void HDG::updateView() {
    QPointF offset{_heading * _originalPixPerDeg, 0};
    if(offset.x() > 275 * _originalPixPerDeg) offset.setX(offset.x() - 360 * _originalPixPerDeg);
    _itemScale->setPos(-scalePos - offset);
    _itemHeading->setPlainText(QString("%1").arg(_heading, 5, 'f', 0, QChar(' ')));
    QPointF tmp = headingPos;
    if (_heading <100 )tmp.setX(tmp.x() - 4.5);
    if (_heading <10 )tmp.setX(tmp.x() - 4.5);
    _itemHeading->setPos(tmp);
}

}// namespace dg::ui::gauge::pfd
