set(component_srcs "temp6000.c")

idf_component_register(SRCS "${component_srcs}"
                    PRIV_REQUIRES driver
                    INCLUDE_DIRS "./include")
