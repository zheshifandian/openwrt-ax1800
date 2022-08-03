/*
 * 	gl_fan {
 *		compatible = "gl-fan";
 *		interrupt-parent = <&pio>;
 *		interrupts = <29 IRQ_TYPE_EDGE_RISING>;
 *	};
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/interrupt.h>
#include <linux/of_irq.h>
#include <linux/timer.h>
#include <linux/of_platform.h>

#define GL_FAN_DRV_NAME "gl-fan_v2.0"

typedef struct {
    struct class *class;
    struct device *dev;
    unsigned int count;
    unsigned int irq;
    bool refresh;
    struct timer_list timer;
} gl_fan_t;

static gl_fan_t gl_fan;

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 4, 0)
static void gl_fan_timer_callback(unsigned long arg)
#else
static void gl_fan_timer_callback(struct timer_list *t)
#endif
{
    disable_irq(gl_fan.irq);
    gl_fan.refresh = false;
}

static irqreturn_t handle_gpio_irq(int irq, void *data)
{
    gl_fan.count++;
    return IRQ_HANDLED;
}

static ssize_t fan_speed_show(struct class *class, struct class_attribute *attr, char *buf)
{
    if (gl_fan.refresh) {
        return sprintf(buf, "refreshing...\n");
    } else {
        if (gl_fan.count < 5) {
            return sprintf(buf, "0\n");
        } else {
            return sprintf(buf, "%d\n", (int)(30 * gl_fan.count));
        }
    }
}

static ssize_t fan_speed_store(struct class *class, struct class_attribute *attr, const char *buf, size_t count)
{
    if (!strstr(buf, "refresh")) {
        pr_err("please input 'refresh' %s\n", buf);
        return -EBADRQC;
    }

    if (gl_fan.refresh == true) {
        pr_err("gpio is busy\n");
        return -EBADRQC;
    }

    gl_fan.refresh = true;
    gl_fan.count = 0 ;

    enable_irq(gl_fan.irq);
    mod_timer(&gl_fan.timer, jiffies + msecs_to_jiffies(1000));

    return count;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 4, 0)
static CLASS_ATTR(fan_speed, 0664, fan_speed_show, fan_speed_store);
#else
static const struct class_attribute class_attr_fan_speed =
    __ATTR(fan_speed, 0664, fan_speed_show, fan_speed_store);
#endif

static int gl_fan_probe(struct platform_device *pdev)
{
    struct device_node *np = pdev->dev.of_node;
    struct device *dev = &pdev->dev;
    int ret;

    gl_fan.irq = of_irq_get(np, 0);
    if (gl_fan.irq < 0) {
        dev_err(dev, "Failed to get IRQ\n");
        return -ENXIO;
    }

    ret = devm_request_irq(dev, gl_fan.irq, handle_gpio_irq, 0, "fan speed", NULL);
    if (ret) {
        pr_err("request irq %d failed!\n", gl_fan.irq);
        return ret;
    }

    disable_irq(gl_fan.irq);

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 4, 0)
    setup_timer(&gl_fan.timer, gl_fan_timer_callback, 0);
#else
    timer_setup(&gl_fan.timer, gl_fan_timer_callback, 0);
#endif

    gl_fan.class = class_create(THIS_MODULE, "fan");
    ret = class_create_file(gl_fan.class, &class_attr_fan_speed);
    if (ret) {
        dev_err(dev, "fail to creat class file\n");
        return ret;
    }

    gl_fan.dev = dev;

    dev_info(dev, "install gl_fan\n");

    return 0;
}

static int gl_fan_remove(struct platform_device *pdev)
{
    class_destroy(gl_fan.class);
    dev_info(&pdev->dev, "remove gl_fan\n");
    return 0;
}

static const struct of_device_id gl_fan_match[] = {
    { .compatible = "gl-fan" },
    {}
};

static struct platform_driver gl_fan_driver = {
    .probe		= gl_fan_probe,
    .remove		= gl_fan_remove,
    .driver = {
        .name	= GL_FAN_DRV_NAME,
        .of_match_table = gl_fan_match,
    }
};

static int __init gl_fan_init(void)
{
    return platform_driver_register(&gl_fan_driver);
}

static void __exit gl_fan_exit(void)
{
    platform_driver_unregister(&gl_fan_driver);
}

module_init(gl_fan_init);
module_exit(gl_fan_exit);

MODULE_AUTHOR("xinfa deng <xinfa.deng@gl-inet.com>");
MODULE_LICENSE("GPL");
