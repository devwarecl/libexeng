
#include <list>
#include "TracerFactory.hpp"

namespace raytracer { namespace tracers {

	TracerFactory::TracerFactory() 
	{

	}

	TracerFactory::~TracerFactory() {}

	Tracer* TracerFactory::createTracer()
	{
		for (std::unique_ptr<TracerCreator> &tracerCreator : this->tracerCreators) {
			return tracerCreator->createTracer();
		}
	}
}}
