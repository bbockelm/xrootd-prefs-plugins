//
//  PrefMatchTopDomain.cpp
//  
//
//  Created by Zhe Zhang on 8/27/12.
//
//
#include "PrefMatchTopDomain.hh"
#include <string.h>
#include <iostream>

#include "PrefClient.hh"
#include "XrdCms/XrdCmsPref.hh"
#include "XrdCms/XrdCmsPrefNodes.hh"
#include "XrdOuc/XrdOucEnv.hh"
#include "XrdSys/XrdSysDNS.hh"
#include "XrdSys/XrdSysError.hh"
#include "XrdSys/XrdSysLogger.hh"

extern "C" {

    XrdCmsXmi *XrdCmsgetXmi(int, char **, XrdCmsXmiEnv * env){
        return new PrefMatchTopDomain(env);
    }
}



void PrefMatchTopDomain::StringReverse(char* original){
    char c;
    int i, j;
    for(i=0, j=strlen(original)-1; i<j; i++, j--){
        c = *(original+i);
        *(original+i) = *(original+j);
        *(original+j) = c;
    }
    return;
} 



void PrefMatchTopDomain::ExtractIpv4fromIpv6(char ip_addr[], const char * nodes_name){
    
    int offset = 3;
    int index = 0;
    while (*(nodes_name+index+offset) != ']'&& *(nodes_name+index+offset) != '\0') {
        ip_addr[index] = *(nodes_name+index+offset);
        index ++;
    }
    ip_addr[index] = '\0';
}


int PrefMatchTopDomain::Pref(XrdCmsReq *, const char *, const char * opaque, XrdCmsPref & pref, XrdCmsPrefNodes& nodes){
    
    XrdSysError *eDest = envinfo-> eDest;

    const char * nodes_name;
    char * nodes_host;
    
    SMask_t mask[4] = {0,0,0,0};
    
    // Get the hostname of the client who sends the request
    XrdOucEnv env(opaque);
    char *client_host = env.Get("client_host");
    eDest->Emsg("PrefMatchTopDomain", "client host name is:", client_host);
    int client_host_length = strlen(client_host);
    StringReverse(client_host);
     
    eDest->Emsg("PrefMatchTopDomain", "The client host name after string reverse is:", client_host);
    
    // Get the number of segments of a host name (e.g. cse.unl.edu has 3 segments, which are seperated by two '.')
    int num_segment = 1;
    int index = 0;
    while (client_host && *(client_host+index)!='\0') {
        if (*(client_host+index) == '.') {
            num_segment++;
        }
        index ++;
    }

    // num_segment_char here is only used for debug purpose, which hold the number of segments, assume number of segment is < 10
    char num_segment_char[2];
    num_segment_char[0] = num_segment + '0';
    num_segment_char[1] = '\0';
    eDest->Emsg("PrefMatchTopDomain", "The number of segments for the client host name is:", num_segment_char);
        
    // Calculate the actual level of preferences beyond Pref 0 based on the number of segments in the client host name
    int actual_levels = (MAX_PREF_LEVELS-1 >= num_segment) ? num_segment : MAX_PREF_LEVELS-1;
    
    char partial_client_host_array[actual_levels][client_host_length];
    
    // For each preference level, partial_client_host represents the corresponding number of segments
    for(int i = 1; i <= actual_levels; i ++){
        char partial_client_host[client_host_length];
        int index = 0;
        int segment = 1;
        while(client_host && *(client_host+index)!='\0'){
            if(segment < i+1){
                *(partial_client_host+index)=*(client_host+index);
                if(*(client_host+index)=='.') segment++;
            }
            index ++;
        }
        *(partial_client_host+index) = '\0';
        strcpy(partial_client_host_array[i-1], partial_client_host);
        eDest->Emsg("PrefMatchTopDomain", "partial client host name is:", partial_client_host_array[i-1]);
    }
            
    // Match the partial_client_host with the server nodes' host name
    for (unsigned int i = 0; i < XRD_MAX_NODES; i++) {
        // Add the condition check *nodes_name == '[', since valid ipv6 address should start with '['
        if((nodes_name = nodes.GetNodeName(i)) &&(*nodes_name == '[')){
            eDest->Emsg("PrefMatchTopDomain", "IPV6 address is:", nodes_name);
            char ip_addr[16];
            ExtractIpv4fromIpv6(ip_addr, nodes_name);
            eDest->Emsg("PrefMatchTopDomain", "the converted IPV4 address is:", ip_addr);
            nodes_host = XrdSysDNS::getHostName(ip_addr);
            eDest->Emsg("PrefMatchTopDomain", "the converted host name for the data server is:", nodes_host);
            StringReverse(nodes_host);
            eDest->Emsg("PrefMatchTopDomain", "the reversed data server host name is:", nodes_host);
            for (int j = 1; j <= actual_levels; j++) {
                if (strstr(nodes_host, partial_client_host_array[j-1]) == nodes_host) {
                    mask[j] |= 1 << i;
                }
            }
            
        }
    }
        
    // Set the preference mask at different levels
    for (int i = 0; i < MAX_PREF_LEVELS; i++) {
        pref.SetPreference(i, mask[i]);
    }

    return 0;
}
    

    

