#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_INST_PHANDLE(0, led), gpios);

static int channel_get_my_impl(const struct device *dev,
				    enum sensor_channel chan,
				    struct sensor_value *val){
    
    LOG_INF("LED off");
    return gpio_pin_set_dt(&led, 0);
}

static int sample_fetch_impl(const struct device *dev, enum sensor_channel chan){
    LOG_INF("LED on");
    return gpio_pin_set_dt(&led, 1);
}

static DEVICE_API(sensor, our_driver_api) = {
    .sample_fetch = sample_fetch_impl,
    .channel_get = channel_get_my_impl,
};

static int init(const struct device* dev){
    LOG_INF("Device Initialized __");
    return gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
}

DEVICE_DT_INST_DEFINE(0, init, NULL, NULL, NULL, POST_KERNEL, 80, &our_driver_api);