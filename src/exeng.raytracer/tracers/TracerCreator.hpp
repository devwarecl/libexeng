//
//#ifndef __RAYTRACER_TRACERS_TRACERCREATOR_HPP__
//#define __RAYTRACER_TRACERS_TRACERCREATOR_HPP__
//
//#include "Tracer.hpp"
//
//namespace raytracer { namespace tracers {
//
//	class TracerCreator {
//	public:
//		virtual ~TracerCreator() {}
//		virtual Tracer* createTracer() = 0;
//	};
//
//	template<typename TracerImpl>
//	class TracerCreatorImpl : public TracerCreator {
//	public:
//		virtual TracerImpl* createTracer() override {
//			return new TracerImpl();
//		}
//	};
//}}
//
//#endif	// __RAYTRACER_TRACERS_TRACERCREATOR_HPP__
