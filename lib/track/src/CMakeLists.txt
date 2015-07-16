add_executable(track main.cc)
add_library(tracker Tracker.cc)

target_link_libraries(track
	${OpenCV_LIBS}
	tracker
)

