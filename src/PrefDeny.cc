
#include "PrefDeny.hh"
#include "XrdCms/XrdCmsPref.hh"

extern "C" {

XrdCmsXmi *XrdCmsgetXmi(int, char **, XrdCmsXmiEnv *)
{
  return new PrefDeny();
}

}

int PrefDeny::Pref(XrdCmsReq *, const char *, const char *, XrdCmsPref &pref, XrdCmsPrefNodes&)
{
   pref.SetPreference(0, 0);
   return 0;
}

