/*
 * ===============================================================
 *    Description:  Remote node pointer for edges.
 *
 *        Created:  03/01/2013 11:29:16 AM
 *
 *         Author:  Ayush Dubey, dubey@cs.cornell.edu
 *
 * Copyright (C) 2013, Cornell University, see the LICENSE file
 *                     for licensing agreement
 * ===============================================================
 */

#ifndef weaver_db_element_remote_node_h_
#define weaver_db_element_remote_node_h_

namespace db
{
namespace element
{
    class remote_node
    {
        public:
            remote_node();
            remote_node(uint64_t, uint64_t);

        public:
            uint64_t loc;
            uint64_t id;
            uint64_t get_id();
            bool operator==(const db::element::remote_node &t) const;
            bool operator!=(const db::element::remote_node &t) const;
    };

    static db::element::remote_node coordinator(0,0);
    
    inline
    remote_node :: remote_node(uint64_t l, uint64_t i)
        : loc(l)
        , id(i)
    { }

    inline remote_node :: remote_node() { }

    inline uint64_t 
    remote_node :: get_id()
    {
        return id;
    }

    inline bool
    remote_node :: operator==(const db::element::remote_node &t) const
    {
        return (id == t.id) && (loc == t.loc);
    }

    inline bool
    remote_node :: operator!=(const db::element::remote_node &t) const
    {
        return (id != t.id) || (loc != t.loc);
    }
    
}
}

namespace std
{
    // used if we want a hash table with a remote node as the key
    template <>
    struct hash<db::element::remote_node> 
    {
        public:
            size_t operator()(const db::element::remote_node &x) const throw() 
            {
                return (hash<int>()(x.loc) * 6291469) + (hash<size_t>()(x.id) * 393241); // some big primes
            }
    };
}

#endif
