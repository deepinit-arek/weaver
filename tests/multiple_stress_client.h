/*
 * ===============================================================
 *    Description:  Multiple client threads stress test
 *                  reachability request
 *
 *        Created:  01/23/2013 05:25:46 PM
 *
 *         Author:  Ayush Dubey, dubey@cs.cornell.edu
 *
 * Copyright (C) 2013, Cornell University, see the LICENSE file
 *                     for licensing agreement
 * ===============================================================
 */

#include "client/client.h"

void
multiple_stress_client()
{
    client c;
    size_t nodes[NUM_NODES];
    size_t edges[NUM_EDGES];
    size_t edge_leading_nodes[NUM_EDGES];
    int i;
    srand(42); // magic seed
    for (i = 0; i < NUM_NODES; i++)
    {
        nodes[i] = c.create_node();
    }
    for (i = 0; i < NUM_EDGES; i++)
    {
        int first = rand() % NUM_NODES;
        int second = rand() % NUM_NODES;
        while (second == first)
        {
            second = rand() % NUM_NODES;
        }
        edges[i] = c.create_edge(nodes[first], nodes[second]);
        edge_leading_nodes[i] = nodes[first];
    }
    for (i = 0; i < NUM_REQUESTS; i++)
    {
        int first = rand() % NUM_NODES;
        int second = rand() % NUM_NODES;
        while (second == first)
        {
            second = rand() % NUM_NODES;
        }
        std::cout << "Req " << i << " result "
            << c.reachability_request(nodes[first], nodes[second]) << std::endl;
    }
}