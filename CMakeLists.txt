# Gather all .cpp files
file(GLOB_RECURSE ALL_CPP_FILES ${PROJECT_SOURCE_DIR}/**/*.cpp)

# Initialize lists
set(LIB_SOURCES "")
set(MAIN_SOURCES "")

foreach(CPP_FILE ${ALL_CPP_FILES})
    file(READ ${CPP_FILE} FILE_CONTENTS)
    # Check for 'int main(' or 'int main ('
    if(FILE_CONTENTS MATCHES "int[ ]+main[ ]*\\(")
        list(APPEND MAIN_SOURCES ${CPP_FILE})
    else()
        list(APPEND LIB_SOURCES ${CPP_FILE})
    endif()
endforeach()

# Create the library
add_library(MyLibrary STATIC ${LIB_SOURCES})

# Create executables
foreach(MAIN_FILE ${MAIN_SOURCES})
    get_filename_component(EXEC_NAME ${MAIN_FILE} NAME_WE)
    add_executable(${EXEC_NAME} ${MAIN_FILE})
    target_link_libraries(${EXEC_NAME} PRIVATE MyLibrary)
endforeach()
