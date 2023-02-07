#include <stdint.h>
#include <vector>
#include <iostream>
#include <string.h>

    template <typename type>
    class serdes {
        public:
            std::vector<uint8_t> serialize(type& _src) {
                uint8_t *bytes = reinterpret_cast<uint8_t*>(&_src);
                std::vector<uint8_t> return_value;
                for(size_t i=0;i<sizeof(_src);i++) {
                    return_value.push_back(*bytes);
                    bytes++;
                } return return_value;
            }
            
            type deserialize(std::vector<uint8_t>& _src) {
                uint8_t *bytes = _src.data();
                type return_value;
                memcpy((void*)&return_value,(void*)bytes,_src.size());
                return return_value;
            }
    };
// namespace fev
