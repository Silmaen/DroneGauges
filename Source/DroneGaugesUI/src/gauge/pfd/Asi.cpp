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

namespace dg::ui::gauge::pfd {

void ASI::init(double scale) {
    DisplayElement::init(scale);
    _itemBack= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_asi_back.svg");
    _itemBack->setCacheMode(QGraphicsItem::NoCache);
    _itemBack->setZValue(70);
    _itemBack->setScale(getScale());
    _itemBack->setTransformOriginPoint(backpos);
    _itemBack->setPos(-backpos + getScale() * getPosition());
    _itemBack->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    getScene()->addItem(_itemBack);

    _itemScale1= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_asi_scale.svg", _itemBack);
    _itemScale1->setCacheMode(QGraphicsItem::NoCache);
    _itemScale1->setZValue(80);
    _itemScale1->setTransformOriginPoint(scale1Pos);
    _itemScale1->setPos(-scale1Pos);

    _itemLabels.clear();
    for(uint8_t i= 0; i < nbLabels; ++i) {
        _itemLabels.emplace_back(new QGraphicsTextItem(QString("999"), _itemBack));
        _itemLabels.back()->setCacheMode(QGraphicsItem::NoCache);
        _itemLabels.back()->setZValue(90);
        _itemLabels.back()->setDefaultTextColor(white);
        _itemLabels.back()->setFont(Font::small());
    }

    _itemFrame= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_asi_frame.svg");
    _itemFrame->setCacheMode(QGraphicsItem::NoCache);
    _itemFrame->setZValue(110);
    _itemFrame->setScale(getScale());
    _itemFrame->setTransformOriginPoint(framePos);
    _itemFrame->setPos(-framePos + getScale() * getPosition());
    getScene()->addItem(_itemFrame);

    _itemVfe= new QGraphicsRectItem(_vfePos.x(), _vfePos.y(), _vfeWidth, 0, _itemBack);
    _itemVfe->setBrush(_vfeBrush);
    _itemVfe->setPen(_vfePen);

    _itemVne= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_asi_vne.svg", _itemBack);
    _itemVne->setCacheMode(QGraphicsItem::NoCache);
    _itemVne->setZValue(90);
    _itemVne->setTransformOriginPoint(vnePos);
    _itemVne->setPos(-vnePos);

    _itemAirspeed= new QGraphicsTextItem(QString("000"), _itemFrame);
    _itemAirspeed->setCacheMode(QGraphicsItem::NoCache);
    _itemAirspeed->setZValue(120);
    _itemAirspeed->setTextInteractionFlags(Qt::NoTextInteraction);
    _itemAirspeed->setDefaultTextColor(white);
    _itemAirspeed->setFont(Font::medium());
    _itemAirspeed->setPos(airSpeedPos);
}

void ASI::update(double scale) {
    DisplayElement::update(scale);

    _itemAirspeed->setPlainText(QString("%1").arg(_airspeed, 3, 'f', 0, QChar(' ')));

    double _scale1DeltaY= _originalPixPerSpd * _airspeed;
    double _labelsDeltaY= _scale1DeltaY;
    while(_scale1DeltaY > scaleSize) _scale1DeltaY-= scaleSize / 2.0;
    QPointF scalePosT{0, _scale1DeltaY};
    _itemScale1->setPos(itemPos - scale1Pos + scalePosT);

    int tmp             = floor(_airspeed + 0.5);
    int velLabelInterval= scaleSize / 4.0 / _originalPixPerSpd;

    int spd= tmp - (tmp % velLabelInterval);

    std::vector<double> spds;
    for(uint8_t i= 0; i < nbLabels; ++i) {
        spds.push_back(static_cast<double>(spd) + (nbLabels / 2 - i) * velLabelInterval);
    }

    while(_labelsDeltaY > velLabelInterval) {
        _labelsDeltaY= _labelsDeltaY - scaleSize / 4.0;
    }

    if(_labelsDeltaY < 0.0 && _airspeed > spd) {
        std::for_each(spds.begin(), spds.end(), [&velLabelInterval](double& d) { d+= velLabelInterval; });
    }

    for(uint8_t i= 0; i < nbLabels; ++i) {
        _itemLabels[i]->setPos(itemPos.x(), itemPos.y() + _labelsDeltaY + i * scaleSize / 4.0);
    }

    for(uint8_t i= 0; i < nbLabels; ++i) {
        if(spds[i] >= -500.0 && spds[i] <= 500.0) {
            _itemLabels[i]->setVisible(true);
            _itemLabels[i]->setPlainText(QString("%1").arg(spds[i], 3, 'f', 0, QChar(' ')));
        } else {
            _itemLabels[i]->setVisible(false);
        }
    }

    double height= _originalPixPerSpd * (_vfe - _airspeed + 58.5);
    _itemVfe->setRect(_vfePos.x(), _vfePos.y() - height, _vfeWidth, height);
    QPointF off= {0, _originalPixPerSpd * (_airspeed - _vne)};
    _itemVne->setPos(-vnePos + off);
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
