include(FindPackageHandleStandardArgs)

find_package(Boost)
if(Boost_FOUND)
    find_path(Boost_Util_FOUND boost/utility/base_from_member.hpp PATHS ${Boost_INCLUDE_DIRS})
    if(Boost_Util_FOUND)
	add_library(boost-utility INTERFACE)
	target_include_directories(boost-utility INTERFACE ${Boost_INCLUDE_DIRS})
	add_library(boost::utility ALIAS boost-utility)
    endif()
endif()

find_package_handle_standard_args(BoostUtility
    REQUIRED_VARS Boost_Util_FOUND Boost_INCLUDE_DIRS)
