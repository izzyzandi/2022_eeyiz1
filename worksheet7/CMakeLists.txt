if(WIN32)
	set(CPACK_GENERATOR "NSIS")
else()
	set(CPACK_GENERATOR "ZIP")
endif()

include(CPack)

add_library(maths adder.cpp)

add_executable(calc calc.cpp)
target_link_libraries(calc maths)

install( TARGETS calc maths
	   RUNTIME DESTINATION bin
	   LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib/static)