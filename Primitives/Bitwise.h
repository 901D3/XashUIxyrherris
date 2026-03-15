
#pragma once

#define UINT8MAX (static_cast<char>(~0u))
#define INT8MAX (static_cast<char>(UINT8MAX >> 1))
#define INT8MIN (static_cast<char>(-(UINT8MAX >> 1) - 1))

#define UINT32MAX (~0U)
#define INT32MAX (static_cast<int>(UINT32MAX >> 1))
#define INT32MIN (-INT32MAX - 1)

#define UINT64MAX (~0ULL)
#define INT64MAX (static_cast<long long>(UINT64MAX >> 1))
#define INT64MIN (-INT64MAX - 1)
