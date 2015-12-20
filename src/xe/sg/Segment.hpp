
#ifndef __EXENG_SCENEGRAPH_SEGMENT_HPP__
#define __EXENG_SCENEGRAPH_SEGMENT_HPP__

#include <xe/Vector.hpp>
#include <array>

namespace xe { namespace sg {
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

namespace xe { namespace sg {
    template<typename Type>
    Segment<Type>::Segment()  {}
    
    template<typename Type>
    Segment<Type>::Segment(const Vector<Type, 3> &p1, const Vector<Type, 3> &p2) {
        this->setPoint(0, p1);
        this->setPoint(2, p2);
    }
    
    template<typename Type>
    Type Segment<Type>::getLength() const {
        Type length = Type(0);
        
        for (int i=1; i<this->getPointCount(); ++i) {
            auto p1 = this->getPoint(i - 1);
            auto p2 = this->getPoint(i - 0);
            
            length += (p2 - p1).getLength();
        }
        
        return length;
    }
    
    template<typename Type>
    const Vector<Type, 3>& Segment<Type>::operator[](int index) const {
        return this->points[index];
    }
    
    template<typename Type>
    Vector<Type, 3>& Segment<Type>::operator[](int index) {
        return this->points[index];
    }
    
    template<typename Type>
    void Segment<Type>::setPoint(int index, const Vector<Type, 3>& point) {
        this->points[index] = point;
    }
    
    template<typename Type> 
    Vector<Type, 3> Segment<Type>::getPoint(int index) const {
        return this->points[index];
    }

    template<typename Type> 
    Vector<Type, 3> Segment<Type>::getPointAt(Type t) const {
        return Vector<Type, 3>();
    }
    
    template<typename Type>
    int Segment<Type>::getPointCount() const {
        return this->points.size();
    }
}}



#endif  // __EXENG_SCENEGRAPH_SEGMENT_HPP__
