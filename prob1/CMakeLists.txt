add_executable(prob1 prob1.cpp)

target_include_directories(prob1 PRIVATE
  ${CMAKE_SOURCE_DIR}/vendor/include
  )
