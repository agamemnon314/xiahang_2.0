cmake_minimum_required(VERSION 3.8)
project(XH_2nd)

set(CMAKE_CXX_STANDARD 11)


set(SYSTEM "x86-64_linux")
set(LIBFORMAT "static_pic")
set(CPLEXDIR "/opt/ibm/ILOG/CPLEX_Studio1271/cplex")
set(CONCERTDIR "/opt/ibm/ILOG/CPLEX_Studio1271/concert")

# cplex
include_directories(${CPLEXDIR}/include)
link_directories(${CPLEXDIR}/lib/${SYSTEM}/${LIBFORMAT})
# cplex concert
include_directories(${CONCERTDIR}/include)
link_directories(${CONCERTDIR}/lib/${SYSTEM}/${LIBFORMAT})
link_libraries(concert)
link_libraries(ilocplex)
link_libraries(cplex)
link_libraries(pthread)
link_libraries(m)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -DIL_STD")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lm -lpthread")

set(SOURCE_FILES main.cpp flight.h data_io.h reschedule.h)
add_executable(XH_2nd ${SOURCE_FILES})