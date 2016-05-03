#pragma once

#ifndef __xe_dataformat_hpp__
#define __xe_dataformat_hpp__

#include <array>
#include <string>
#include <xe/DataType.hpp>

namespace xe {

    struct Attrib {
        std::string     name;
        DataType::Enum  type = DataType::Unknown;
        std::size_t     dim = 1;
        
        std::size_t getSize() const {
            return dim * DataType::getSize(type);
        }
    };

    template<typename DataAttrib, std::size_t AttribCount>
    struct DataFormat {
        std::array<DataAttrib, AttribCount> attribs;
        
        DataFormat() {}
        DataFormat(const std::array<DataAttrib, AttribCount> &attribs_) : attribs(attribs_) {}

        std::size_t getSize() const {
            std::size_t size = 0;

            for (const DataAttrib &attrib : attribs) {
                size += attrib.getSize();
            }

            return size;
        }

        constexpr std::size_t getCount() const {
            return AttribCount;
        }
    };
}

#endif
