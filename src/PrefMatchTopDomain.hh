//
//  PrefMatchTopDomain.hh
//  
//
//  Created by Zhe Zhang on 8/27/12.
//
//

#ifndef ____PrefMatchTopDomain__
#define ____PrefMatchTopDomain__

#include <iostream>
#include "XrdCms/XrdCmsXmi.hh"

// This class basically just match the top level domains between the client
// which request for file and all the available nodes that can server the file.
// The client will favor the nodes with the same top level domain and set the
// preference mask accordingly.

class PrefMatchTopDomain : public XrdCmsXmi{
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
     * Get the ipv4 address from the condensed ipv6 address structure
     "[::123.123.123.123]:1234"
     */
    
    void ExtractIpv4fromIpv6(char ip_addr[], const char * nodes_name);

    /*
     * Simple string reverse utility
     */
    
    void StringReverse(char* original);    
};
    


#endif /* defined(____PrefMatchTopDomain__) */
