
#ifndef __RAYTRACER_SAMPLERS_JITTEREDSAMPLER_HPP__
#define __RAYTRACER_SAMPLERS_JITTEREDSAMPLER_HPP__

#include "Sampler.hpp"

namespace raytracer { namespace samplers {

	class JitteredSampler : public Sampler {
	public:
		JitteredSampler(int sampleCount);
    
		virtual void generateSamples();
	};

}}

#endif  //__RAYTRACER_JITTEREDSAMPLER_HPP__

