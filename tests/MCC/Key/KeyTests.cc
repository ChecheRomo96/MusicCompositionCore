#include <gtest/gtest.h>

#include <MCC.h>

#include <type_traits>

using MCC::Accidental;
using MCC::Key;
using MCC::KeyMode;
using MCC::KeySignature;
using MCC::Letter;
using MCC::NoteName;
using MCC::PitchClass;

static_assert(sizeof(KeySignature) == 1);
static_assert(std::is_trivially_copyable_v<Key>);
static_assert(Key(NoteName(Letter::E), KeyMode::Minor).Signature().Sharps() == 1);
static_assert(Key::FromSignature(KeySignature(-2), KeyMode::Major) ==
    Key(NoteName(Letter::B, Accidental::Flat()), KeyMode::Major));

namespace {

NoteName N(Letter letter, int accidental = 0) {
    return NoteName(letter, Accidental(accidental));
}

}

TEST(KeySignatureTests, AppliesSharpsAndFlatsInOrder) {
    const KeySignature twoSharps(2);
    EXPECT_EQ(twoSharps.AccidentalOf(Letter::F), Accidental::Sharp());
    EXPECT_EQ(twoSharps.AccidentalOf(Letter::C), Accidental::Sharp());
    EXPECT_EQ(twoSharps.AccidentalOf(Letter::G), Accidental::Natural());
    const KeySignature threeFlats(-3);
    EXPECT_EQ(threeFlats.AccidentalOf(Letter::B), Accidental::Flat());
    EXPECT_EQ(threeFlats.AccidentalOf(Letter::E), Accidental::Flat());
    EXPECT_EQ(threeFlats.AccidentalOf(Letter::A), Accidental::Flat());
    EXPECT_EQ(threeFlats.AccidentalOf(Letter::D), Accidental::Natural());
    EXPECT_EQ(threeFlats.Flats(), 3);
    EXPECT_FALSE(KeySignature(8).IsValid());
    EXPECT_FALSE(KeySignature(-8).IsValid());
    EXPECT_EQ(KeySignature().AccidentalOf(Letter::C), Accidental::Invalid());
}

TEST(KeyTests, SignaturesFollowTheCircleOfFifths) {
    struct Case { NoteName tonic; KeyMode mode; int fifths; };
    const Case cases[] = {
        {N(Letter::C), KeyMode::Major, 0},       {N(Letter::A), KeyMode::Minor, 0},
        {N(Letter::G), KeyMode::Major, 1},       {N(Letter::E), KeyMode::Minor, 1},
        {N(Letter::F), KeyMode::Major, -1},      {N(Letter::D), KeyMode::Minor, -1},
        {N(Letter::C, 1), KeyMode::Major, 7},    {N(Letter::C, -1), KeyMode::Major, -7},
        {N(Letter::A, 1), KeyMode::Minor, 7},    {N(Letter::A, -1), KeyMode::Minor, -7},
        {N(Letter::D), KeyMode::Dorian, 0},      {N(Letter::E), KeyMode::Phrygian, 0},
        {N(Letter::F), KeyMode::Lydian, 0},      {N(Letter::G), KeyMode::Mixolydian, 0},
        {N(Letter::B), KeyMode::Locrian, 0},     {N(Letter::F, 1), KeyMode::Dorian, 4},
    };
    for (const Case& c : cases) {
        const Key key(c.tonic, c.mode);
        ASSERT_TRUE(key.IsValid());
        EXPECT_EQ(key.Signature().Fifths(), c.fifths);
        EXPECT_EQ(Key::FromSignature(KeySignature(c.fifths), c.mode), key);
    }
    EXPECT_FALSE(Key(N(Letter::G, 1), KeyMode::Major).IsValid());
    EXPECT_FALSE(Key(N(Letter::F, -1), KeyMode::Major).IsValid());
    EXPECT_FALSE(Key(NoteName::Invalid(), KeyMode::Major).IsValid());
}

TEST(KeyTests, EverySignatureAndModeRoundTrips) {
    for (int fifths = -7; fifths <= 7; ++fifths) {
        for (int mode = 0; mode < 7; ++mode) {
            const Key key = Key::FromSignature(KeySignature(fifths), static_cast<KeyMode>(mode));
            ASSERT_TRUE(key.IsValid()) << fifths << ' ' << mode;
            EXPECT_EQ(key.Signature().Fifths(), fifths);
            // The key's scale uses exactly the signature's accidentals.
            const MCC::Scale scale = key.Scale();
            ASSERT_EQ(scale.DegreeCount(), 7);
            for (int degree = 1; degree <= 7; ++degree) {
                const NoteName note = scale.NoteAt(degree);
                EXPECT_EQ(note.Accidental(), key.Signature().AccidentalOf(note.Letter()));
            }
        }
    }
}

TEST(KeyTests, SpellsPitchClassesInContext) {
    const Key eMinor(N(Letter::E), KeyMode::Minor);
    const Key fMajor(N(Letter::F), KeyMode::Major);
    const Key bMajor(N(Letter::B), KeyMode::Major);
    EXPECT_EQ(eMinor.Spell(PitchClass(6)), N(Letter::F, 1));     // diatonic F#
    EXPECT_EQ(eMinor.Spell(PitchClass(3)), N(Letter::D, 1));     // chromatic, raised
    EXPECT_EQ(fMajor.Spell(PitchClass(10)), N(Letter::B, -1));   // diatonic Bb
    EXPECT_EQ(fMajor.Spell(PitchClass(3)), N(Letter::E, -1));    // chromatic, lowered
    EXPECT_EQ(bMajor.Spell(PitchClass(5)), N(Letter::F));        // F natural, not E#
    EXPECT_EQ(bMajor.Spell(PitchClass(10)), N(Letter::A, 1));    // tie: raised in a sharp key
    EXPECT_EQ(fMajor.Spell(PitchClass(8)), N(Letter::A, -1));    // tie: lowered in a flat key
    EXPECT_EQ(Key(N(Letter::E), KeyMode::Major).Spell(PitchClass(0)), N(Letter::C));
    EXPECT_EQ(Key(N(Letter::C, 1), KeyMode::Major).Spell(PitchClass(0)), N(Letter::B, 1));  // diatonic
    for (int fifths = -7; fifths <= 7; ++fifths) {
        const Key key = Key::FromSignature(KeySignature(fifths), KeyMode::Major);
        for (int pc = 0; pc < 12; ++pc) {
            const NoteName spelled = key.Spell(PitchClass(pc));
            ASSERT_TRUE(spelled.IsValid());
            EXPECT_EQ(spelled.PitchClass(), PitchClass(pc));
        }
    }
    EXPECT_FALSE(Key().Spell(PitchClass(0)).IsValid());
}

TEST(KeyTests, SpellsChromaticIndicesWithOctaves) {
    const Key cSharpMajor(N(Letter::C, 1), KeyMode::Major);
    // Chromatic index 60 is C4; B# is diatonic in C# major, so it is written B#3.
    EXPECT_EQ(cSharpMajor.Spell(MCC::ChromaticIndex(60)), MCC::Pitch(N(Letter::B, 1), 3));
    const Key cFlatMajor(N(Letter::C, -1), KeyMode::Major);
    // Chromatic index 59 is B3; in Cb major it is written Cb4.
    EXPECT_EQ(cFlatMajor.Spell(MCC::ChromaticIndex(59)), MCC::Pitch(N(Letter::C, -1), 4));
    EXPECT_FALSE(cFlatMajor.Spell(MCC::ChromaticIndex()).IsValid());
}
