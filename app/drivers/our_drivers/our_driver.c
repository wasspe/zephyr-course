#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#include "our_driver.h"

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_INST_PHANDLE(0, led), gpios);

struct our_driver_data {
    bool inverted;
};

static int channel_get_my_impl(const struct device *dev,
				    enum sensor_channel chan,
				    struct sensor_value *val){
    struct our_driver_data *data = dev->data;

    if (data->inverted) {
        LOG_INF("LED on");
        return gpio_pin_set_dt(&led, 1);
    }
    LOG_INF("LED off");
    return gpio_pin_set_dt(&led, 0);
}

static int sample_fetch_impl(const struct device *dev, enum sensor_channel chan){
    struct our_driver_data *data = dev->data;

    if (data->inverted) {
        LOG_INF("LED off");
        return gpio_pin_set_dt(&led, 0);
    }
    LOG_INF("LED on");
    return gpio_pin_set_dt(&led, 1);
}

static int set_inverted_impl(const struct device *dev, bool inverted){
    struct our_driver_data *data = dev->data;
    data->inverted = inverted;
    LOG_INF("Inverted set to %d", inverted);
    return 0;
}

static const struct our_driver_api our_driver_api = {
    .base = {
        .sample_fetch = sample_fetch_impl,
        .channel_get = channel_get_my_impl,
    },
    .set_inverted = set_inverted_impl,
};

static struct our_driver_data our_data;

static int init(const struct device* dev){
    LOG_INF("Device Initialized __");
    return gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
}

DEVICE_DT_INST_DEFINE(0, init, NULL, &our_data, NULL, POST_KERNEL, 80, &our_driver_api);
