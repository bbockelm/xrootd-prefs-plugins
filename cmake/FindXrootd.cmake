
# Find the xrootd client includes and libraries

FIND_PATH(XROOTD_INCLUDES XrdCms/XrdCmsXmi.hh
  HINTS
  ${XROOTD_DIR}
  $ENV{XROOTD_DIR}
  /usr
  PATH_SUFFIXES include /xrootd
)

FIND_LIBRARY(XROOTD_UTILS XrdUtils
  HINTS
  ${XROOTD_DIR}
  $ENV{XROOTD_DIR}
  /usr
  PATH_SUFFIXES lib
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Xrootd DEFAULT_MSG XROOTD_UTILS XROOTD_INCLUDES)

