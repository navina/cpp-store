## Download dependencies with Hunter ##
hunter_add_package(Protobuf)

## Find Dependencies ##
find_package(Protobuf CONFIG REQUIRED)

## Targets ##

#Code Generation
set(MESSAGES_PROTOS
        "proto/messages.proto"
        "proto/addressbook.proto")
set(MESSAGES_SRCS)
set(MESSAGES_HDRS)

foreach(proto_file ${MESSAGES_PROTOS})
    message(STATUS "Inside ${proto_file}")
    get_filename_component(proto_file_abs ${proto_file} ABSOLUTE)
    get_filename_component(basename ${proto_file} NAME_WE)
    set(generated_files ${basename}.pb.cc ${basename}.pb.h)

    list(APPEND MESSAGES_SRCS ${basename}.pb.cc)
    list(APPEND MESSAGES_HDRS ${CMAKE_CURRENT_BINARY_DIR}/${basename}.pb.h)

    add_custom_command(
            OUTPUT ${generated_files}
            COMMAND echo ${CMAKE_CURRENT_BINARY_DIR}
            COMMAND protobuf::protoc --cpp_out ${CMAKE_CURRENT_BINARY_DIR} -I ${CMAKE_CURRENT_SOURCE_DIR}/proto ${proto_file_abs}
            COMMENT "Generating ${generated_files} from ${proto_file}"
            VERBATIM
    )
endforeach()

message(STATUS "Adding messages library ${MESSAGES_SRCS}")

add_library(messages "${MESSAGES_SRCS}")
target_link_libraries(messages protobuf::libprotobuf)
target_include_directories(messages PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

add_executable(hello "src/main.cpp")
target_link_libraries(hello messages)
add_dependencies(hello messages)