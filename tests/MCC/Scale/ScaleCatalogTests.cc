#include <gtest/gtest.h>

#include <MCC.h>

#include <cstring>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace Scales = MCC::Scales;
using MCC::Accidental;
using MCC::Letter;
using MCC::NoteName;
using MCC::Scale;

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
    Scales::Id id;
    const char* name;
    Scales::Family family;
    const char* fromC;
};

// Reviewed catalog spelled from C. Legacy definitions keep their semitones
// except where Scale.dox records a correction (Byzantine, Hirajoshi, Arabic,
// Japanese, Major Blues name); Melodic Minor and Iwato are new.
const Expected Catalog[] = {
    {Scales::Id::Chromatic, "Chromatic", Scales::Family::Symmetric, "C C# D D# E F F# G G# A A# B"},
    {Scales::Id::ChromaticFlats, "Chromatic (Flats)", Scales::Family::Symmetric, "C Db D Eb E F Gb G Ab A Bb B"},
    {Scales::Id::Major, "Major", Scales::Family::Western, "C D E F G A B"},
    {Scales::Id::Minor, "Minor", Scales::Family::Western, "C D Eb F G Ab Bb"},
    {Scales::Id::HarmonicMinor, "Harmonic Minor", Scales::Family::Western, "C D Eb F G Ab B"},
    {Scales::Id::MelodicMinor, "Melodic Minor", Scales::Family::Western, "C D Eb F G A B"},
    {Scales::Id::HarmonicMajor, "Harmonic Major", Scales::Family::Western, "C D E F G Ab B"},
    {Scales::Id::MajorPentatonic, "Major Pentatonic", Scales::Family::Western, "C D E G A"},
    {Scales::Id::MinorPentatonic, "Minor Pentatonic", Scales::Family::Western, "C Eb F G Bb"},
    {Scales::Id::MinorBlues, "Minor Blues", Scales::Family::Western, "C Eb F Gb G Bb"},
    {Scales::Id::MajorBlues, "Major Blues", Scales::Family::Western, "C D Eb E G A"},
    {Scales::Id::Dorian, "Dorian", Scales::Family::Modal, "C D Eb F G A Bb"},
    {Scales::Id::Phrygian, "Phrygian", Scales::Family::Modal, "C Db Eb F G Ab Bb"},
    {Scales::Id::Lydian, "Lydian", Scales::Family::Modal, "C D E F# G A B"},
    {Scales::Id::Mixolydian, "Mixolydian", Scales::Family::Modal, "C D E F G A Bb"},
    {Scales::Id::Locrian, "Locrian", Scales::Family::Modal, "C Db Eb F Gb Ab Bb"},
    {Scales::Id::Algerian, "Algerian", Scales::Family::Exotic, "C D Eb F F# G Ab B"},
    {Scales::Id::Arabic, "Arabic", Scales::Family::Exotic, "C D E F Gb Ab Bb"},
    {Scales::Id::Augmented, "Augmented", Scales::Family::Symmetric, "C Eb E G G# B"},
    {Scales::Id::Pelog, "Pelog", Scales::Family::Exotic, "C Db Eb G Ab"},
    {Scales::Id::Byzantine, "Byzantine", Scales::Family::Exotic, "C Db E F G Ab B"},
    {Scales::Id::Chinese, "Chinese", Scales::Family::Exotic, "C E F# G B"},
    {Scales::Id::Diminished, "Diminished", Scales::Family::Symmetric, "C D Eb F F# G# A B"},
    {Scales::Id::Egyptian, "Egyptian", Scales::Family::Exotic, "C D F G Bb"},
    {Scales::Id::EightToneSpanish, "Eight Tone Spanish", Scales::Family::Exotic, "C Db D# E F Gb Ab Bb"},
    {Scales::Id::Enigmatic, "Enigmatic", Scales::Family::Exotic, "C Db E F# G# A# B"},
    {Scales::Id::Hindu, "Hindu", Scales::Family::Exotic, "C D E F G Ab Bb"},
    {Scales::Id::Hirajoshi, "Hirajoshi", Scales::Family::Exotic, "C D Eb G Ab"},
    {Scales::Id::Iwato, "Iwato", Scales::Family::Exotic, "C Db F Gb Bb"},
    {Scales::Id::HungarianMinor, "Hungarian Minor", Scales::Family::Exotic, "C D Eb F# G Ab B"},
    {Scales::Id::Japanese, "Japanese", Scales::Family::Exotic, "C Db F G Bb"},
    {Scales::Id::Oriental, "Oriental", Scales::Family::Exotic, "C Db E F Gb A Bb"},
    {Scales::Id::WholeTone, "Whole Tone", Scales::Family::Symmetric, "C D E F# G# Bb"},
    {Scales::Id::RomanianMinor, "Romanian Minor", Scales::Family::Exotic, "C D Eb F# G A Bb"},
    {Scales::Id::SpanishGypsy, "Spanish Gypsy", Scales::Family::Exotic, "C Db E F G Ab Bb"},
    {Scales::Id::SuperLocrian, "Super Locrian", Scales::Family::Exotic, "C Db Eb Fb Gb Ab Bb"},
};

std::vector<std::string> Words(const char* text) {
    std::istringstream stream(text);
    std::vector<std::string> words;
    for (std::string word; stream >> word;) {
        words.push_back(word);
    }
    return words;
}

std::string Name(Scales::Id id) {
    char buffer[Scales::NameCapacity];
    Scales::CopyName(id, buffer, sizeof(buffer));
    return buffer;
}

}

TEST(ScaleCatalogTests, MatchesTheReviewedTable) {
    ASSERT_EQ(sizeof(Catalog) / sizeof(Catalog[0]), Scales::Count);
    for (const Expected& expected : Catalog) {
        SCOPED_TRACE(expected.name);
        EXPECT_EQ(static_cast<int>(expected.id), &expected - Catalog);
        EXPECT_EQ(Name(expected.id), expected.name);
        EXPECT_EQ(Scales::FamilyOf(expected.id), expected.family);
        const Scale scale = Scales::Make(NoteName(Letter::C), expected.id);
        const std::vector<std::string> notes = Words(expected.fromC);
        ASSERT_EQ(scale.DegreeCount(), notes.size());
        for (std::size_t i = 0; i < notes.size(); ++i) {
            EXPECT_EQ(scale.NoteAt(static_cast<int>(i + 1)), Parse(notes[i])) << notes[i];
        }
    }
}

TEST(ScaleCatalogTests, EveryEntrySpellsFromEveryCommonRoot) {
    // SPEC-SCL-2: degree letters follow the pattern's steps and pitch classes
    // follow its semitones for all 35 roots with up to two accidentals.
    for (uint8_t i = 0; i < Scales::Count; ++i) {
        const Scales::Id id = static_cast<Scales::Id>(i);
        const MCC::ScalePattern pattern = Scales::Pattern(id);
        ASSERT_TRUE(pattern.IsValid()) << Name(id);
        for (int letter = 0; letter < 7; ++letter) {
            for (int accidental = -2; accidental <= 2; ++accidental) {
                const NoteName root(static_cast<Letter>(letter), Accidental(accidental));
                const Scale scale(root, pattern);
                for (int degree = 1; degree <= scale.DegreeCount(); ++degree) {
                    const NoteName note = scale.NoteAt(degree);
                    const MCC::Interval interval = pattern.DegreeInterval(degree);
                    ASSERT_TRUE(note.IsValid()) << Name(id) << " degree " << degree;
                    EXPECT_EQ(MCC::DiatonicIndex(note.Letter()),
                              (letter + interval.DiatonicSteps()) % 7);
                    EXPECT_EQ(note.PitchClass().Value(),
                              (root.PitchClass().Value() + interval.Semitones()) % 12);
                    EXPECT_EQ(scale.DegreeOf(note), degree);
                }
            }
        }
    }
}

TEST(ScaleCatalogTests, IdentifiersNamesAndPatternsAreUnique) {
    std::set<std::string> names;
    for (uint8_t i = 0; i < Scales::Count; ++i) {
        const Scales::Id id = static_cast<Scales::Id>(i);
        EXPECT_TRUE(names.insert(Name(id)).second) << Name(id);
        EXPECT_EQ(Scales::Find(Name(id).c_str()), id);
        for (uint8_t j = 0; j < i; ++j) {
            EXPECT_NE(Scales::Pattern(id), Scales::Pattern(static_cast<Scales::Id>(j)))
                << Name(id) << " duplicates " << Name(static_cast<Scales::Id>(j));
        }
    }
    for (uint8_t i = 0; i < Scales::AliasCount; ++i) {
        char alias[Scales::NameCapacity];
        Scales::Id target = Scales::Id::Invalid;
        Scales::CopyAlias(i, alias, sizeof(alias), target);
        EXPECT_TRUE(names.insert(alias).second) << alias;
        EXPECT_NE(target, Scales::Id::Invalid);
        EXPECT_EQ(Scales::Find(alias), target) << alias;
    }
}

TEST(ScaleCatalogTests, AliasesResolveToTheirScales) {
    EXPECT_EQ(Scales::Find("Ionian"), Scales::Id::Major);
    EXPECT_EQ(Scales::Find("Aeolian"), Scales::Id::Minor);
    EXPECT_EQ(Scales::Find("Ethiopian"), Scales::Id::Minor);
    EXPECT_EQ(Scales::Find("Altered"), Scales::Id::SuperLocrian);
    EXPECT_EQ(Scales::Find("Phrygian Dominant"), Scales::Id::SpanishGypsy);
    EXPECT_EQ(Scales::Find("major"), Scales::Id::Invalid);
    EXPECT_EQ(Scales::Find(""), Scales::Id::Invalid);
    EXPECT_EQ(Scales::Find(nullptr), Scales::Id::Invalid);
}

TEST(ScaleCatalogTests, InvalidQueriesAreSafe) {
    EXPECT_FALSE(Scales::Pattern(Scales::Id::Invalid).IsValid());
    EXPECT_EQ(Scales::FamilyOf(Scales::Id::Invalid), Scales::Family::Invalid);
    char buffer[4] = {'x', 'x', 'x', 'x'};
    EXPECT_EQ(Scales::CopyName(Scales::Id::Invalid, buffer, sizeof(buffer)), 0U);
    EXPECT_STREQ(buffer, "");
    Scales::Id target = Scales::Id::Major;
    EXPECT_EQ(Scales::CopyAlias(Scales::AliasCount, buffer, sizeof(buffer), target), 0U);
    EXPECT_EQ(target, Scales::Id::Invalid);
    // Truncation follows snprintf semantics.
    EXPECT_EQ(Scales::CopyName(Scales::Id::Mixolydian, buffer, sizeof(buffer)), 10U);
    EXPECT_STREQ(buffer, "Mix");
}
