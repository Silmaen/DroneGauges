/**
 * @file PrimaryFlightDisplay.h
 * @author Silmean
 * @date 20/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsSvgItem>
#include <QGraphicsView>

namespace dg::ui::gauge {

namespace pfd {
class ADI;
}

/**
 * @brief Base Object for flight data display
 */
class PrimaryFlightDisplay: public QGraphicsView {
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent Parent Widget
     */
    explicit PrimaryFlightDisplay(QWidget* parent= nullptr);
    /**
     * @brief Destructor
     */
    ~PrimaryFlightDisplay() override;

    /** Re-initiates widget. */
    void reinit();

    /** Refreshes (redraws) widget. */
    void redraw();
public slots:

    /**
     * @brief Defines internal pitch.
     */
    void setPitch(int);
    /**
     * @brief Defines the internal yaw.
     */
    void setYaw(int);
    /**
     * @brief Defines the internal roll.
     */
    void setRoll(int);

protected:
    /** */
    void resizeEvent(QResizeEvent* event) override;

private:
    void init();

    void updateScale();
    void updateView();

    QGraphicsScene* _scene= nullptr;///< graphics scene
    pfd::ADI* adi         = nullptr;

    double _scaleX  = 1.0;
    double _scaleY  = 1.0;
    double _scaleMax= 1.0;

    const int _originalHeight      = 120;
    const int _originalWidth       = 120;
};

}// namespace dg::ui::gauge
