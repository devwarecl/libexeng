
#include <stdexcept>
#include <boost/shared_array.hpp>

#include "Image.hpp"

struct exeng::graphics::Image::Private
{
    exeng::math::Vector3i size;
    exeng::graphics::ColorFormat::Type format;
    exeng::graphics::PixelType::Type type;
    boost::shared_array<UInt8> data;
            
    Private() : size(0, 0, 0), format(ColorFormat::Unknown), type(PixelType::Unknown)
    {
    }
};


namespace exeng
{
    namespace graphics
    {
        Image::Image() : Data(NULL)
        {
        }
        
        
        Image::Image(const math::Vector3i& size, ColorFormat::Type format, PixelType::Type type) : Data(NULL)
        {
            this->initialize(size, format, type);
        }
        
        
        Image::~Image()
        {
            if (this->Data)
            {
                delete this->Data;
                this->Data = NULL;    
            }
        }
        
        
        const void* Image::getPtr() const
        {
            assert(this->Data != NULL);
            return (void*)this->Data->data.get();
        }
        
        
        void* Image::getPtr()
        {
            assert(this->Data != NULL);
            return (void*)this->Data->data.get();
        }
        
        
        ColorFormat::Type Image::getFormat() const
        {
            assert(this->Data != NULL);
            return this->Data->format;
        }
        
        
        PixelType::Type Image::getType() const
        {
            assert(this->Data != NULL);
            return this->Data->type;
        }
        
        
        math::Vector3i Image::getSize() const
        {
            assert(this->Data != NULL);
            return this->Data->size;
        }
        
        
        void Image::initialize(const math::Vector3i& size, ColorFormat::Type format, PixelType::Type type)
        {
            UInt32 imageSize;
            
            //Validar el formato y el tipo de datos
            if (format == ColorFormat::Unknown)
                throw std::invalid_argument("'format' argument has an invalid value");
            
            if (type != PixelType::Integer )
                throw std::invalid_argument("Only integer image types supported by now");
            
            if (size.x <= 0 || size.y <= 0 || size.z != 0)
                throw std::invalid_argument("Only rectangular images supported");

            //Continuar con el proceso de inicializacion
            if (this->Data)
                delete this->Data;
            
            this->Data = new Image::Private();
            
            imageSize = ColorFormat::getPitch(format) * size.z * size.y;
            
            this->Data->format = format;
            this->Data->type = type;
            this->Data->size = size;
            
            this->Data->data.reset(new UInt8[imageSize]);
        }
        
        
        UInt32 Image::getPixel(const math::Vector2i& position) const
        {
            assert( this->Data != NULL );
            assert( position.x <  this->Data->size.x );
            assert( position.y <  this->Data->size.y );
            
            UInt32 *imagePointer = (UInt32*)( this->Data->data.get() );
            
            return imagePointer[ this->getOffset(position) ];
        }
        
            
        void Image::setPixel(const math::Vector2i& position, UInt32 color)
        {
            assert( this->Data != NULL );
            assert( position.x <  this->Data->size.x );
            assert( position.y <  this->Data->size.y );
            
            UInt32 *imagePointer = (UInt32*)( this->Data->data.get() );

            imagePointer[ this->getOffset(position) ] = color;
        }


        int Image::getOffset(const math::Vector2i& position) const
        {
            assert(this->Data != NULL);
            assert( position.x <  this->Data->size.x );
            assert( position.y <  this->Data->size.y );
            
            return position.y * this->Data->size.x + position.x;
        }
    }
}
