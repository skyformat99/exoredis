#ifndef __SORTED_MAP_KEY_HPP__
#define __SORTED_MAP_KEY_HPP__

#include <vector>
#include <memory>
#include <cstddef>

#include "sorted_set_key.hpp"

/*
 * Key of the boost::unordered_map of the sorted set. Contians either an
 * owning or a non-owning pointer to a member.
*/
class sorted_map_key
{
public:
    struct equal_to
    {
        bool operator()(const sorted_map_key&, const sorted_map_key&) const;
    };

    struct hash
    {
        std::size_t operator()(const sorted_map_key&) const;
    };

    static sorted_map_key create_owned(const std::vector<unsigned char>&);
    static sorted_map_key create_unowned(const std::vector<unsigned char>*);

    const std::vector<unsigned char>& member() const;

    // Used to make a set key with the correct member pointer.
    sorted_set_key make_set_key(double score) const;

private:
    sorted_map_key(const std::vector<unsigned char>*);
    sorted_map_key(const std::vector<unsigned char>&);


    const std::vector<unsigned char>* unowned_member_ptr_;
    std::shared_ptr<std::vector<unsigned char>> member_ptr_;
};


#endif
