/**
 * @file DisplayElement.h
 * @author damien.lachouette 
 * @date 25/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <utility>

namespace dg::ui::gauge::pfd {

/**
 * @brief Class DisplayElement
 */
class DisplayElement {
public:
    /**
     * @brief Base Constructor
     * @param scene The scene where to draw
     */
    explicit DisplayElement(std::shared_ptr<QGraphicsScene> scene, const QPointF& position= {0, 0}, const double& internalScale= 1.0);

    /**
     * @brief Destructor
     */
    virtual ~DisplayElement();
    /**
     * @brief Initialization of the display
     * @param scale The initial scal of the view
     */
    virtual void init(double scale) {
        _scale= scale;
    }

    /**
     * @brief Update the view port
     * @param scale The update scale of the view
     */
    virtual void update(double scale) {
        _scale= scale;
    }

    /**
     * @brief Get the scene where to draw
     * @return The drawing scene
     */
    auto getScene() { return _scene; }

    /**
     * @brief Definition of the internal scale of this element
     * @param scale The new internal scale
     */
    void setInternalScale(const double& scale) {
        _internalScale= scale;
        init(_scale);
    }

    /**
     * @brief Get the overall scale of this element
     * @return The overall scale
     */
    double getScale() const { return _scale * _internalScale; }

    /**
     * @brief Definition of the position
     * @param position The new position
     */
    void setPosition(const QPointF& position) {
        _position= position;
        init(_scale);
    }

    /**
     * @brief Get the position of this element
     * @return The position of this element
     */
    const QPointF& getPosition() const { return _position; }

private:
    /// The scene where to draw
    std::shared_ptr<QGraphicsScene> _scene;
    /// The Global Scale of the display
    double _scale= 1.0;
    /// The position of this Element
    QPointF _position= {0, 0};
    /// The internal scale
    double _internalScale= 1.0;
};

}// namespace dg::ui::gauge::pfd
