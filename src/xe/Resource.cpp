///**
// * @file Resource.cpp
// * @brief Implements some of the methods of the Resource abstact class.
// */
//
//
///*
// * Copyright (c) 2013 Felipe Apablaza.
// *
// * The license and distribution terms for this file may be
// * found in the file LICENSE in this distribution.
// */
//
//#include "Resource.hpp"
//#include <xe/Exception.hpp>
//
//namespace xe {
//    Resource::~Resource() 
//	{
//		this->release();
//	}
//
//    void Resource::release()  {}
//    
//    void Resource::restore() {}
//
//	int Resource::getHandle() const 
//	{
//		return reinterpret_cast<int>(this);
//	}
//
//    ResourceStatus::Flags Resource::getResourceStatus() const
//	{
//		return ResourceStatus::Ready;
//	}
//}
