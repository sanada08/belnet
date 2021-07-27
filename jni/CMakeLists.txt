add_library(belnet-android
    SHARED
    belnet_config.cpp
    belnet_daemon.cpp)
add_log_tag(belnet-android)
target_link_libraries(belnet-android libbelnet)
