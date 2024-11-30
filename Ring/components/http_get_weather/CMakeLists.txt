set(priv_requires "esp_http_client" "esp-tls" "json")

idf_component_register(SRC_DIRS "."
                    INCLUDE_DIRS "include"
                    PRIV_REQUIRES ${priv_requires})
