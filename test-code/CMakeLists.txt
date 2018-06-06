add_executable(crash assertdbg/crash.cpp)
target_link_libraries(crash Coin::Coin SoQt)

#add_executable(coloreditor components/coloreditor.cpp)
#target_link_libraries(coloreditor Coin::Coin SoQt)

add_executable(embeddedexaminer components/embeddedexaminer.cpp)
target_link_libraries(embeddedexaminer Coin::Coin SoQt)

add_executable(renderarea components/renderarea.cpp)
target_link_libraries(renderarea Coin::Coin SoQt)

add_executable(scrollview components/scrollview.cpp)
target_link_libraries(scrollview Coin::Coin SoQt)

add_executable(tripleview components/tripleview.cpp)
target_link_libraries(tripleview Coin::Coin SoQt)

add_executable(withoutdecor0 components/withoutdecor0.cpp)
target_link_libraries(withoutdecor0 Coin::Coin SoQt)

add_executable(withoutdecor1 components/withoutdecor1.cpp)
target_link_libraries(withoutdecor1 Coin::Coin SoQt)

add_executable(thumbwheel widgets/thumbwheel.cpp)
target_link_libraries(thumbwheel Coin::Coin SoQt)
