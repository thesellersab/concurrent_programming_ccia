cmake_minimum_required(VERSION 3.10)
project(DynamicProjectBuilder)

# Set project number via command line: -DPROJ_NUM=<number>
set(PROJ_NUM 1 CACHE STRING "Project number (e.g., 1, 2, etc.)")

# 1. Find the target folder (e.g., "1_manage_thread")
file(GLOB PROJECT_DIR LIST_DIRECTORIES true "${PROJ_NUM}_*")
list(LENGTH PROJECT_DIR NUM_DIRS)

if(NUM_DIRS EQUAL 0)
    message(FATAL_ERROR "No directory found starting with '${PROJ_NUM}_'")
elseif(NUM_DIRS GREATER 1)
    message(FATAL_ERROR "Multiple directories found starting with '${PROJ_NUM}_'")
endif()

# 2. Find the .cpp file in the folder
file(GLOB SOURCES "${PROJECT_DIR}/*.cpp")
list(LENGTH SOURCES NUM_SOURCES)

if(NUM_SOURCES EQUAL 0)
    message(FATAL_ERROR "No .cpp file found in ${PROJECT_DIR}")
endif()

# 3. Build executable named <number>_app.exe
set(EXE_NAME "${PROJ_NUM}_app")
add_executable(${EXE_NAME} ${SOURCES})

# Link threading libraries
find_package(Threads REQUIRED)
target_link_libraries(${EXE_NAME} PRIVATE Threads::Threads)

# 4. Generate a run script and set execute permissions
configure_file(
    "${CMAKE_SOURCE_DIR}/run_app.sh.in"
    "${CMAKE_BINARY_DIR}/run_app.sh"
    @ONLY
)

# Ensure execute permissions (Unix-only)
if(UNIX)
    execute_process(
        COMMAND chmod +x "${CMAKE_BINARY_DIR}/run_app.sh"
        RESULT_VARIABLE chmod_result
    )
    if(NOT chmod_result EQUAL 0)
        message(FATAL_ERROR "Failed to set execute permissions for run_app.sh")
    endif()
endif()

# 5. Custom 'run' target (usage: make run RUN_NUM=<number>)
add_custom_target(run
    COMMAND ./run_app.sh ${RUN_NUM}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running project ${RUN_NUM}_app.exe"
)