/*
 * ===============================================================
 *    Description:  Client-side transaction data structures.
 *
 *        Created:  09/04/2013 08:57:13 AM
 *
 *         Author:  Ayush Dubey, dubey@cs.cornell.edu
 *
 * Copyright (C) 2013, Cornell University, see the LICENSE file
 *                     for licensing agreement
 * ===============================================================
 */

#ifndef weaver_client_transaction_h_
#define weaver_client_transaction_h_

#include <vector>

#include "common/message.h"

namespace client
{
    struct pending_update
    {
        message::msg_type type;
        uint64_t elem1, elem2, handle;
        std::string key, value;
    };

    typedef std::vector<std::shared_ptr<pending_update>> tx_list_t;
}

#endif
