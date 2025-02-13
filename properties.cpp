#include "properties.h"

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

void property_override(char const prop[], char const value[], bool add) {
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

void property_override(const std::vector<std::string> &props, char const value[], bool add) {
    for (const auto &prop : props) {
        property_override(prop.c_str(), value, add);
    }
}

std::vector<std::string> property_list(const std::string &prefix, const std::string &suffix) {
    std::vector<std::string> props;

    for (const std::string &part : {
        "",
        "bootimage.",
        "odm_dlkm.",
        "odm.",
        "oem.",
        "product.",
        "system_ext.",
        "system.",
        "vendor_dlkm.",
        "vendor.",
    }) {
        props.emplace_back(prefix + part + suffix);
    }

    return props;
}
