#ifndef PATHTRACER_CUDA_RL_HELPER_FUNCTIONS_H
#define PATHTRACER_CUDA_RL_HELPER_FUNCTIONS_H

#include <cmath>
#include "renderengine_gpu.h"
#include "pathtracer_params.h"

struct QNode
{
    float v[8];
    float max;
};

#if ENABLE_RL

__device__ unsigned int getQIndex(float3 &r)
{
    return clamp(static_cast<uint>((floor(r.x) + MAX_COORD) * MAX_COORD * MAX_COORD * 4 + (floor(r.y) + MAX_COORD) * MAX_COORD * 2 + floor(r.z) + MAX_COORD), (uint)0, (uint)MAX_COORD * MAX_COORD * MAX_COORD * 8);
}

__device__ unsigned char getDirectionOctant(float3 &r)
{
    return static_cast<unsigned char>(r.z > 0 ? (r.y > 0 ? (r.x > 0 ? 0 : 1) : (r.x > 0 ? 2 : 3)) : (r.y > 0 ? (r.x > 0 ? 4 : 5) : (r.x > 0 ? 6 : 7)));
}

__device__ __inline__ inline void
updateQTable(QNode *&q_table, unsigned int &last_index, unsigned char &dir_oct, float newVal)
{
    q_table[last_index].v[dir_oct] = q_table[last_index].v[dir_oct] * (1 - ALPHA) + newVal * ALPHA;
    q_table[last_index].max = fmax(q_table[last_index].v[dir_oct], q_table[last_index].max);
}

#endif

#endif // PATHTRACER_CUDA_RL_HELPER_FUNCTIONS_H
