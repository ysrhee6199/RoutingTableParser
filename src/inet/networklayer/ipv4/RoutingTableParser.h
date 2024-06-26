//
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
// Copyright (C) 2004 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

//
//  Author:     Jochen Reber
//  Date:       18.5.00
//  On Linux:   19.5.00 - 29.5.00
//  Modified by Vincent Oberle
//  Date:       1.2.2001
//  Cleanup and rewrite: Andras Varga, 2004
//

#ifndef __INET_ROUTINGTABLEPARSER_H
#define __INET_ROUTINGTABLEPARSER_H

#include "inet/networklayer/ipv4/Ipv4RoutingTable.h"

namespace inet {

/**
 * Parses a routing table file into a routing table.
 */
class INET_API RoutingTableParser
{
  protected:
    IInterfaceTable *ift;
    IIpv4RoutingTable *rt;

  public:
    /**
     * Constructor
     */
    RoutingTableParser(IInterfaceTable *ift, IIpv4RoutingTable *rt) : ift(ift), rt(rt) {}

    /**
     * Destructor
     */
    virtual ~RoutingTableParser() {}

    /**
     * Read Routing Table file; return 0 on success, -1 on error
     */
    virtual int readRoutingTableFromFile(const char *filename);

  protected:
    // Parsing functions

    // Used to create specific "files" char arrays without comments or blanks
    // from original file.
    virtual char *createFilteredFile(char *file,
            int& charpointer,
            const char *endtoken);

    // Go through the ifconfigFile char array, parse all entries and
    // write them into the interface table.
    // Loopback interface is not part of the file.
    virtual void parseInterfaces(char *ifconfigFile);

    // Go through the routeFile char array, parse all entries line by line and
    // write them into the routing table.
    virtual void parseRouting(char *routeFile);
    virtual void parseMultiRouting(char *routeFile);
    virtual char *parseEntry(char *ifconfigFile,
            const char *tokenStr,
            int& charpointer,
            char *destStr);

    // Convert string separated by ':' into dynamic string array.
    virtual void parseMulticastGroups(char *groupStr, NetworkInterface *);

    // Return 1 if beginning of str1 and str2 is equal up to str2-len,
    // otherwise 0.
    static int streq(const char *str1, const char *str2);

    // Skip blanks in string
    static void skipBlanks(char *str, int& charptr);

    // Copies the first word of src up to a space-char into dest
    // and appends \0, returns position of next space-char in src
    static int strcpyword(char *dest, const char *src);
};

} // namespace inet

#endif

