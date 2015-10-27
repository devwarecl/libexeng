//
//#ifndef __RAYTRACER_TRACERS_TRACERFACTORY_HPP__
//#define __RAYTRACER_TRACERS_TRACERFACTORY_HPP__
//
//#include <memory>
//#include <list>
//
//#include "Tracer.hpp"
//#include "TracerCreator.hpp"
//
//namespace raytracer { namespace tracers {
//	class TracerFactory {
//	public:
//		TracerFactory();
//		~TracerFactory();
//
//		std::unique_ptr<Tracer> createTracer(exeng::scenegraph::Scene *scene, raytracer::samplers::Sampler *sampler);
//	private:
//		std::list<std::unique_ptr<TracerCreator>> tracerCreators;
//	};
//}}
//
//#endif	// __RAYTRACER_TRACERS_TRACERFACTORY_HPP__
