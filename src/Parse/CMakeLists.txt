set(DIR "${CMAKE_SOURCE_DIR}/Parse/")

execute_process(COMMAND bison -d -o ${DIR}parser.cpp ${DIR}parser.y)
    
add_custom_target(parse ALL
    COMMAND bison -d -o ${DIR}parser.cpp ${DIR}parser.y
    DEPENDS ${DIR}parser.y
    BYPRODUCTS ${DIR}parser.hpp ${DIR}parser.cpp
    )

