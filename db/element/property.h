/*
 * ===============================================================
 *    Description:  Each graph element (node or edge) can have
 *                  properties, which are key-value pairs 
 *
 *        Created:  Friday 12 October 2012 01:28:02  EDT
 *
 *         Author:  Ayush Dubey, dubey@cs.cornell.edu
 *
 * Copyright (C) 2013, Cornell University, see the LICENSE file
 *                     for licensing agreement
 * ===============================================================
 */

#ifndef weaver_db_element_property_h_
#define weaver_db_element_property_h_

#include <string>

#include "common/weaver_constants.h"
#include "common/vclock.h"

#include "node_prog/property.h"

namespace db
{
namespace element
{
    class property : public node_prog::property
    {
        public:
            property();
            property(std::string&, std::string&);
            property(std::string&, std::string&, vc::vclock&);
        
        public:
        /*
            std::string key;
            std::string value;
            */
            vc::vclock creat_time;
            vc::vclock del_time;

        public:
        /*
            const std::string& get_key();
            const std::string& get_value();
            */

            bool equals(std::string const &key2, std::string const &value2) const;
            bool operator==(property const &p2) const;

        public:
            const vc::vclock& get_creat_time() const;
            const vc::vclock& get_del_time() const;
            void update_del_time(vc::vclock&);
    };

    inline
    property :: property()
        : creat_time(MAX_UINT64, MAX_UINT64)
        , del_time(MAX_UINT64, MAX_UINT64)
    { }

    inline
    property :: property(std::string &k, std::string &v)
        : node_prog::property(k, v)
    {
    }

    inline
    property :: property(std::string &k, std::string &v, vc::vclock &creat)
        : node_prog::property(k, v)
        , creat_time(creat)
        , del_time(MAX_UINT64, MAX_UINT64)
    { }

/*
    inline const std::string&
    property :: get_key()
    {
        return key;
    }

    inline const std::string&
    property :: get_value()
    {
        return value;
    }
    */

    inline bool
    property :: equals(std::string const &key2, std::string const &value2) const
    {
        if (key.length() != key2.length()
         || value.length() != value2.length()) {
            return false;
        }
        uint64_t smaller, larger;
        if (key.length() < value.length()) {
            smaller = key.length();
            larger = value.length();
        } else {
            smaller = value.length();
            larger = key.length();
        }
        uint64_t i;
        for (i = 0; i < smaller; i++) {
            if (key[i] != key2[i]) {
                return false;
            } else if (value[i] != value2[i]) {
                return false;
            }
        }
        if (larger == key.length()) {
            for (; i < larger; i++) {
                if (key[i] != key2[i]) {
                    return false;
                }
            }
        } else {
            for (; i < larger; i++) {
                if (value[i] != value2[i]) {
                    return false;
                }
            }
        }
        return true;
    }

    inline bool
    property :: operator==(property const &p2) const
    {
        return equals(p2.key, p2.value);
    }

    inline const vc::vclock&
    property :: get_creat_time() const
    {
        return creat_time;
    }

    inline const vc::vclock&
    property :: get_del_time() const
    {
        return del_time;
    }

    inline void
    property :: update_del_time(vc::vclock &tdel)
    {
        del_time = tdel;
    }
}
}

namespace std
{
    template <>
    struct hash<db::element::property> 
    {
        private:
            std::function<size_t(const std::string&)> string_hasher;

        public:
            hash<db::element::property>() : string_hasher(std::hash<std::string>()) { }

            size_t operator()(const db::element::property &p) const throw() 
            {
                size_t hkey = string_hasher(p.key);
                size_t hvalue = string_hasher(p.value);
                return ((hkey + 0x9e3779b9 + (hvalue<<6) + (hvalue>>2)) ^ hvalue);
            }
    };
}

#endif
