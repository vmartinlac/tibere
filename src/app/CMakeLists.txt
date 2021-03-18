
add_executable(
    tibere_app
    System.h
    System.cpp
    Message.h
    Message.cpp
    Engine.h
    Engine.cpp
    main.cpp)

target_link_libraries(tibere_app PUBLIC Qt5::Core)

