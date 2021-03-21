
add_executable(
    tibere_app
    System.h
    System.cpp
    DiscreteStorage.h
    DiscreteStorage.cpp
    MetaMessage.h
    MetaMessage.cpp
    main.cpp)

target_link_libraries(tibere_app PUBLIC Qt5::Core)

