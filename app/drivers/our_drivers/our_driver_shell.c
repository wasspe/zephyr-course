#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>

/* get our sensor from the devicetree*/
static const struct device *sensor_dev = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

/* sensorroot fetch -> calls sensor_sample_fetch() */
static int cmd_fetch(const struct shell *sh, size_t argc, char **argv)
{

    shell_print(sh, "fetch ok");
    return 0;
}

/* sensorroot read -> calls sensor_channel_get() and prints the value */
static int cmd_read(const struct shell *sh, size_t argc, char **argv)
{
    struct sensor_value val = {0, 0};

    /* val1 is the whole part, val2 is the part after the dot (in millionths) */
    shell_print(sh, "value: %d.%06d", val.val1, val.val2);
    return 0;
}

/* sensorroot info -> prints device name and if it is ready */
static int cmd_info(const struct shell *sh, size_t argc, char **argv)
{
    shell_print(sh, "name:  %s", sensor_dev->name);
    shell_print(sh, "ready: %s", device_is_ready(sensor_dev) ? "yes" : "no");
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sensorroot_cmds,
    SHELL_CMD(fetch, NULL, "Fetch a new sample from the sensor", cmd_fetch),
    SHELL_CMD(read, NULL, "Read the channel and print the value", cmd_read),
    SHELL_CMD(info, NULL, "Show device name and ready state", cmd_info),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensorroot, &sensorroot_cmds, "Sensor driver commands", NULL);