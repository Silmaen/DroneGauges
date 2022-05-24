/**
 * @file Asi.cpp
 * @author argawaen
 * @date 24/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "gauge/pfd/Asi.h"
#include "base/base.h"
#include "gauge/pfd/color.h"
#include "gauge/pfd/font.h"

#include <iostream>

namespace dg::ui::gauge::pfd {

ASI::ASI(QGraphicsScene* scene):
    _scene{scene} {}

void ASI::init(double scale) {
    _scale   = scale * _scale_factor;
    _itemBack= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_asi_back.svg");
    _itemBack->setCacheMode(QGraphicsItem::NoCache);
    _itemBack->setZValue(70);
    _itemBack->setScale(_scale);
    _itemBack->setTransformOriginPoint(backpos);
    _itemBack->setPos(-backpos + _scale * position);
    _itemBack->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    _scene->addItem(_itemBack);

    _itemScale1= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_asi_scale.svg", _itemBack);
    _itemScale1->setCacheMode(QGraphicsItem::NoCache);
    _itemScale1->setZValue(80);
    _itemScale1->setTransformOriginPoint(scale1Pos);
    _itemScale1->setPos(-scale1Pos);

    _itemLabel1= new QGraphicsTextItem(QString("999"), _itemBack);
    _itemLabel1->setCacheMode(QGraphicsItem::NoCache);
    _itemLabel1->setZValue(90);
    _itemLabel1->setDefaultTextColor(white);
    _itemLabel1->setFont(Font::small());

    _itemLabel2= new QGraphicsTextItem(QString("999"), _itemBack);
    _itemLabel2->setCacheMode(QGraphicsItem::NoCache);
    _itemLabel2->setZValue(90);
    _itemLabel2->setDefaultTextColor(white);
    _itemLabel2->setFont(Font::small());

    _itemLabel3= new QGraphicsTextItem(QString("999"), _itemBack);
    _itemLabel3->setCacheMode(QGraphicsItem::NoCache);
    _itemLabel3->setZValue(90);
    _itemLabel3->setDefaultTextColor(white);
    _itemLabel3->setFont(Font::small());

    _itemLabel4= new QGraphicsTextItem(QString("999"), _itemBack);
    _itemLabel4->setCacheMode(QGraphicsItem::NoCache);
    _itemLabel4->setZValue(90);
    _itemLabel4->setDefaultTextColor(magenta);
    _itemLabel4->setFont(Font::small());

    _itemLabel5= new QGraphicsTextItem(QString("999"), _itemBack);
    _itemLabel5->setCacheMode(QGraphicsItem::NoCache);
    _itemLabel5->setZValue(90);
    _itemLabel5->setDefaultTextColor(white);
    _itemLabel5->setFont(Font::small());

    _itemLabel6= new QGraphicsTextItem(QString("999"), _itemBack);
    _itemLabel6->setCacheMode(QGraphicsItem::NoCache);
    _itemLabel6->setZValue(90);
    _itemLabel6->setDefaultTextColor(white);
    _itemLabel6->setFont(Font::small());

    _itemLabel7= new QGraphicsTextItem(QString("999"), _itemBack);
    _itemLabel7->setCacheMode(QGraphicsItem::NoCache);
    _itemLabel7->setZValue(90);
    _itemLabel7->setDefaultTextColor(white);
    _itemLabel7->setFont(Font::small());

    _itemFrame= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_asi_frame.svg");
    _itemFrame->setCacheMode(QGraphicsItem::NoCache);
    _itemFrame->setZValue(110);
    _itemFrame->setScale(_scale);
    _itemFrame->setTransformOriginPoint(framePos);
    _itemFrame->setPos(-framePos + _scale * position);
    _scene->addItem(_itemFrame);
    /*
    _itemVfe= _scene->addRect(_scaleX * _originalVfePos.x(),
                              _scaleY * _originalVfePos.y(),
                              _scaleX * _originalVfeWidth,
                              _scaleY * 10,
                              _vfePen, _vfeBrush);
    _itemVfe->setZValue(_iasVfeZ);

    _itemVne= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_asi_vne.svg");
    _itemVne->setCacheMode(QGraphicsItem::NoCache);
    _itemVne->setZValue(90);
    _itemVne->setScale(_scale);
    _itemVne->setPos(_originalScale1Pos);
    _scene->addItem(_itemVne);
*/
    _itemAirspeed= new QGraphicsTextItem(QString("000"), _itemFrame);
    _itemAirspeed->setCacheMode(QGraphicsItem::NoCache);
    _itemAirspeed->setZValue(120);
    _itemAirspeed->setTextInteractionFlags(Qt::NoTextInteraction);
    _itemAirspeed->setDefaultTextColor(white);
    _itemAirspeed->setFont(Font::medium());
    _itemAirspeed->setPos(airSpeedPos);
}

void ASI::update(double scale) {
    _scale= scale * _scale_factor;

    _itemAirspeed->setPlainText(QString("%1").arg(_airspeed, 3, 'f', 0, QChar(' ')));

    double _scale1DeltaY= _originalPixPerSpd * _airspeed;
    double _labelsDeltaY= _scale1DeltaY - 15;
    while(_scale1DeltaY > scaleSize) _scale1DeltaY-= scaleSize / 2.0;
    QPointF scalePosT{0, _scale1DeltaY};
    _itemScale1->setPos(-scale1Pos + scalePosT);

    int tmp             = floor(_airspeed + 0.5);
    int velLabelInterval= scaleSize / 4.0 / _originalPixPerSpd;

    int spd= tmp - (tmp % velLabelInterval);

    double spd1= static_cast<double>(spd) + 3.0 * velLabelInterval;
    double spd2= static_cast<double>(spd) + 2.0 * velLabelInterval;
    double spd3= static_cast<double>(spd) + velLabelInterval;
    double spd4= static_cast<double>(spd);
    double spd5= static_cast<double>(spd) - velLabelInterval;
    double spd6= static_cast<double>(spd) - 2.0 * velLabelInterval;
    double spd7= static_cast<double>(spd) - 3.0 * velLabelInterval;

    while(_labelsDeltaY > velLabelInterval * 0.75) {
        _labelsDeltaY= _labelsDeltaY - scaleSize / 4;
    }

    if(_labelsDeltaY < 0.0 && _airspeed > spd4) {
        spd1+= velLabelInterval;
        spd2+= velLabelInterval;
        spd3+= velLabelInterval;
        spd4+= velLabelInterval;
        spd5+= velLabelInterval;
        spd6+= velLabelInterval;
        spd7+= velLabelInterval;
    }
    std::cout << _labelsDeltaY << std::endl;
    _itemLabel1->setPos(0.0, _labelsDeltaY);
    _itemLabel2->setPos(0.0, _labelsDeltaY + scaleSize / 4.0);
    _itemLabel3->setPos(0.0, _labelsDeltaY + 2.0 * scaleSize / 4.0);
    _itemLabel4->setPos(0.0, _labelsDeltaY + 3.0 * scaleSize / 4.0);
    _itemLabel5->setPos(0.0, _labelsDeltaY + 4.0 * scaleSize / 4.0);
    _itemLabel6->setPos(0.0, _labelsDeltaY + 5.0 * scaleSize / 4.0);
    _itemLabel7->setPos(0.0, _labelsDeltaY + 6.0 * scaleSize / 4.0);

    if(spd1 >= 0.0 && spd1 <= 10000.0) {
        _itemLabel1->setVisible(true);
        _itemLabel1->setPlainText(QString("%1").arg(spd1, 3, 'f', 0, QChar(' ')));
    } else {
        _itemLabel1->setVisible(false);
    }
    if(spd2 >= 0.0 && spd2 <= 10000.0) {
        _itemLabel2->setVisible(true);
        _itemLabel2->setPlainText(QString("%1").arg(spd2, 3, 'f', 0, QChar(' ')));
    } else {
        _itemLabel2->setVisible(false);
    }
    if(spd3 >= 0.0 && spd3 <= 10000.0) {
        _itemLabel3->setVisible(true);
        _itemLabel3->setPlainText(QString("%1").arg(spd3, 3, 'f', 0, QChar(' ')));
    } else {
        _itemLabel3->setVisible(false);
    }
    if(spd4 >= 0.0 && spd4 <= 10000.0) {
        _itemLabel4->setVisible(true);
        _itemLabel4->setPlainText(QString("%1").arg(spd4, 3, 'f', 0, QChar(' ')));
    } else {
        _itemLabel4->setVisible(false);
    }
    if(spd5 >= 0.0 && spd5 <= 10000.0) {
        _itemLabel5->setVisible(true);
        _itemLabel5->setPlainText(QString("%1").arg(spd5, 3, 'f', 0, QChar(' ')));
    } else {
        _itemLabel5->setVisible(false);
    }
    if(spd6 >= 0.0 && spd6 <= 10000.0) {
        _itemLabel6->setVisible(true);
        _itemLabel6->setPlainText(QString("%1").arg(spd6, 3, 'f', 0, QChar(' ')));
    } else {
        _itemLabel6->setVisible(false);
    }
    if(spd7 >= 0.0 && spd7 <= 10000.0) {
        _itemLabel7->setVisible(true);
        _itemLabel7->setPlainText(QString("%1").arg(spd7, 3, 'f', 0, QChar(' ')));
    } else {
        _itemLabel7->setVisible(false);
    }
}

void ASI::setVelocity(double velocity) {
    _airspeed= velocity;
}

void ASI::setVfe(double vfe) {
    _vfe= vfe;
}

void ASI::setVne(double vne) {
    _vne= vne;
}

}// namespace dg::ui::gauge::pfd
