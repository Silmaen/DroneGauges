/**
 * @file font.h
 * @author argawaen
 * @date 23/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include <QFont>

namespace dg::ui::gauge::pfd {
/**
 * @brief Fonts class.
 */
class Font {
public:
    static inline const QFont& small() {
        if(!_inited) init();
        return _small;
    }

    static inline const QFont& xsmall() {
        if(!_inited) init();
        return _xsmall;
    }

    static inline const QFont& medium() {
        if(!_inited) init();
        return _medium;
    }

private:
    static QFont _xsmall;
    static QFont _small;
    static QFont _medium;

    static bool _inited;

    static void init();
};
}// namespace dg::ui::gauge::pfd
