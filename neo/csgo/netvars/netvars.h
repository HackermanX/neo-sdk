#pragma once
#include "../classes/recv.h"
#include <memory>
#include <iostream>
#include <unordered_map>

class netvar_manager
{
public:
    struct netvar_table {
        std::string               name;
        recv_prop* prop;
        uint32_t                  offset;
        std::vector<recv_prop*>   child_props;
        std::vector<netvar_table> child_tables;
    };

    void init();
    netvar_table load_table(recv_table* recv_table);
    uint32_t get_offset(const std::string& tableName, const std::string& propName);
    uint32_t get_offset(const netvar_table& table, const std::string& propName);

    std::vector<netvar_table>  database;
};

extern netvar_manager netvars;