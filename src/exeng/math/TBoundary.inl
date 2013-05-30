/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

namespace exeng {
    namespace math {
        template<typename Type, int Dimension>
        TBoundary<Type, Dimension>::TBoundary() { }
        

        template<typename Type, int Dimension>
        TBoundary<Type, Dimension>::TBoundary(const TVector<Type, Dimension> &minPoint, const TVector<Type, Dimension> &maxPoint) {
            this->set(minPoint, maxPoint);
        }
        
        
        template<typename Type, int Dimension>
        TBoundary<Type, Dimension>::TBoundary(Type initialSize) {
            this->set(initialSize);
        }
        
        
        template<typename Type, int Dimension>
        TBoundary<Type, Dimension>::TBoundary(const TSize<Type, Dimension>& size) {
            this->set(size);
        }
        
        
        template<typename Type, int Dimension>
        TBoundary<Type, Dimension>::TBoundary(const TVector<Type, Dimension>& minPoint, const TSize<Type, Dimension>& size) {
            this->set(minPoint, size);
        }
        
        
        template<typename Type, int Dimension>
        void TBoundary<Type, Dimension>::set(Type initialSize) {
            this->edges[Min].set(static_cast<Type>(0));
            this->edges[Max].set(initialSize);
        }
        
        
        template<typename Type, int Dimension>
        void TBoundary<Type, Dimension>::set(const TSize<Type, Dimension> &size) {
            this->edges[Min].set(static_cast<Type>(0));
            this->edges[Max].set(size.getPtr());
        }
        
        
        template<typename Type, int Dimension>
        void TBoundary<Type, Dimension>::set(const TVector<Type, Dimension> &minPoint, const TSize<Type, Dimension> &size) {
            this->edges[Min] = minPoint;
            this->edges[Max] = minPoint + TVector<Type, Dimension>(size.getPtr());
        }
        
        
        template<typename Type, int Dimension>
        void TBoundary<Type, Dimension>::set(const TVector<Type, Dimension> &minPoint, const TVector<Type, Dimension> &maxPoint) {
            this->edges[Min] = minPoint;
            this->edges[Max] = maxPoint;
        }
        

        template<typename Type, int Dimension>
        TVector<Type, Dimension> TBoundary<Type, Dimension>::getCenter() const {
            return this->edges[Min] + Vector(this->getSize()) / static_cast<Type>(2);
        }
        

        template<typename Type, int Dimension>
        void TBoundary<Type, Dimension>::setCenter(const TVector<Type, Dimension>& newCenter) {
            TVector<Type, Dimension> halfSize;
            
            halfSize = TVector<Type, Dimension>( this->getSize() ) / 2;
            
            this->set(-halfSize + newCenter, halfSize + newCenter);
        }
        
        
        //!Compute the hyper box size
        template<typename Type, int Dimension>
        TSize<Type, Dimension> TBoundary<Type, Dimension>::getSize() const {
			auto vsize = this->edges[Max] - this->edges[Min];

			return TSize<Type, Dimension>(vsize);
        }
        
        
        //!Return the specified edge
        template<typename Type, int Dimension>
        TVector<Type, Dimension> TBoundary<Type, Dimension>::getEdge(int PointIndex) const {
            switch (PointIndex) {
                case 0: 
                    return this->edges[Min];
                
                case TBoundary<Type, Dimension>::PointCount-1:
                    return this->edges[Max]; 
                
                default: {
                    TVector<Type, Dimension> Result;
                    int Remainder;
                    
                    //Fill the result...
                    for(int i=0; i<Dimension; ++i) {
                        Remainder = PointIndex % 2;
                        PointIndex /= 2;
                        
                        Result[i] = edges[Remainder][i];
                    }
                    
                    return Result;
                }
            }
        }
        
        
        template<typename Type, int Dimension>
        void TBoundary<Type, Dimension>::setSize(const TVector<Type, Dimension>& newSize) {
			this->set(newSize,  this->getCenter());
        }
        

        template<typename Type, int Dimension>
        bool TBoundary<Type, Dimension>::doIntersect(const TBoundary<Type, Dimension>& other) const {   
            for(int i=0; i<TBoundary<Type, Dimension>::PointCount; ++i) {
                if ( this->isInside( other.getEdge(i) ) ) {
                    return true;
				}
            }
            
            return false;
        }
        
        
        template<typename Type, int Dimension>
        bool TBoundary<Type, Dimension>::intersect(const TBoundary<Type, Dimension>& other) const {
            return this->doIntersect(other) || other.doIntersect(*this);
        }
        
        
        template<typename Type, int Dimension>
        bool TBoundary<Type, Dimension>::isInside(const TVector<Type, Dimension>& point) const {
            Type value;
            
            for(int i=0; i<Dimension; ++i) { 
                value = point[i];
                
                if ( value < this->edges[Min][i] ) {
                    return false;
				} else if ( value > this->edges[Max][i] ) {
                    return false;
				}
            }
            
            return true;
        }

        
        template<typename Type, int Dimension>
        void TBoundary<Type, Dimension>::expand(const TVector<Type, Dimension>& point) {
            this->edges[Min] = this->edges[Min].minimize(point);
            this->edges[Max] = this->edges[Max].maximize(point);
        }
        
        
        template<typename Type, int Dimension>
        void TBoundary<Type, Dimension>::expand(const TBoundary<Type, Dimension>& boundary) {
            this->expand(boundary.edges[0]);
            this->expand(boundary.edges[1]);
        }
        
        
        template<typename Type, int Dimension>
        std::ostream& operator<< (std::ostream &os, const TBoundary<Type, Dimension>& Boundary) {
            os << Boundary.getMin() << ", " << Boundary.getMax();
            
            return os;
        }
        
        template<typename Type, int Dimension>
        inline TVector<Type, Dimension> TBoundary<Type, Dimension>::getMin() const {
            return this->edges[0];
        }
        
        template<typename Type, int Dimension>
        inline TVector<Type, Dimension> TBoundary<Type, Dimension>::getMax() const {
            return this->edges[1];
        }
    }
}
