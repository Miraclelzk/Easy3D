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

#ifndef EASY3D_CORE_SEGMENT_H
#define EASY3D_CORE_SEGMENT_H


#include <algorithm>

#include <easy3d/core/vec.h>
#include <easy3d/core/line.h>


namespace easy3d {

    /**
     * \brief A generic segmentation representation, which supports both 2D and 3D line segments.
     * \tparam DIM The dimension of the space (2 or 3).
     * \tparam FT The scalar type for segment coordinates.
     * \class GenericSegment easy3d/core/segment.h
     */
    template <int DIM, typename FT>
    class GenericSegment {
    public:
        typedef Vec<DIM, FT>			Point;      ///< The type of the point.
        typedef Vec<DIM, FT>			Vector;     ///< The type of the vector.
        typedef GenericLine<DIM, FT>	Line;       ///< The type of the line.
        typedef GenericSegment<DIM, FT> thisclass;  ///< The type of this class.

    public:
        /**
         * \brief Constructs a line segment from its two end points \p s and \p t.
         * \param s The source end point.
         * \param t The target end point.
         */
        GenericSegment(const Point& s, const Point& t);
        /**
         * \brief Default constructor.
         */
        GenericSegment() = default;

        /**
         * \brief Returns the source end point of this line segment.
         * \return The source end point.
         */
        const Point& source() const { return s_; }
        /**
         * \brief Returns the target end point of this line segment.
         * \return The target end point.
         */
        const Point& target() const { return t_; }

        /**
         * \brief Sets/Changes the source end point of this line segment.
         * \param s The new source end point.
         */
        void  set_source(const Point& s) { s_ = s; }
        /**
         * \brief Sets/Changes the target end point of this line segment.
         * \param t The new target end point.
         */
        void  set_target(const Point& t) { t_ = t; }

        /**
         * \brief Returns the supporting line of this line segment.
         * \return The supporting line.
         */
        Line  supporting_line() const { return Line::from_two_points(s_, t_); }

        /**
         * \brief Returns a vector originating from source() and pointing to target().
         * \return The vector from source to target.
         */
        Vector to_vector() const { return t_ - s_; }

        /**
         * \brief Returns the projection of a point \p p on the supporting line of this segment.
         * \param p The point to project.
         * \return The projected point on the supporting line.
         */
        Point  projection(const Point &p) const;

        /**
         * \brief Tests if the projection of a point \p p is within the two end points of this segment.
         * \param p The point to test.
         * \return \c true if the projection is within the segment, \c false otherwise.
         */
        bool   projected_inside(const Point& p) const;

        /**
         * \brief Returns the squared distance of a point \p p to this segment.
         * \param p The point to compute the distance to.
         * \return The squared distance to the segment. The return the value is the min of the following:
         *      - the squared distance between \p p and the supporting_line() of this segment;
         *      - the squared distance between \p p and the source() of this segment;
         *      - the squared distance between \p p and the target() of this segment.
         */
        FT squared_distance(const Point &p) const;

    private:
        Point s_;
        Point t_;
    };



    template<int DIM, typename FT> inline
    GenericSegment<DIM, FT>::GenericSegment(const Point& s, const Point& t) : s_(s), t_(t) {
        DLOG_IF(distance2(s, t) < 1e-15, ERROR) << "degenerate segment constructed from 2 points:"
                                                << "\t(" << s << ")"
                                                << "\t(" << t << ")";
    }


    template<int DIM, typename FT> inline
    typename GenericSegment<DIM, FT>::Point  GenericSegment<DIM, FT>::projection(const Point &p) const {
        Vector dir = normalize(t_ - s_);
        return (s_ + dir * dot(p - s_, dir));
    }


    template<int DIM, typename FT> inline
    bool GenericSegment<DIM, FT>::projected_inside(const Point& p) const {
        return (dot(s_ - p, t_ - p) < 0);
    }


    template<int DIM, typename FT> inline
    FT GenericSegment<DIM, FT>::squared_distance(const Point &p) const {
        if (projected_inside(p))
            return distance2(projection(p), p);
        else {
            FT ds = distance2(s_, p);
            FT dt = distance2(t_, p);
            return std::min(ds, dt);
        }
    }

}


#endif  // EASY3D_CORE_SEGMENT_H
