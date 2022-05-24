/**
 * @file Alt.cpp
 * @author damien.lachouette 
 * @date 23/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "gauge/pfd/Alt.h"
#include "gauge/pfd/color.h"
#include "gauge/pfd/font.h"
#include <iostream>

namespace dg::ui::gauge::pfd {

ALT::ALT(QGraphicsScene* scene):
    _scene{scene} {
}

void ALT::init(double scale) {
    _scale   = scale * _scale_factor;
    _itemBack= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_alt_back.svg");
    _itemBack->setCacheMode(QGraphicsItem::NoCache);
    _itemBack->setZValue(70);
    _itemBack->setScale(_scale);
    _itemBack->setTransformOriginPoint(backpos);
    _itemBack->setPos(-backpos + _scale * position);
    _itemBack->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    _scene->addItem(_itemBack);

    _itemScale1= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_alt_scale.svg", _itemBack);
    _itemScale1->setCacheMode(QGraphicsItem::NoCache);
    _itemScale1->setZValue(77);
    _itemScale1->setTransformOriginPoint(scale1Pos);
    _itemScale1->setPos(-scale1Pos + _scale * position);

    _itemLabel1= new QGraphicsTextItem(QString("99999"), _itemBack);
    _itemLabel1->setCacheMode(QGraphicsItem::NoCache);
    _itemLabel1->setZValue(78);
    _itemLabel1->setDefaultTextColor(white);
    _itemLabel1->setFont(Font::small());

    _itemLabel2= new QGraphicsTextItem(QString("99999"), _itemBack);
    _itemLabel2->setCacheMode(QGraphicsItem::NoCache);
    _itemLabel2->setZValue(78);
    _itemLabel2->setDefaultTextColor(white);
    _itemLabel2->setFont(Font::small());

    _itemLabel3= new QGraphicsTextItem(QString("99999"), _itemBack);
    _itemLabel3->setCacheMode(QGraphicsItem::NoCache);
    _itemLabel3->setZValue(78);
    _itemLabel3->setDefaultTextColor(white);
    _itemLabel3->setFont(Font::small());

    _itemGround= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_alt_ground.svg", _itemBack);
    _itemGround->setCacheMode(QGraphicsItem::NoCache);
    _itemGround->setZValue(79);
    _itemGround->setTransformOriginPoint(groundPos);
    _itemGround->setPos(-groundPos);

    _itemFrame= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_alt_frame.svg");
    _itemFrame->setCacheMode(QGraphicsItem::NoCache);
    _itemFrame->setZValue(110);
    _itemFrame->setScale(_scale);
    _itemFrame->setTransformOriginPoint(framePos);
    _itemFrame->setPos(-framePos + _scale * position);
    _scene->addItem(_itemFrame);

    _itemAltitude= new QGraphicsTextItem(QString("    0"), _itemFrame);
    _itemAltitude->setCacheMode(QGraphicsItem::NoCache);
    _itemAltitude->setZValue(120);
    _itemAltitude->setDefaultTextColor(white);
    _itemAltitude->setFont(Font::medium());
}

void ALT::update(double scale) {
    _scale= scale * _scale_factor;
    updateAltView();
    updateVertVelView();
}

void ALT::updateAltView() {
    _itemAltitude->setPlainText(QString("%1").arg(_altitude, 5, 'f', 0, QChar(' ')));

    double _scale1DeltaY= _originalPixPerAlt * _altitude;
    double _groundDeltaY= _scale1DeltaY;
    double _labelsDeltaY= _scale1DeltaY;

    while(_scale1DeltaY > scaleSize) _scale1DeltaY-= scaleSize / 2.0;
    QPointF scalePosT{0, _scale1DeltaY};

    _itemScale1->setPos(-scale1Pos + scalePosT);
    QPointF groundPosT{0, _groundDeltaY};
    _itemGround->setPos(-groundPos + groundPosT);

    int tmp             = floor(_altitude + 0.5);
    int altLabelInterval= scaleSize / 2.0 / _originalPixPerAlt;

    int alt= tmp - (tmp % altLabelInterval);

    double alt1= static_cast<double>(alt) + altLabelInterval;
    double alt2= static_cast<double>(alt);
    double alt3= static_cast<double>(alt) - altLabelInterval;

    while(_labelsDeltaY > altLabelInterval) {
        _labelsDeltaY= _labelsDeltaY - scaleSize / 2.0;
    }

    if(_labelsDeltaY < 0.0 && _altitude > alt2) {
        alt1+= altLabelInterval;
        alt2+= altLabelInterval;
        alt3+= altLabelInterval;
    }

    _itemLabel1->setPos(0.0, _labelsDeltaY);
    _itemLabel2->setPos(0.0, _labelsDeltaY + scaleSize / 2.0);
    _itemLabel3->setPos(0.0, _labelsDeltaY + scaleSize);

    if(alt1 > 0.0 && alt1 <= 100000.0) {
        _itemLabel1->setVisible(true);
        _itemLabel1->setPlainText(QString("%1").arg(alt1, 5, 'f', 0, QChar(' ')));
    } else {
        _itemLabel1->setVisible(false);
    }

    if(alt2 > 0.0 && alt2 <= 100000.0) {
        _itemLabel2->setVisible(true);
        _itemLabel2->setPlainText(QString("%1").arg(alt2, 5, 'f', 0, QChar(' ')));
    } else {
        _itemLabel2->setVisible(false);
    }

    if(alt3 > 0.0 && alt3 <= 100000.0) {
        _itemLabel3->setVisible(true);
        _itemLabel3->setPlainText(QString("%1").arg(alt3, 5, 'f', 0, QChar(' ')));
    } else {
        _itemLabel3->setVisible(false);
    }
}

void ALT::updateVertVelView() {
}

void ALT::setAltitude(double altitude) {
    _altitude= altitude;
}

void ALT::setVerticalVelocity(double verticalVelocity) {
    _verticalVelocity= verticalVelocity;
}

}// namespace dg::ui::gauge::pfd
