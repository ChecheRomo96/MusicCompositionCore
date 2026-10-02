#include <gtest/gtest.h>

#include <MCC.h>

#include <type_traits>

using MCC::Accidental;
using MCC::Letter;
using MCC::Note;
using MCC::NoteName;
using MCC::NoteValue;
using MCC::Pitch;

namespace {

constexpr Pitch cSharp4(Letter::C, Accidental::Sharp(), 4);
constexpr NoteValue dottedEighth = NoteValue::Eighth(1);
constexpr Note noteFromPitch(cSharp4, dottedEighth);
constexpr Note noteFromName(NoteName(Letter::C, Accidental::Sharp()), 4,
                            dottedEighth);
constexpr Note noteFromParts(Letter::C, Accidental::Sharp(), 4, dottedEighth);
static_assert(noteFromPitch.IsValid());
static_assert(noteFromPitch == noteFromName);
static_assert(noteFromPitch == noteFromParts);
static_assert(noteFromPitch.Pitch() == cSharp4);
static_assert(noteFromPitch.Value() == dottedEighth);
static_assert(noteFromPitch.NoteName() == cSharp4.NoteName());
static_assert(noteFromPitch.ChromaticIndex().Value() == 61);

} // namespace

TEST(NoteTests, SupportsEverySpellingPreservingConstructor) {
    const Note expected(Pitch(Letter::F, Accidental::DoubleSharp(), 5),
                        NoteValue::Sixteenth(2));

    EXPECT_EQ(Note(
        Pitch(Letter::F, Accidental::DoubleSharp(), 5),
        NoteValue::Sixteenth(2)), expected);
    EXPECT_EQ(Note(
        NoteName(Letter::F, Accidental::DoubleSharp()), 5,
        NoteValue::Sixteenth(2)), expected);
    EXPECT_EQ(Note(
        Letter::F, Accidental::DoubleSharp(), 5,
        NoteValue::Sixteenth(2)), expected);
}

TEST(NoteTests, OmittedValueMeansQuarterNote) {
    EXPECT_EQ(Note(Pitch(Letter::C, 4)).Value(), NoteValue::Quarter());
    EXPECT_EQ(Note(NoteName(Letter::D), 4).Value(), NoteValue::Quarter());
    EXPECT_EQ(Note(Letter::E, 4).Value(), NoteValue::Quarter());
    EXPECT_EQ(Note(Letter::F, Accidental::Sharp(), 4).Value(),
              NoteValue::Quarter());
}

TEST(NoteTests, NaturalLetterConstructorPreservesTheRequestedValue) {
    const Note note(Letter::A, 3, NoteValue::Half(1));
    EXPECT_EQ(note.Pitch(), Pitch(Letter::A, 3));
    EXPECT_EQ(note.NoteName(), NoteName(Letter::A));
    EXPECT_EQ(note.Accidental(), Accidental::Natural());
    EXPECT_EQ(note.Octave(), 3);
    EXPECT_EQ(note.Value(), NoteValue::Half(1));
}

TEST(NoteTests, InvalidComponentsProduceTheCanonicalInvalidNote) {
    const Note invalidPitch(Pitch::Invalid(), NoteValue::Quarter());
    const Note invalidValue(Pitch(Letter::C, 4), NoteValue::Invalid());
    const Note invalidOctave(Letter::C, 128, NoteValue::Quarter());

    EXPECT_EQ(Note(), Note::Invalid());
    EXPECT_EQ(invalidPitch, Note::Invalid());
    EXPECT_EQ(invalidValue, Note::Invalid());
    EXPECT_EQ(invalidOctave, Note::Invalid());
    EXPECT_FALSE(Note::Invalid().IsValid());
    EXPECT_FALSE(Note::Invalid().Pitch().IsValid());
    EXPECT_FALSE(Note::Invalid().Value().IsValid());
    EXPECT_FALSE(Note::Invalid().NoteName().IsValid());
    EXPECT_FALSE(Note::Invalid().Accidental().IsValid());
    EXPECT_FALSE(Note::Invalid().PitchClass().IsValid());
    EXPECT_FALSE(Note::Invalid().ChromaticIndex().IsValid());
    EXPECT_EQ(Note::Invalid().Octave(), 0);
}

TEST(NoteTests, CopyStyleModifiersPreserveTheOtherComponent) {
    const Note original(Letter::C, 4, NoteValue::Quarter(1));

    EXPECT_EQ(original.WithPitch(Pitch(Letter::G, 5)),
              Note(Letter::G, 5, NoteValue::Quarter(1)));
    EXPECT_EQ(original.WithValue(NoteValue::Eighth()),
              Note(Letter::C, 4, NoteValue::Eighth()));
    EXPECT_EQ(original.WithDots(3), Note(Letter::C, 4, NoteValue::Quarter(3)));
    EXPECT_EQ(original.WithDots(5), Note::Invalid());
    EXPECT_EQ(Note::Invalid().WithPitch(Pitch(Letter::C, 4)), Note::Invalid());
}

TEST(NoteTests, PitchMovementPreservesTheNoteValue) {
    const Note bSharp3(
        Letter::B, Accidental::Sharp(), 3, NoteValue::Eighth(2));

    EXPECT_EQ(bSharp3.MovedDiatonically(1),
              Note(Letter::C, Accidental::Sharp(), 4, NoteValue::Eighth(2)));
    EXPECT_EQ(bSharp3.Altered(-1),
              Note(Letter::B, Accidental::Natural(), 3, NoteValue::Eighth(2)));
    EXPECT_EQ(bSharp3.MovedByOctaves(2),
              Note(Letter::B, Accidental::Sharp(), 5, NoteValue::Eighth(2)));
}

TEST(NoteTests, EqualityAndWrittenOrderIncludeTheValue) {
    const Note c4Quarter(Letter::C, 4, NoteValue::Quarter());
    const Note c4DottedQuarter(Letter::C, 4, NoteValue::Quarter(1));
    const Note d4Eighth(Letter::D, 4, NoteValue::Eighth());

    EXPECT_NE(c4Quarter, c4DottedQuarter);
    EXPECT_LT(c4Quarter, c4DottedQuarter);
    EXPECT_LT(c4DottedQuarter, d4Eighth);
    EXPECT_LT(d4Eighth, Note::Invalid());
    EXPECT_FALSE(Note::Invalid() < d4Eighth);
}

TEST(NoteTests, SoundingOrderHandlesEnharmonicSpellings) {
    const Note bSharp3(
        Letter::B, Accidental::Sharp(), 3, NoteValue::Quarter());
    const Note cFlat4(
        Letter::C, Accidental::Flat(), 4, NoteValue::Quarter());
    const Note c4(Letter::C, 4, NoteValue::Quarter());

    EXPECT_TRUE(MCC::IsNoteLowerThan(cFlat4, bSharp3));
    EXPECT_TRUE(MCC::IsNoteLowerThan(bSharp3, c4));
    EXPECT_FALSE(MCC::IsNoteLowerThan(c4, bSharp3));
}

TEST(NoteTests, LayoutAndConstexprMeetEmbeddedRequirements) {
    static_assert(std::is_trivially_copyable_v<Note>);
    static_assert(!std::is_polymorphic_v<Note>);
    static_assert(sizeof(Note) <= 6u);
    SUCCEED();
}
