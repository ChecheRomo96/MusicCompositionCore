#include <MCC/Rhythm/RhythmPattern.h>

namespace MCC {

namespace {

bool IsStepCountValid(int32_t steps) noexcept {
    return steps >= 1 && steps <= static_cast<int32_t>(RhythmPattern::MaximumSteps);
}

int32_t Reduce(int32_t step, int32_t steps) noexcept {
    return ((step % steps) + steps) % steps;
}

// Counts the steps in box notation; -1 when the text is malformed or too long.
int32_t CountBoxSteps(const char* text) noexcept {
    if (text == nullptr) {
        return -1;
    }
    int32_t steps = 0;
    for (const char* c = text; *c != '\0'; ++c) {
        if (*c == 'x' || *c == 'X' || *c == '.') {
            if (steps == static_cast<int32_t>(RhythmPattern::MaximumSteps)) {
                return -1;
            }
            ++steps;
        } else if (*c != ' ' && *c != '|') {
            return -1;
        }
    }
    return steps;
}

// Sums interonset intervals; -1 when the text is malformed or too long.
int32_t CountIntervalSteps(const char* text) noexcept {
    if (text == nullptr || text[0] == '\0') {
        return -1;
    }
    const int32_t maximum = static_cast<int32_t>(RhythmPattern::MaximumSteps);
    int32_t steps = 0;
    const char* c = text;
    for (;;) {
        if (*c < '0' || *c > '9') {
            return -1;
        }
        int32_t interval = 0;
        while (*c >= '0' && *c <= '9') {
            interval = interval * 10 + (*c - '0');
            if (interval > maximum) {
                return -1;
            }
            ++c;
        }
        if (interval == 0 || steps + interval > maximum) {
            return -1;
        }
        steps += interval;
        if (*c == '\0') {
            return steps;
        }
        if (*c != '-') {
            return -1;
        }
        ++c;
    }
}

} // namespace

RhythmPattern::RhythmPattern(int32_t steps) noexcept : _steps() {
    if (IsStepCountValid(steps)) {
        _steps.Resize(static_cast<size_t>(steps));
    }
}

// --- Storage --------------------------------------------------------------

uint16_t RhythmPattern::Capacity() const noexcept {
    const size_t steps = _steps.GetCapacity();
    return steps > MaximumSteps ? MaximumSteps : static_cast<uint16_t>(steps);
}

bool RhythmPattern::Resize(int32_t steps) noexcept {
    return IsStepCountValid(steps) && _steps.Resize(static_cast<size_t>(steps));
}

bool RhythmPattern::Reserve(int32_t steps) noexcept {
    return steps >= 0 && steps <= static_cast<int32_t>(MaximumSteps) &&
        _steps.Reserve(static_cast<size_t>(steps));
}

bool RhythmPattern::Append(bool onset) noexcept {
    return _steps.GetCount() < MaximumSteps && _steps.PushBack(onset);
}

bool RhythmPattern::Append(const RhythmPattern& other) noexcept {
    const size_t added = other._steps.GetCount();
    const size_t total = _steps.GetCount() + added;
    if (added == 0u || total > MaximumSteps) {
        return false;
    }
    const size_t capacity = _steps.GetCapacity();
    if (total > capacity) {
        // Owned storage grows geometrically; attached storage cannot grow.
        const size_t doubled = capacity * 2u;
        const size_t target = OwnsStorage() && doubled > total ? doubled : total;
        if (!_steps.Reserve(target) && !_steps.Reserve(total)) {
            return false;
        }
    }
    // `other` may be this pattern: its first `added` steps are read before
    // any of them could be overwritten, and no reallocation happens here.
    for (size_t i = 0u; i < added; ++i) {
        _steps.PushBack(other._steps.Get(i));
    }
    return true;
}

bool RhythmPattern::ShrinkToFit() noexcept { return _steps.ShrinkToFit(); }

// --- Construction from data -----------------------------------------------

RhythmPattern RhythmPattern::FromMask(uint32_t onsets, int32_t steps) noexcept {
    if (steps < 1 || steps > 32 ||
        (steps < 32 && (onsets >> static_cast<uint8_t>(steps)) != 0u)) {
        return Invalid();
    }
    RhythmPattern pattern(steps);
    for (uint16_t i = 0u; i < pattern.StepCount(); ++i) {
        pattern._steps.Set(i, ((onsets >> i) & 1u) != 0u);
    }
    return pattern;
}

RhythmPattern RhythmPattern::FromString(const char* text) noexcept {
    RhythmPattern pattern;
    return pattern.Parse(text) ? pattern : Invalid();
}

RhythmPattern RhythmPattern::FromIntervals(const char* text) noexcept {
    RhythmPattern pattern;
    return pattern.ParseIntervals(text) ? pattern : Invalid();
}

bool RhythmPattern::Parse(const char* text) noexcept {
    const int32_t steps = CountBoxSteps(text);
    if (steps < 1 || !_steps.Reserve(static_cast<size_t>(steps))) {
        return false;
    }
    // The capacity is in place, so clearing and resizing cannot fail.
    _steps.Clear();
    _steps.Resize(static_cast<size_t>(steps));
    size_t step = 0u;
    for (const char* c = text; *c != '\0'; ++c) {
        if (*c == 'x' || *c == 'X' || *c == '.') {
            _steps.Set(step, *c != '.');
            ++step;
        }
    }
    return true;
}

bool RhythmPattern::ParseIntervals(const char* text) noexcept {
    const int32_t steps = CountIntervalSteps(text);
    if (steps < 1 || !_steps.Reserve(static_cast<size_t>(steps))) {
        return false;
    }
    _steps.Clear();
    _steps.Resize(static_cast<size_t>(steps));
    size_t step = 0u;
    const char* c = text;
    while (*c != '\0') {
        _steps.Set(step, true);
        size_t interval = 0u;
        while (*c >= '0' && *c <= '9') {
            interval = interval * 10u + static_cast<size_t>(*c - '0');
            ++c;
        }
        step += interval;
        if (*c == '-') {
            ++c;
        }
    }
    return true;
}

// --- Queries --------------------------------------------------------------

uint16_t RhythmPattern::OnsetCount() const noexcept {
    return static_cast<uint16_t>(_steps.CountOnes());
}

bool RhythmPattern::IsOnset(int32_t step) const noexcept {
    return IsValid() && Bit(static_cast<uint16_t>(Reduce(step, StepCount())));
}

int32_t RhythmPattern::OnsetStep(int32_t index) const noexcept {
    if (index < 0) {
        return -1;
    }
    int32_t seen = 0;
    for (uint16_t step = 0u; step < StepCount(); ++step) {
        if (Bit(step)) {
            if (seen == index) {
                return step;
            }
            ++seen;
        }
    }
    return -1;
}

int32_t RhythmPattern::InteronsetInterval(int32_t index) const noexcept {
    const int32_t from = OnsetStep(index);
    if (from < 0) {
        return 0;
    }
    const int32_t steps = StepCount();
    for (int32_t step = from + 1; step < steps; ++step) {
        if (Bit(static_cast<uint16_t>(step))) {
            return step - from;
        }
    }
    return steps - from + OnsetStep(0);
}

bool RhythmPattern::IsRotationOf(const RhythmPattern& other) const noexcept {
    if (!IsValid() || StepCount() != other.StepCount() || OnsetCount() != other.OnsetCount()) {
        return false;
    }
    const int32_t steps = StepCount();
    const int32_t first = OnsetStep(0);
    if (first < 0) {
        return true; // both are all rests
    }
    // Only shifts that land this pattern's first onset on an onset of
    // `other` can match.
    for (int32_t candidate = 0; candidate < steps; ++candidate) {
        if (other.Bit(static_cast<uint16_t>(candidate))) {
            const int32_t shift = Reduce(candidate - first, steps);
            bool same = true;
            for (int32_t i = 0; same && i < steps; ++i) {
                same = Bit(static_cast<uint16_t>(i)) ==
                    other.Bit(static_cast<uint16_t>((i + shift) % steps));
            }
            if (same) {
                return true;
            }
        }
    }
    return false;
}

// --- Editing --------------------------------------------------------------

bool RhythmPattern::SetOnset(int32_t step, bool onset) noexcept {
    return step >= 0 && _steps.Set(static_cast<size_t>(step), onset);
}

// Reverses the steps in [first, last).
void RhythmPattern::ReverseSteps(uint16_t first, uint16_t last) noexcept {
    while (static_cast<uint32_t>(first) + 1u < static_cast<uint32_t>(last)) {
        --last;
        const bool a = Bit(first);
        _steps.Set(first, Bit(last));
        _steps.Set(last, a);
        ++first;
    }
}

bool RhythmPattern::Rotate(int32_t steps) noexcept {
    if (!IsValid()) {
        return false;
    }
    // Left rotation by three reversals: no extra storage.
    const uint16_t count = StepCount();
    const uint16_t shift = static_cast<uint16_t>(Reduce(steps, count));
    if (shift != 0u) {
        ReverseSteps(0u, shift);
        ReverseSteps(shift, count);
        ReverseSteps(0u, count);
    }
    return true;
}

bool RhythmPattern::Invert() noexcept {
    if (!IsValid()) {
        return false;
    }
    _steps.FlipAll();
    return true;
}

RhythmPattern RhythmPattern::Rotated(int32_t steps) const noexcept {
    RhythmPattern rotated(*this);
    return rotated.Rotate(steps) ? rotated : Invalid();
}

RhythmPattern RhythmPattern::Complement() const noexcept {
    RhythmPattern complement(*this);
    return complement.Invert() ? complement : Invalid();
}

RhythmPattern RhythmPattern::Concatenated(const RhythmPattern& other) const noexcept {
    if (!IsValid() || !other.IsValid()) {
        return Invalid();
    }
    RhythmPattern joined;
    if (!joined.Reserve(static_cast<int32_t>(StepCount()) + other.StepCount()) ||
        !joined.Append(*this) || !joined.Append(other)) {
        return Invalid();
    }
    return joined;
}

} // namespace MCC
