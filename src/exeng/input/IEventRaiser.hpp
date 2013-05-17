

#ifndef __EXENG_INPUT_IEVENTRAISER_HPP__
#define __EXENG_INPUT_IEVENTRAISER_HPP__

namespace exeng {
    namespace input {
        class IEventRaiser {
        public:
            virtual ~IEventRaiser() = 0;
            virtual void pollEvents() = 0;
        };
    }
}

#endif  //__EXENG_INPUT_IEVENTRAISER_HPP__
