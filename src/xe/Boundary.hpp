/**
 * @file Boundary.hpp
 * @brief Boundary class template definition
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __xe_boundary_hpp__
#define __xe_boundary_hpp__

#include <limits>
#include <cassert>
#include <xe/Vector.hpp>

namespace xe { 

	template<typename Type, int Size>
	class Boundary {
	private:
        template<int Base, int Exp> 
		struct Power {
            enum { Value = Base * Power<Base, Exp - 1>::Value };
        };
    
        template<int Base> 
		struct Power<Base, 0> {
            enum { Value = 1 };
        };

	public:
		enum { PointCount = Power<2, Size>::Value };

	public:
		Boundary() {
            minEdge = Vector<Type, Size>(std::numeric_limits<Type>::max());
            maxEdge = Vector<Type, Size>(-std::numeric_limits<Type>::max());		
		}

		Boundary(const Vector<Type, Size> &value1, const Vector<Type, Size> &value2) {
			expand(value1);
			expand(value2);
		}

		template<typename ContainerType>
		explicit Boundary(const ContainerType& values) {
			for (const auto &value : values) {
				expand(value);
			}
		}

		void expand(const Vector<Type, Size> &value) {
			minEdge = minimize(minEdge, value);
			maxEdge = maximize(maxEdge, value);
		}

		void expand(const Boundary<Type, Size>& other) {
			expand(other.getMinEdge());
			expand(other.getMaxEdge());
		}

		Vector<Type, Size> getMinEdge() const {
			return minEdge;
		}

		Vector<Type, Size> getMaxEdge() const {
			return maxEdge;
		}

		Vector<Type, Size> getSize() const {
			assert(isValid());

			return maxEdge - minEdge;
		}

		Vector<Type, Size> getCenter() const {
			assert(isValid());

			return minEdge + ((maxEdge - minEdge) / Type(2));
		}

		bool isValid() const {
			for (int i=0; i<Size; i++) {
				if (minEdge[i] > maxEdge[i]) {
					return false;
				}
			}

			return true;
		}

		bool isInside(const Vector<Type, Size> &point) const {
			assert(isValid());

			for(int i=0; i<Size; ++i) { 
				Type value = point[i];
        
				if (value < minEdge[i]) {
					return false;

				} else if (value > maxEdge[i]) {
					return false;
				}
			}
    
			return true;
		}

		bool operator== (const Boundary<Type, Size> &other) const {
			if (minEdge != other.minEdge) {
				return false;
			}

			if (maxEdge != other.maxEdge) {
				return false;
			}

			return true;
		}

		bool operator!= (const Boundary<Type, Size> &other) const {
			return ! (*this == other);
		}

		Vector<Type, Size> getEdge(int pointIndex) const {
			assert(isValid());

			const int LastPoint = Boundary<Type, Size>::PointCount-1;
			const Vector<Type, Size> *edges = &minEdge;

			switch (pointIndex) {
				case 0:         return edges[0];
				case LastPoint: return edges[1];
        
				default: {
					Vector<Type, Size> point;
					int remainder;
					
					for(int i=0; i<Size; ++i) {
						remainder = pointIndex % 2;
						pointIndex /= 2;
                
						point[i] = edges[remainder][i];
					}
            
					return point;
				}
			}
		}

		bool doIntersect(const Boundary<Type, Size>& other) const {   
			assert(isValid());

			for(int i=0; i<Boundary<Type, Size>::PointCount; ++i) {
				if (this->isInside(other.getEdge(i))) {
					return true;
				}
			}
    
			return false;
		}

		bool intersect(const Boundary<Type, Size>& other) const {
			assert(isValid());

			return this->doIntersect(other) || other.doIntersect(*this);
		}

	public:
		friend std::ostream& operator<< (std::ostream &os, const Boundary<Type, Size>& boundary) {
            return os << "Center: {" << boundary.getCenter() << "}, Size: {" << boundary.getSize() << "}";
        }
		
	private:
		Vector<Type, Size> minEdge;
		Vector<Type, Size> maxEdge;
	};

    typedef Boundary<float, 2> Rectf;
    typedef Boundary<int, 2> Recti;

	typedef Boundary<float, 3> Boxf;
    typedef Boundary<int, 3> Boxi;
}

#endif 
