#pragma once

#ifndef __xe_sg_transformationstack_hpp__
#define __xe_sg_transformationstack_hpp__

#include <stack>
#include <xe/Matrix.hpp>

namespace xe { namespace sg {
	class TransformationStack {
	public:
		void reset(const Matrix4f& m);

		void push(const Matrix4f& m);

		void pop();

		Matrix4f top() const;

	public:
		std::stack<Matrix4f> stack;
	};

	inline void TransformationStack::reset(const Matrix4f& m) {
		this->stack = std::stack<Matrix4f>();
		this->stack.push(m);
	}

	inline void TransformationStack::push(const Matrix4f& m) {
		Matrix4f current = this->top();
		this->stack.push(current * m);
	}

	inline void TransformationStack::pop() {
		this->stack.pop();
	}

	inline Matrix4f TransformationStack::top() const {
		return this->stack.top();
	}
}}

#endif 