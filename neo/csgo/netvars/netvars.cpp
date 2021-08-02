#include "netvars.h"
#include "../utilities/xor.h"
#include "../sdk.h"

netvar_manager netvars;

    void netvar_manager::init() {
        database.clear();
        for (auto clientclass = csgo::client->get_client_classes();
            clientclass != nullptr;
            clientclass = clientclass->next_ptr) {
            if (clientclass->recvtable_ptr) {
                database.emplace_back(load_table(clientclass->recvtable_ptr));
            }
        }
    }

    netvar_manager::netvar_table netvar_manager::load_table(recv_table* recv_table) {
        auto table = netvar_table{};
        table.offset = 0;
        table.name = recv_table->table_name;
        for (auto i = 0; i < recv_table->props_count; ++i) {
            auto prop = &recv_table->props[i];
            if (!prop || isdigit(prop->prop_name[0]))
                continue;
            if (strcmp(xor("baseclass"), prop->prop_name) == 0)
                continue;
            if (prop->prop_type == _data_table && prop->data_table) {
                table.child_tables.emplace_back(load_table(prop->data_table));
                table.child_tables.back().offset = prop->offset;
                table.child_tables.back().prop = prop;
            }
            else {
                table.child_props.emplace_back(prop);
            }
        }
        return table;
    }

    uint32_t netvar_manager::get_offset(const std::string& tableName, const std::string& propName) {
        auto result = 0u;
        for (const auto& table : database) {
            if (table.name == tableName) {
                result = get_offset(table, propName);
                if (result != 0)
                    return result;
            }
        }
        return 0;
    }

    uint32_t netvar_manager::get_offset(const netvar_table& table, const std::string& propName) {
        for (const auto& prop : table.child_props) {
            if (strncmp(prop->prop_name, propName.data(), propName.size()) == 0) {
                return table.offset + prop->offset;
            }
        }
        for (const auto& child : table.child_tables) {
            auto prop_offset = get_offset(child, propName);
            if (prop_offset != 0)
                return table.offset + prop_offset;
        }
        for (const auto& child : table.child_tables) {
            if (strncmp(child.prop->prop_name, propName.data(), propName.size()) == 0) {
                return table.offset + child.offset;
            }
        }
        return 0;
    }