

#define EXENG_DATA_TYPE_TRAITS(KeyEnum, BasicType)              \
    template<> struct DataTypeTraits<BasicType> {               \
        typedef BasicType Type;                                 \
        enum { Enum=static_cast<int>(DataType::KeyEnum) };      \
    }

namespace exeng {
    inline DataType::DataType() {
        this->value = 0;
    }
    
    
    inline DataType::DataType(uint16_t value) {
        this->value = value;
    }
    
    
    inline DataType::DataType(bool sign, DataType::Kind kind, int size) {
        this->value = 0;
        this->setSize(size);
        this->setSign(sign);
        this->setKind(kind);
    }
    
    
    inline DataType::Kind DataType::getKind() const {
        return static_cast<DataType::Kind>(this->kind);
    }
    
    
    inline void DataType::setKind(DataType::Kind kind) {
        this->kind = static_cast<int>(kind);
    }

    
    inline bool DataType::getSign() const {
        return this->value == 1;
    }
    
    
    inline void DataType::setSign(bool value) {
        if (value == true) {
            this->sign = 1;
        } else {
            this->sign = 0;
        }
    }
    
    
    inline int DataType::getSize() const {
        //! FIXME: Reimplement this based on bit operations instead.
        int size = 0;
        
        switch(this->size) {
            case 1: size = 1; break;
            case 2: size = 2; break;
            case 3: size = 4; break;
            case 4: size = 8; break;
            default: size = 0; break;
        }
        
        return size;
    }
    
    
    inline void DataType::setSize(int size) {
        //! FIXME: Reimplement this based on bit operations instead.
        int binSize = 0;
        
        switch(size) {
            case 1: binSize = 1; break;
            case 2: binSize = 2; break;
            case 4: binSize = 3; break;
            case 8: binSize = 4; break;
            default: binSize = 0; break;
        }
        
        this->size = binSize;
    }
    
    
    inline bool DataType::isValid() const {
        bool validReserved = this->__unused0 == 0 && this->__unused1 == 0;
        bool validSize = this->size != 0;
        bool validFloat = (this->sign == true && this->getKind() == DataType::Float);
        bool validInt = (this->getKind() == DataType::Int);
        
        return validReserved && validSize && (validFloat || validInt);
    }
    
    
    inline bool DataType::operator== (const DataType &other) const {
        return this->value == other.value;
    }
    
    
    inline bool DataType::operator!= (const DataType &other) const {
        return this->value != other.value;
    }
    
    
    inline bool DataType::operator> (const DataType &other) const {
        return this->size > other.size;
    }
    
    
    inline bool DataType::operator< (const DataType &other) const {
        return this->size < other.size;
    }
    
    
    inline bool DataType::operator>= (const DataType &other) const {
        return (*this == other) || (*this > other);
    }
    
    
    inline bool DataType::operator<= (const DataType &other) const {
        return (*this == other) || (*this < other);
    }
    
    
    inline uint16_t DataType::getValue() const {
        return this->value;
    }
    
    
    inline void DataType::setValue(uint16_t value) {
        this->value = value;
    }
    
    
    EXENG_DATA_TYPE_TRAITS(DataType::UInt8,  uint8_t);
    EXENG_DATA_TYPE_TRAITS(DataType::UInt16, uint16_t);
    EXENG_DATA_TYPE_TRAITS(DataType::UInt32, uint32_t);
    EXENG_DATA_TYPE_TRAITS(DataType::UInt64, uint64_t);
    EXENG_DATA_TYPE_TRAITS(DataType::Int8,  int8_t);
    EXENG_DATA_TYPE_TRAITS(DataType::Int16, int16_t);
    EXENG_DATA_TYPE_TRAITS(DataType::Int32, int32_t);
    EXENG_DATA_TYPE_TRAITS(DataType::Int64, int64_t);
    EXENG_DATA_TYPE_TRAITS(DataType::Float32, float);
    EXENG_DATA_TYPE_TRAITS(DataType::Float64, double);
}


#undef EXENG_DATA_TYPE_TRAITS