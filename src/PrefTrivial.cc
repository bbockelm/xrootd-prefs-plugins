
#include "PrefTrivial.hh"
#include "XrdCms/XrdCmsPref.hh"

int PrefTrivial::Pref(XrdCmsReq *, const char *, const char *, XrdCmsPref &pref, XrdCmsPrefNodes&)
{
   pref.SetPreference(0, -1);
   return 0;
}

