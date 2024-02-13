add_executable(1-base-from-member
    main.cpp
    FdStreambuf.h
    FdStreambuf.cpp
)
target_link_libraries(1-base-from-member PUBLIC boost::utility)
