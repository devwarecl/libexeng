

namespace exeng { namespace scenegraph {
    template<typename Type>
    Segment<Type>::Segment()  {}
    
    
    template<typename Type>
    Segment<Type>::Segment(const exeng::math::TVector<Type, 3> &p1, const exeng::math::TVector<Type, 3> &p2) {
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
    const exeng::math::TVector<Type, 3>& Segment<Type>::operator[](int index) const {
        return this->points[index];
    }
    
    
    template<typename Type>
    exeng::math::TVector<Type, 3>& Segment<Type>::operator[](int index) {
        return this->points[index];
    }
    
    
    template<typename Type>
    void Segment<Type>::setPoint(int index, const exeng::math::TVector<Type, 3>& point) {
        this->points[index] = point;
    }
    
    
    template<typename Type> 
    exeng::math::TVector<Type, 3> Segment<Type>::getPoint(int index) const {
        return this->points[index];
    }

    
    template<typename Type> 
    exeng::math::TVector<Type, 3> Segment<Type>::getPointAt(Type t) const {
        return exeng::math::TVector<Type, 3>();
    }
    
    
    template<typename Type>
    int Segment<Type>::getPointCount() const {
        return this->points.size();
    }
}}
