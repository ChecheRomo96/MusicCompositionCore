add_executable(MCC_Note_Testing MusicalNoteTesting.cc )
target_link_libraries( MCC_Note_Testing PUBLIC MCC PUBLIC GTest::gtest_main )
gtest_discover_tests(MCC_Note_Testing)