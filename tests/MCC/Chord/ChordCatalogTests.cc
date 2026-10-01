#include <gtest/gtest.h>

#include <MCC.h>

#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace Chords = MCC::Chords;
using MCC::Accidental;
using MCC::Chord;
using MCC::Letter;
using MCC::NoteName;

namespace {

NoteName Parse(const std::string& text) {
    const Letter letters[] = {Letter::C, Letter::D, Letter::E, Letter::F,
                              Letter::G, Letter::A, Letter::B};
    const int index = static_cast<int>(std::string("CDEFGAB").find(text[0]));
    int accidental = 0;
    for (std::size_t i = 1; i < text.size(); ++i) {
        accidental += text[i] == '#' ? 1 : -1;
    }
    return NoteName(letters[index], Accidental(accidental));
}

struct Expected {
    Chords::Id id;
    const char* name;
    const char* symbol;
    const char* fromC;
};

// Reviewed catalog spelled from C. Legacy definitions keep their tones except
// where Chord.dox records a correction; entries 23-27 are new.
const Expected Catalog[] = {
    {Chords::Id::Major, "Major", "", "C E G"},
    {Chords::Id::Minor, "Minor", "m", "C Eb G"},
    {Chords::Id::Augmented, "Augmented", "aug", "C E G#"},
    {Chords::Id::Diminished, "Diminished", "dim", "C Eb Gb"},
    {Chords::Id::Sixth, "Sixth", "6", "C E G A"},
    {Chords::Id::MinorSixth, "Minor Sixth", "m6", "C Eb G A"},
    {Chords::Id::DominantSeventh, "Dominant Seventh", "7", "C E G Bb"},
    {Chords::Id::MajorSeventh, "Major Seventh", "maj7", "C E G B"},
    {Chords::Id::MinorSeventh, "Minor Seventh", "m7", "C Eb G Bb"},
    {Chords::Id::HalfDiminishedSeventh, "Half Diminished Seventh", "m7b5", "C Eb Gb Bb"},
    {Chords::Id::DiminishedSeventh, "Diminished Seventh", "dim7", "C Eb Gb Bbb"},
    {Chords::Id::DominantNinth, "Dominant Ninth", "9", "C E G Bb D"},
    {Chords::Id::DominantMinorNinth, "Dominant Minor Ninth", "7b9", "C E G Bb Db"},
    {Chords::Id::MajorNinth, "Major Ninth", "maj9", "C E G B D"},
    {Chords::Id::MinorNinth, "Minor Ninth", "m9", "C Eb G Bb D"},
    {Chords::Id::DominantEleventh, "Dominant Eleventh", "11", "C E G Bb D F"},
    {Chords::Id::MajorEleventh, "Major Eleventh", "maj11", "C E G B D F"},
    {Chords::Id::MinorEleventh, "Minor Eleventh", "m11", "C Eb G Bb D F"},
    {Chords::Id::DominantThirteenth, "Dominant Thirteenth", "13", "C E G Bb D A"},
    {Chords::Id::MajorThirteenth, "Major Thirteenth", "maj13", "C E G B D A"},
    {Chords::Id::MinorThirteenth, "Minor Thirteenth", "m13", "C Eb G Bb D F A"},
    {Chords::Id::SuspendedSecond, "Suspended Second", "sus2", "C D G"},
    {Chords::Id::SuspendedFourth, "Suspended Fourth", "sus4", "C F G"},
    {Chords::Id::MinorMajorSeventh, "Minor Major Seventh", "mMaj7", "C Eb G B"},
    {Chords::Id::AugmentedSeventh, "Augmented Seventh", "aug7", "C E G# Bb"},
    {Chords::Id::AddedNinth, "Added Ninth", "add9", "C E G D"},
    {Chords::Id::SeventhSuspendedFourth, "Seventh Suspended Fourth", "7sus4", "C F G Bb"},
    {Chords::Id::Power, "Power", "5", "C G"},
};

std::vector<std::string> Words(const char* text) {
    std::istringstream stream(text);
    std::vector<std::string> words;
    for (std::string word; stream >> word;) {
        words.push_back(word);
    }
    return words;
}

std::string Name(Chords::Id id) {
    char buffer[Chords::NameCapacity];
    Chords::CopyName(id, buffer, sizeof(buffer));
    return buffer;
}

std::string Symbol(Chords::Id id) {
    char buffer[Chords::SymbolCapacity];
    Chords::CopySymbol(id, buffer, sizeof(buffer));
    return buffer;
}

}

TEST(ChordCatalogTests, MatchesTheReviewedTable) {
    ASSERT_EQ(sizeof(Catalog) / sizeof(Catalog[0]), Chords::Count);
    for (const Expected& expected : Catalog) {
        SCOPED_TRACE(expected.name);
        EXPECT_EQ(static_cast<int>(expected.id), &expected - Catalog);
        EXPECT_EQ(Name(expected.id), expected.name);
        EXPECT_EQ(Symbol(expected.id), expected.symbol);
        const Chord chord = Chords::Make(NoteName(Letter::C), expected.id);
        const std::vector<std::string> notes = Words(expected.fromC);
        ASSERT_EQ(chord.ToneCount(), notes.size());
        for (std::size_t i = 0; i < notes.size(); ++i) {
            EXPECT_EQ(chord.ToneAt(static_cast<int>(i + 1)), Parse(notes[i])) << notes[i];
        }
    }
}

TEST(ChordCatalogTests, EveryEntrySpellsFromEveryCommonRoot) {
    // SPEC-CHD-2: tone letters follow the pattern's steps and pitch classes
    // follow its semitones for all 35 roots with up to two accidentals.
    for (uint8_t i = 0; i < Chords::Count; ++i) {
        const Chords::Id id = static_cast<Chords::Id>(i);
        const MCC::ChordPattern pattern = Chords::Pattern(id);
        ASSERT_TRUE(pattern.IsValid()) << Name(id);
        for (int letter = 0; letter < 7; ++letter) {
            for (int accidental = -2; accidental <= 2; ++accidental) {
                const NoteName root(static_cast<Letter>(letter), Accidental(accidental));
                const Chord chord(root, pattern);
                for (int tone = 1; tone <= chord.ToneCount(); ++tone) {
                    const NoteName note = chord.ToneAt(tone);
                    const MCC::Interval interval = pattern.ToneInterval(tone);
                    ASSERT_TRUE(note.IsValid()) << Name(id) << " tone " << tone;
                    EXPECT_EQ(MCC::DiatonicIndex(note.Letter()),
                              (letter + interval.DiatonicSteps()) % 7);
                    EXPECT_EQ(note.PitchClass().Value(),
                              (root.PitchClass().Value() + interval.Semitones()) % 12);
                    EXPECT_TRUE(chord.Contains(note));
                }
            }
        }
    }
}

TEST(ChordCatalogTests, IdentifiersNamesSymbolsAndPatternsAreUnique) {
    std::set<std::string> names;
    std::set<std::string> symbols;
    for (uint8_t i = 0; i < Chords::Count; ++i) {
        const Chords::Id id = static_cast<Chords::Id>(i);
        EXPECT_TRUE(names.insert(Name(id)).second) << Name(id);
        EXPECT_TRUE(symbols.insert(Symbol(id)).second) << Symbol(id);
        EXPECT_EQ(Chords::Find(Name(id).c_str()), id);
        for (uint8_t j = 0; j < i; ++j) {
            EXPECT_NE(Chords::Pattern(id), Chords::Pattern(static_cast<Chords::Id>(j)))
                << Name(id) << " duplicates " << Name(static_cast<Chords::Id>(j));
        }
    }
    for (uint8_t i = 0; i < Chords::AliasCount; ++i) {
        char alias[Chords::NameCapacity];
        Chords::Id target = Chords::Id::Invalid;
        Chords::CopyAlias(i, alias, sizeof(alias), target);
        EXPECT_TRUE(names.insert(alias).second) << alias;
        EXPECT_NE(target, Chords::Id::Invalid);
        EXPECT_EQ(Chords::Find(alias), target) << alias;
    }
}

TEST(ChordCatalogTests, InvalidQueriesAreSafe) {
    EXPECT_FALSE(Chords::Pattern(Chords::Id::Invalid).IsValid());
    EXPECT_EQ(Chords::Find("major"), Chords::Id::Invalid);
    EXPECT_EQ(Chords::Find(nullptr), Chords::Id::Invalid);
    char buffer[4] = {'x', 'x', 'x', 'x'};
    EXPECT_EQ(Chords::CopyName(Chords::Id::Invalid, buffer, sizeof(buffer)), 0U);
    EXPECT_STREQ(buffer, "");
    EXPECT_EQ(Chords::CopySymbol(Chords::Id::Invalid, buffer, sizeof(buffer)), 0U);
    Chords::Id target = Chords::Id::Major;
    EXPECT_EQ(Chords::CopyAlias(Chords::AliasCount, buffer, sizeof(buffer), target), 0U);
    EXPECT_EQ(target, Chords::Id::Invalid);
    EXPECT_EQ(Chords::CopySymbol(Chords::Id::MinorMajorSeventh, buffer, sizeof(buffer)), 5U);
    EXPECT_STREQ(buffer, "mMa");
}
