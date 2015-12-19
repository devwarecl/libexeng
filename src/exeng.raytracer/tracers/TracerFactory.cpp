//
//#include <list>
//#include "TracerFactory.hpp"
//
//#include "SoftwareTracer.hpp"
//#include "HardwareTracer.hpp"
//#include "MultiHardwareTracer.hpp"
//
//namespace raytracer { namespace tracers {
//
//	using namespace raytracer::samplers;
//	using namespace xe::sg;
//
//	TracerFactory::TracerFactory()  {}
//	TracerFactory::~TracerFactory() {}
//
//	std::unique_ptr<Tracer> TracerFactory::createTracer(Scene *scene, Sampler *sampler)
//	{
//		return std::unique_ptr<MultiHardwareTracer>(new MultiHardwareTracer(scene, nullptr));
//
//		/*
//		for (std::unique_ptr<TracerCreator> &tracerCreator : this->tracerCreators) {
//			return tracerCreator->createTracer();
//		}
//		*/
//	}
//}}
