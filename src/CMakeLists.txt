
include_directories ( ${XROOTD_INCLUDES} )
add_library (PrefAllowXmi MODULE PrefAllow.cc)
add_library (PrefDenyXmi MODULE PrefDeny.cc)
add_library (PrefOneXmi MODULE PrefOne.cc)
add_library (PrefClientXmi MODULE PrefClient.cc)
add_library (PrefMatchTopDomainXmi MODULE PrefMatchTopDomain.cc)

install(
  TARGETS PrefAllowXmi
          PrefDenyXmi
          PrefMatchTopDomainXmi
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/PrefXmi )

