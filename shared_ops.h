#pragma once

/**
* Format:   v_mov_b32 dst, src
* Example:  v_mov_b32 v4, 65536
*/
inline __device__ void shared_init(uint32_t &redA, uint32_t &redB, uint32_t &blueA, uint32_t &blueB) {
    asm volatile ("\n \
        v_mov_b32 %0, 0     \n \
        v_mov_b32 %1, 4096  \n \
        v_mov_b32 %2, 8192  \n \
        v_mov_b32 %3, 12288 \n \
        "
    :"=v"(redA),"=v"(redB),"=v"(blueA),"=v"(blueB)
    :
    );
}

/**
* Format:   ds_write_b128 src, dst
* Example:  ds_write_b128 v2, v[4:7]
*/
template<uint32_t offset>
inline __device__ void shared_write_b128_off(Float4 &val, uint32_t &lds) {
    if(offset == 0) {
    asm volatile("\n \
        ds_write_b128 %0, %1 \n \
        "
    :
    :"v"(lds),"v"(val)
    );
    return;
    }
    if(offset == 4096) {
      asm volatile("\n \
          ds_write_b128 %0, %1 offset:4096 \n \
          "
      :
      :"v"(lds),"v"(val)
      );
    }
}

inline __device__ void shared_write_b128(Float4 &val, uint32_t &lds) {
    asm volatile("\n \
    ds_write_b128 %0, %1 \n \
    "
    :
    :"v"(lds),"v"(val)
    );
}

/**
* Format:   ds_read_b128 dst, src
* Example:  ds_read_b128 v[8:11], v2
*/
inline __device__ void shared_read_b128(Float4 &val, uint32_t &lds) {
    asm volatile ("\n \
        ds_read_b128 %0, %1 \n \
        "
    :"=v"(val)
    :"v"(lds)
    );
}
