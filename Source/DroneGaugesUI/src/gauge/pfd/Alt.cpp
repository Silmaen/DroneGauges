/**
 * @file Alt.cpp
 * @author damien.lachouette 
 * @date 23/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "gauge/pfd/Alt.h"
#include "base/base.h"
#include "gauge/pfd/color.h"
#include "gauge/pfd/font.h"

namespace dg::ui::gauge::pfd {

ALT::ALT(QGraphicsScene* scene):
    _scene{scene} {}

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
    _itemScale1->setPos(-scale1Pos);

    _itemLabels.clear();
    for(uint8_t i= 0; i < nbLabels; ++i) {
        _itemLabels.emplace_back(new QGraphicsTextItem(QString("999"), _itemBack));
        _itemLabels.back()->setCacheMode(QGraphicsItem::NoCache);
        _itemLabels.back()->setZValue(90);
        _itemLabels.back()->setDefaultTextColor(white);
        _itemLabels.back()->setFont(Font::small());
    }

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

    _itemScale= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_vsi_scale.svg");
    _itemScale->setCacheMode(QGraphicsItem::NoCache);
    _itemScale->setZValue(70);
    _itemScale->setScale(_scale);
    _itemScale->setTransformOriginPoint(scalePos);
    _itemScale->setPos(-scalePos + _scale * (position + scaleOffset));
    _scene->addItem(_itemScale);

    _itemMarker= new QGraphicsRectItem(_originalMarkerPos.x(), _originalMarkerPos.y(), _originalMarkerWidth, 0, _itemScale);
    _itemMarker->setBrush(_markerBrush);
    _itemMarker->setPen(_markerPen);
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
    std::vector<double> alts;
    for(uint8_t i= 0; i < nbLabels; ++i) {
        alts.push_back(static_cast<double>(alt) + (nbLabels / 2 - i) * altLabelInterval);
    }

    while(_labelsDeltaY > altLabelInterval) {
        _labelsDeltaY= _labelsDeltaY - scaleSize / 2.0;
    }

    if(_labelsDeltaY < 0.0 && _altitude > alt) {
        std::for_each(alts.begin(), alts.end(), [&altLabelInterval](double& d) { d+= altLabelInterval; });
    }

    for(uint8_t i= 0; i < nbLabels; ++i) {
        _itemLabels[i]->setPos(itemPos.x(), itemPos.y() + _labelsDeltaY + i * scaleSize / 2.0);
    }
    for(uint8_t i= 0; i < nbLabels; ++i) {
        if(alts[i] > 0.0 && alts[i] <= 100000.0) {
            _itemLabels[i]->setVisible(true);
            _itemLabels[i]->setPlainText(QString("%1").arg(alts[i], 3, 'f', 0, QChar(' ')));
        } else {
            _itemLabels[i]->setVisible(false);
        }
    }
}

void ALT::updateVertVelView() {

    double climbRateAbs= fabs(_verticalVelocity);
    double arrowDeltaY = 0.0;
    if(climbRateAbs <= 1.0) {
        arrowDeltaY= _originalPixPerSpd1 * climbRateAbs;
    } else if(climbRateAbs <= 2.0) {
        arrowDeltaY= _originalPixPerSpd1 + _originalPixPerSpd2 * (climbRateAbs - 1.0);
    } else {
        arrowDeltaY= _originalPixPerSpd1 + _originalPixPerSpd2 + _originalPixPerSpd4 * (climbRateAbs - 2.0);
    }

    if(_verticalVelocity > 0.0) {
        _itemMarker->setRect(_originalMarkerPos.x(),
                             _originalMarkerPos.y() - arrowDeltaY,
                             _originalMarkerWidth,
                             arrowDeltaY);
    } else {
        _itemMarker->setRect(_originalMarkerPos.x(),
                             _originalMarkerPos.y(),
                             _originalMarkerWidth,
                             arrowDeltaY);
    }
}

void ALT::setAltitude(double altitude) {
    _altitude= altitude;
}

void ALT::setVerticalVelocity(double verticalVelocity) {
    _verticalVelocity= core::base::clamp(verticalVelocity, -6.8, 6.8);
}

}// namespace dg::ui::gauge::pfd
