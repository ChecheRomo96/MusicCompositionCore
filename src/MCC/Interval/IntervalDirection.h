#ifndef MCC_INTERVAL_INTERVAL_DIRECTION_H
#define MCC_INTERVAL_INTERVAL_DIRECTION_H

#include <stdint.h>

namespace MCC {

/**
 * @brief Direction of an interval (SPEC-INT-2).
 * @ingroup MCC_Interval
 *
 * The direction follows the written letters: an interval whose second
 * letter is higher is ascending even if it is a diminished interval. Only
 * the perfect unison has direction `Unison`; an augmented unison is
 * ascending or descending (SPEC-INT-5).
 */
enum class IntervalDirection : int8_t {
    Descending = -1,
    Unison = 0,
    Ascending = 1
};

} // namespace MCC

#endif // MCC_INTERVAL_INTERVAL_DIRECTION_H
