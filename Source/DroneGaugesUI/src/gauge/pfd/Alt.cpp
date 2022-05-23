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

    _itemScale1= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_alt_scale.svg");
    _itemScale1->setCacheMode(QGraphicsItem::NoCache);
    _itemScale1->setZValue(77);
    _itemScale1->setScale(_scale);
    _itemScale1->setTransformOriginPoint(scale1Pos);
    _itemScale1->setPos(-scale1Pos + _scale * position);
    _scene->addItem(_itemScale1);

    /*_itemScale2= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_alt_scale.svg");
    _itemScale2->setCacheMode(QGraphicsItem::NoCache);
    _itemScale2->setZValue(77);
    _itemScale2->setScale(_scale);
    _itemScale2->setTransformOriginPoint(scale2Pos);
    _itemScale2->setPos(-scale2Pos + _scale * position);
    _scene->addItem(_itemScale2);

    _itemLabel1= new QGraphicsTextItem(QString("99999"));
    _itemLabel1->setCacheMode(QGraphicsItem::NoCache);
    _itemLabel1->setZValue(78);
    _itemLabel1->setDefaultTextColor(white);
    _itemLabel1->setFont(Font::small());
    _itemLabel1->setScale(_scale);
    _itemLabel1->moveBy(_scale * (label1Pos.x() - _itemLabel1->boundingRect().width() / 2.0),
                        _scale * (label1Pos.y() - _itemLabel1->boundingRect().height() / 2.0));
    _scene->addItem(_itemLabel1);

    _itemLabel2= new QGraphicsTextItem(QString("99999"));
    _itemLabel2->setCacheMode(QGraphicsItem::NoCache);
    _itemLabel2->setZValue(78);
    _itemLabel2->setDefaultTextColor(white);
    _itemLabel2->setFont(Font::small());
    _itemLabel2->setScale(_scale);
    _itemLabel2->moveBy(_scale * (label2Pos.x() - _itemLabel2->boundingRect().width() / 2.0),
                        _scale * (label2Pos.y() - _itemLabel2->boundingRect().height() / 2.0));
    _scene->addItem(_itemLabel2);

    _itemLabel3= new QGraphicsTextItem(QString("99999"));
    _itemLabel3->setCacheMode(QGraphicsItem::NoCache);
    _itemLabel3->setZValue(78);
    _itemLabel3->setDefaultTextColor(white);
    _itemLabel3->setFont(Font::small());
    _itemLabel3->setScale(_scale);
    _itemLabel3->moveBy(_scale * (label3Pos.x() - _itemLabel3->boundingRect().width() / 2.0),
                        _scale * (label3Pos.y() - _itemLabel3->boundingRect().height() / 2.0));
    _scene->addItem(_itemLabel3);
*/
    _itemGround= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_alt_ground.svg", _itemBack);
    _itemGround->setCacheMode(QGraphicsItem::NoCache);
    _itemGround->setZValue(79);
    _itemGround->setScale(1);
    _itemGround->setTransformOriginPoint(groundPos);
    _itemGround->setPos(-groundPos);
    _scene->addItem(_itemGround);

    _itemFrame= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_alt_frame.svg");
    _itemFrame->setCacheMode(QGraphicsItem::NoCache);
    _itemFrame->setZValue(110);
    _itemFrame->setScale(_scale);
    _itemFrame->setTransformOriginPoint(framePos);
    _itemFrame->setPos(-framePos + _scale * position);
    _scene->addItem(_itemFrame);
    /*
    _itemAltitude= new QGraphicsTextItem(QString("    0"));
    _itemAltitude->setCacheMode(QGraphicsItem::NoCache);
    _itemAltitude->setZValue(120);
    _itemAltitude->setDefaultTextColor(white);
    _itemAltitude->setFont(Font::medium());
    _itemAltitude->setScale(_scale);
    _itemAltitude->moveBy(_scale * (altitudePos.x() - _itemAltitude->boundingRect().width() / 2.0),
                          _scale * (altitudePos.y() - _itemAltitude->boundingRect().height() / 2.0));
    _scene->addItem(_itemAltitude);

    _itemPressure= new QGraphicsTextItem(QString("  STD  "));
    _itemPressure->setCacheMode(QGraphicsItem::NoCache);
    _itemPressure->setZValue(120);
    _itemPressure->setDefaultTextColor(lime);
    _itemPressure->setFont(Font::medium());
    _itemPressure->setScale(_scale);
    _itemPressure->moveBy(_scale * (pressurePos.x() - _itemPressure->boundingRect().width() / 2.0),
                          _scale * (pressurePos.y() - _itemPressure->boundingRect().height() / 2.0));
    _scene->addItem(_itemPressure);*/
}

void ALT::update(double scale) {
    _scale= scale * _scale_factor;
    updateAltView();
    updateVertVelView();
}

void ALT::updateAltView() {
    //_itemAltitude->setPlainText(QString("%1").arg(_altitude, 5, 'f', 0, QChar(' ')));

    double _scale1DeltaY= _scale * _originalPixPerAlt * _altitude;
    double _scale2DeltaY= _scale1DeltaY;
    double _groundDeltaY= _scale1DeltaY;

    double scaleSingleHeight= _scale * _originalScaleHeight;
    double scaleDoubleHeight= _scale * _originalScaleHeight * 2.0;

    while(_scale1DeltaY > scaleSingleHeight + _scale * 74.5) {
        _scale1DeltaY= _scale1DeltaY - scaleDoubleHeight;
    }

    while(_scale2DeltaY > scaleDoubleHeight + _scale * 74.5) {
        _scale2DeltaY= _scale2DeltaY - scaleDoubleHeight;
    }

    if(_groundDeltaY > _scale * 100.0) _groundDeltaY= _scale * 100.0;

    //_itemScale1->setPos(0.0, _scale1DeltaY);
    //_itemScale2->setPos(0.0, _scale2DeltaY);

    QPointF groundPosT{0, _groundDeltaY};
    _itemGround->setPos(-groundPos + groundPosT);
    //_itemGround->setPos(0.0, _groundDeltaY);

    int tmp= floor(_altitude + 0.5);
    int alt= tmp - (tmp % 500);

    double alt1= static_cast<double>(alt) + 500.0;
    double alt2= static_cast<double>(alt);
    double alt3= static_cast<double>(alt) - 500.0;

    double _labelsDeltaY= _scale * _originalPixPerAlt * _altitude;

    while(_labelsDeltaY > _scale * 37.5) {
        _labelsDeltaY= _labelsDeltaY - _scale * 75.0;
    }

    if(_labelsDeltaY < 0.0 && _altitude > alt2) {
        alt1+= 500.0;
        alt2+= 500.0;
        alt3+= 500.0;
    }

    //_itemLabel1->setPos(0.0, _labelsDeltaY);
    //_itemLabel2->setPos(0.0, _labelsDeltaY + 75);
    //_itemLabel3->setPos(0.0, _labelsDeltaY + 150);

    if(alt1 > 0.0 && alt1 <= 100000.0) {
        //_itemLabel1->setVisible(true);
        //_itemLabel1->setPlainText(QString("%1").arg(alt1, 5, 'f', 0, QChar(' ')));
    } else {
        //_itemLabel1->setVisible(false);
    }

    if(alt2 > 0.0 && alt2 <= 100000.0) {
        //_itemLabel2->setVisible(true);
        //_itemLabel2->setPlainText(QString("%1").arg(alt2, 5, 'f', 0, QChar(' ')));
    } else {
        //_itemLabel2->setVisible(false);
    }

    if(alt3 > 0.0 && alt3 <= 100000.0) {
        //_itemLabel3->setVisible(true);
        //_itemLabel3->setPlainText(QString("%1").arg(alt3, 5, 'f', 0, QChar(' ')));
    } else {
        //_itemLabel3->setVisible(false);
    }
    /*
    if(_pressureMode == qfi_EADI::PressureMode::STD) {
        _itemPressure->setPlainText(QString("  STD  "));
    } else if(_pressureMode == qfi_EADI::PressureMode::MB) {
        _itemPressure->setPlainText(QString::number(_pressure, 'f', 0) + QString(" MB"));
    } else if(_pressureMode == qfi_EADI::PressureMode::IN) {
        _itemPressure->setPlainText(QString::number(_pressure, 'f', 2) + QString(" IN"));
    }
    */
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
