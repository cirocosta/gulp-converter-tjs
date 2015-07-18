add_executable(track main.cc)
add_executable(info_gen info_gen.cc)
add_executable(solver solver.cc)
add_library(tracker Tracker.cc)

add_subdirectory(cli/)

target_link_libraries(info_gen
	${OpenCV_LIBS}
	cli_infogen
)

target_link_libraries(solver
	${OpenCV_LIBS}
	cli_solver
	tracker
)

target_link_libraries(track
	${OpenCV_LIBS}
	cli_tracker
	tracker
)

