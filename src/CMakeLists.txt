add_subdirectory(external)


add_executable(pixie pixie.cpp)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(
    pixie PUBLIC 
    "${PROJECT_BINARY_DIR}"
)


target_link_libraries(pixie PRIVATE 
    ImGui-SFML::ImGui-SFML
    nlohmann_json::nlohmann_json
    )

# Copy DLLs needed for runtime on Windows
if(WIN32)
  if (BUILD_SHARED_LIBS)
    add_custom_command(TARGET pixie POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
          $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
          $<TARGET_FILE:sfml-graphics>
          $<TARGET_FILE:sfml-window>
          $<TARGET_FILE:sfml-system>
          $<TARGET_FILE_DIR:pixie>)
  endif()
endif()