
include_directories ( ${XROOTD_INCLUDES} )
add_library (PrefAllowXmi MODULE PrefAllow.cc)
add_library (PrefDenyXmi MODULE PrefDeny.cc)
add_library (PrefOneXmi MODULE PrefOne.cc)

