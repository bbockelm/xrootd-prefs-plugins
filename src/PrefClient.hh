
#include "XrdCms/XrdCmsXmi.hh"

// A simple, silly plugin for testing preferences
// This prefers the server brian-test.unl.edu:1094 for clients from that host
// For all other clients, any other server is preferred.

class PrefClient : public XrdCmsXmi
{

virtual int  Chmod (      XrdCmsReq      *,
                          mode_t          ,
                    const char           *,
                    const char           *) {return -1;}

virtual int  Mkdir (      XrdCmsReq      *,
                          mode_t          ,
                    const char           *,
                    const char           *) {return -1;}

virtual int Mkpath(      XrdCmsReq       *,
                          mode_t          ,
                    const char           *,
                    const char           *) {return -1;}

virtual int  Prep  (const char           *,
                          int             ,
                    const char           *,
                    const char           *) {return -1;}

virtual int  Rename(      XrdCmsReq      *,
                    const char           *,
                    const char           *,
                    const char           *,
                    const char           *) {return -1;}

virtual int  Remdir(      XrdCmsReq      *,
                    const char           *,
                    const char           *) {return -1;}

virtual int  Remove(      XrdCmsReq      *,
                    const char           *,
                    const char           *) {return -1;}

virtual int  Select(      XrdCmsReq      *, // See description above
                          int             ,
                    const char           *,
                    const char           *) {return -1;}

virtual int  Stat  (      XrdCmsReq      *,
                    const char           *,
                    const char           *) {return -1;}

virtual int  Pref  (      XrdCmsReq      *,
                    const char           *,
                    const char           *,
                         XrdCmsPref      &pref,
                    XrdCmsPrefNodes      &
                    );

virtual void XeqMode(unsigned int &isNormal,
                     unsigned int &isDirect) // We only implement the "Pref" command.
                    {isNormal = XMI_ALL-XMI_PREF; isDirect = XMI_ALL;}

private:

/*
 *  Returns true if this is the client we prefer; false otherwise.
 */
bool IsPreferredClient(const char * opaque);

};
