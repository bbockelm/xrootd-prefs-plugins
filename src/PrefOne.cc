
#include "string.h"

#include "PrefOne.hh"
#include "XrdCms/XrdCmsPref.hh"
#include "XrdCms/XrdCmsPrefNodes.hh"

extern "C" {

XrdCmsXmi *XrdCmsgetXmi(int, char **, XrdCmsXmiEnv *)
{
  return new PrefOne();
}

}

int PrefOne::Pref(XrdCmsReq *, const char *, const char *, XrdCmsPref &pref, XrdCmsPrefNodes& nodes)
{
   const char * node_name;
   pref.SetPreference(0, -1);
   SMask_t mask = 0;
   for (unsigned int i=0; i<XRD_MAX_NODES; i++)
   {
      if ((node_name = nodes.GetNodeName(i)) && (strcmp(node_name, "[::129.93.239.174]:1094") == 0))
      {
         mask |= 1 << i;
      }
   }
   pref.SetPreference(1, mask);
   return 0;
}

