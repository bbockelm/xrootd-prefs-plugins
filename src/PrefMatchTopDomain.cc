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
#include "XrdClient/XrdClientDebug.hh"

extern "C" {

    XrdCmsXmi *XrdCmsgetXmi(int, char **, XrdCmsXmiEnv *){
        return new PrefMatchTopDomain();
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
    while (*(nodes_name+index+offset) != ']') {
        ip_addr[index] = *(nodes_name+index+offset);
        index ++;
    }
    ip_addr[index] = '\0';
}


int PrefMatchTopDomain::Pref(XrdCmsReq *, const char *, const char * opaque, XrdCmsPref & pref, XrdCmsPrefNodes& nodes){

    const char * nodes_name;
    char * nodes_host;
    
    SMask_t mask[4] = {0,0,0,0};
    
    // Get the hostname of the client who sends the request
    XrdOucEnv env(opaque);
    char *client_host = env.Get("client_host");
    int client_host_length = strlen(client_host);
    StringReverse(client_host);
    
    // Debug Info
    Info(XrdClientDebug::kUSERDEBUG, "PrefMatchTopDomain", "Break Point 1 Reached");
    
    // Get the number of segments of a host name (e.g. cse.unl.edu has 3 segments, which are seperated by two '.')
    int num_segment = 1;
    int index = 0;
    while (client_host && *(client_host+index)!='\0') {
        if (*(client_host+index) == '.') {
            num_segment++;
        }
        index ++;
    }
    
    std::cout << "Break Point 1 reached!" << endl;
    
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
    }
    
    std::cout << "Break Point 2 reached!" << std::endl;
        
    // Match the partial_client_host with the server nodes' host name
    for (unsigned int i = 0; i < XRD_MAX_NODES; i++) {
        if((nodes_name = nodes.GetNodeName(i))){
            char ip_addr[16];
            ExtractIpv4fromIpv6(ip_addr, nodes_name);
            nodes_host = XrdSysDNS::getHostName(ip_addr);
            StringReverse(nodes_host);
            for (int j = 1; j <= actual_levels; j++) {
                if (strstr(nodes_host, partial_client_host_array[j-1]) == nodes_host) {
                    mask[j] |= 1 << i;
                }
            }
            
        }
    }
    
    std::cout << "Break Point 3 reached!" << std::endl;
    
    // Set the preference mask at different levels
    for (int i = 0; i < MAX_PREF_LEVELS; i++) {
        pref.SetPreference(i, mask[i]);
    }

    return 0;
}
    

    

