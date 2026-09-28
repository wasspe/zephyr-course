#ifndef OUR_DRIVER_H
#define OUR_DRIVER_H

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

#ifdef __cplusplus
extern "C" {
#endif

struct our_driver_api {
    struct sensor_driver_api base;
    int (*set_inverted)(const struct device *dev, bool inverted);
};

static inline int our_driver_set_inverted(const struct device *dev, bool inverted)
{
    const struct our_driver_api *api = (const struct our_driver_api *)dev->api;
    return api->set_inverted(dev, inverted);
}

#ifdef __cplusplus
}
#endif

#endif
