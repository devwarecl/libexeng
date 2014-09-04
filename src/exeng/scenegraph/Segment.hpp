
#ifndef __EXENG_SCENEGRAPH_SEGMENT_HPP__
#define __EXENG_SCENEGRAPH_SEGMENT_HPP__

#include <exeng/Vector.hpp>
#include <array>

namespace exeng { namespace scenegraph {

    /**
     * @brief Line segment
     */
    template<typename Type>    
    struct Segment {
    public:
        Segment();
        Segment(const Vector<Type, 3> &p1, const Vector<Type, 3> &p2);
    
        /**
         * @brief Compute total length.
         */
        Type getLength() const;

        const Vector<Type, 3>& operator[](int index) const;
        Vector<Type, 3>& operator[](int index);
    
        /**
         * @brief Get the point of the line segment at specified index.
         */
        Vector<Type, 3> getPoint(int index) const;
    
        /**
         * @brief Get the point of the line segment at specified index.
         */
        void setPoint(int index, const Vector<Type, 3>& point);
        
        /**
         * @brief Interpolate across the line segment for point at parametric coordinate 't'.
         */
        Vector<Type, 3> getPointAt(Type t) const;
    
        /**
         * @brief Get the current point count of the segment
         */
        int getPointCount() const;
        
    private:
        std::array<Vector<Type, 3>, 2> points;
    };

    typedef Segment<float> Segmentf;
    typedef Segment<double> Segmentd;
    typedef Segment<int> Segmenti;

}}

#include "Segment.inl"

#endif  // __EXENG_SCENEGRAPH_SEGMENT_HPP__
