
#include "string.h"

#include "PrefClient.hh"
#include "XrdCms/XrdCmsPref.hh"
#include "XrdCms/XrdCmsPrefNodes.hh"
#include "XrdOuc/XrdOucEnv.hh"

extern "C" {

XrdCmsXmi *XrdCmsgetXmi(int, char **, XrdCmsXmiEnv *)
{
  return new PrefClient();
}

}

bool PrefClient::IsPreferredClient(const char * opaque)
{
   XrdOucEnv env(opaque);
   const char *client_host = env.Get("client_host");
   return client_host && (strcmp(client_host, "brian-test.unl.edu") == 0);
}

int PrefClient::Pref(XrdCmsReq *, const char *, const char * opaque, XrdCmsPref &pref, XrdCmsPrefNodes& nodes)
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
   if (IsPreferredClient(opaque))
      pref.SetPreference(1, mask);
   else
      pref.SetPreference(1, ~mask);
   return 0;
}

