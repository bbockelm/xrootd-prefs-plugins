
#include "PrefAllow.hh"
#include "XrdCms/XrdCmsPref.hh"

extern "C" {

XrdCmsXmi *XrdCmsgetXmi(int, char **, XrdCmsXmiEnv *)
{
  return new PrefAllow();
}

}

int PrefAllow::Pref(XrdCmsReq *, const char *, const char *, XrdCmsPref &pref, XrdCmsPrefNodes&)
{
   pref.SetPreference(0, -1);
   return 0;
}

