#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/shell/shell.h>
#include <stdlib.h>

/* handler for: sensor set <0|1> */
static int cmd_set(const struct shell *sh, size_t argc, char **argv)
{
    char *end;
    long value;

    /* argc is 1 when the user only typed "sensor set" */
    if (argc < 2) {
        shell_error(sh, "Missing argument. Usage: sensor set <0|1>");
        return -EINVAL;
    }

    /* convert the text to a number and check that it was really a number */
    value = strtol(argv[1], &end, 10);
    if (end == argv[1] || *end != '\0') {
        shell_error(sh, "'%s' is not a number. Usage: sensor set <0|1>", argv[1]);
        return -EINVAL;
    }

    /* inverted is a bool so only 0 and 1 make sense */
    if (value < 0 || value > 1) {
        shell_error(sh, "Value %ld is out of range, use 0 or 1", value);
        return -EINVAL;
    }

    shell_print(sh, "Inverted mode is now %s", value == 1 ? "on" : "off");
    return 0;
}

/* 1 mandatory arg (the command name "set") and 1 optional arg (the value).
 * More than one value is rejected by the shell itself, a missing value
 * is handled in cmd_set so we can print our own error message. */
SHELL_STATIC_SUBCMD_SET_CREATE(sensor_cmds,
    SHELL_CMD_ARG(set, NULL, "Set inverted mode: sensor set <0|1>", cmd_set, 1, 1),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sensor_cmds, "Sensor commands", NULL);