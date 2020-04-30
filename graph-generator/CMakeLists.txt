set(RESULT -1)

execute_process(COMMAND pip show networkx
	RESULT_VARIABLE RESULT)

if(RESULT EQUAL 1)
	execute_process(COMMAND pip install --user networkx)
else()
	if(NOT (RESULT EQUAL 0))
		message(FATAL_ERROR "Error when installing necessary libs. CMake aborted!")
	endif()
endif()

add_custom_target(gengraph 
	python3 ${PROJECT_SOURCE_DIR}/graph-generator/graph-generator.py
	BYPRODUCTS ${CMAKE_BINARY_DIR}/generated_graphs/gn_random_graphs/*
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})