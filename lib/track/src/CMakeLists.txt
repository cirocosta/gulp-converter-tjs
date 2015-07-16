add_executable(track main.cc)
add_executable(info_gen info_gen.cc)
add_library(tracker Tracker.cc Cli.cc)

target_link_libraries(info_gen
	${OpenCV_LIBS}
)

target_link_libraries(track
	${OpenCV_LIBS}
	tracker
)

