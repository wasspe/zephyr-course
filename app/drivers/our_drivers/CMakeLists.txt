if(CONFIG_OUR_DRIVER)
    target_include_directories(app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_sources(app PRIVATE our_driver.c)
endif()