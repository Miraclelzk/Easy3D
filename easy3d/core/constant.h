/********************************************************************
 * Copyright (C) 2015 Liangliang Nan <liangliang.nan@gmail.com>
 * https://3d.bk.tudelft.nl/liangliang/
 *
 * This file is part of Easy3D. If it is useful in your research/work,
 * I would be grateful if you show your appreciation by citing it:
 * ------------------------------------------------------------------
 *      Liangliang Nan.
 *      Easy3D: a lightweight, easy-to-use, and efficient C++ library
 *      for processing and rendering 3D data.
 *      Journal of Open Source Software, 6(64), 3255, 2021.
 * ------------------------------------------------------------------
 *
 * Easy3D is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License Version 3
 * as published by the Free Software Foundation.
 *
 * Easy3D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 ********************************************************************/

#ifndef EASY3D_CORE_CONSTANT_H
#define EASY3D_CORE_CONSTANT_H

#include <cfloat>
#include <climits>
#include <cmath>


namespace easy3d {

#ifndef M_PI
#define M_PI			3.14159265358979323846264338327950288
#endif


    /**
     * \brief Function returning minimum representable value for a given type.
     * \tparam FT The floating point type.
     * \return The minimum representable value.
     */
    template <typename FT> FT min();
    /**
     * \brief Function returning maximum representable value for a given type.
     * \tparam FT The floating point type.
     * \return The maximum representable value.
     */
    template <typename FT> FT max();

    // Template specializations for int, float, and double

    /**
     * \brief Function returning \c min for int type numbers.
     * \return The minimum representable value for int.
     */
    template <> inline int     min<int>()    { return INT_MIN; }
    /**
     * \brief Function returning \c max for int type numbers.
     * \return The maximum representable value for int.
     */
    template <> inline int     max<int>()    { return INT_MAX; }
    /**
     * \brief Function returning \c min for float type numbers.
     * \return The minimum representable value for float.
     */
    template <> inline float   min<float>()  { return FLT_MIN; }
    /**
     * \brief Function returning \c max for float type numbers.
     * \return The maximum representable value for float.
     */
    template <> inline float   max<float>()  { return FLT_MAX; }
    /**
     * \brief Function returning \c min for double type numbers.
     * \return The minimum representable value for double.
     */
    template <> inline double  min<double>() { return DBL_MIN; }
    /**
     * \brief Function returning \c max for double type numbers.
     * \return The maximum representable value for double.
     */
    template <> inline double  max<double>() { return DBL_MAX; }

    /**
     * \brief Function returning the epsilon value for a given type.
     * \tparam FT The floating point type.
     * \return The epsilon value.
     */
    template <typename FT> FT epsilon();
    /**
     * \brief Function returning the squared epsilon value for a given type.
     * \tparam FT The floating point type.
     * \return The squared epsilon value.
     */
    template <typename FT> FT epsilon_sqr();

    // Template specializations for float and double

    /**
     * \brief Function returning \c epsilon for float type numbers.
     * \return The epsilon value for float.
     */
    template <> inline float  epsilon<float>()      { return 1.0e-6f;  }
    /**
     * \brief Function returning \c squared epsilon for float type numbers.
     * \return The squared epsilon value for float.
     */
    template <> inline float  epsilon_sqr<float>()  { return 1.0e-12f; }
    /**
     * \brief Function returning \c epsilon for double type numbers.
     * \return The epsilon value for double.
     */
    template <> inline double epsilon<double>()     { return 1.0e-12;  }
    /**
     * \brief Function returning \c squared epsilon for double type numbers.
     * \return The squared epsilon value for double.
     */
    template <> inline double epsilon_sqr<double>() { return 1.0e-24;  }


    /**
     * \brief Tests if two values are Epsilon equal.
     * \tparam FT The floating point type.
     * \param x The first value.
     * \param y The second value.
     * \param eps The epsilon value.
     * \return True if the values are Epsilon equal, false otherwise.
     */
    template<typename FT>
    bool epsilon_equal(FT const& x, FT const& y, FT const& eps) { return std::abs(x - y) < eps; }

    /**
     * \brief Tests if two values are not Epsilon equal.
     * \tparam FT The floating point type.
     * \param x The first value.
     * \param y The second value.
     * \param eps The epsilon value.
     * \return True if the values are not Epsilon equal, false otherwise.
     */
    template<typename FT>
    bool epsilon_not_equal(FT const& x, FT const& y, FT const& eps) { return std::abs(x - y) >= eps; }

}


#endif // EASY3D_CORE_CONSTANT_H
