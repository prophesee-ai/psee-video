// SPDX-License-Identifier: GPL-2.0 OR MIT
/*
 * Prophesee FPGA CSI Rx driver
 *
 * Copyright (C) Prophesee S.A.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/interrupt.h>

#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>

static int psee_video_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;

	int rc = 0;
	dev_info(dev, "Device Tree Probing\n");
	dev_set_drvdata(dev, NULL);
	return rc;
}

static int psee_video_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	dev_set_drvdata(dev, NULL);
	return 0;
}

#ifdef CONFIG_OF
static struct of_device_id psee_video_of_match[] = {
	{ .compatible = "psee,psee-video", },
	{},
};
MODULE_DEVICE_TABLE(of, psee_video_of_match);
#else
# define psee_video_of_match
#endif


static struct platform_driver psee_video_driver = {
	.driver = {
		.name = "psee-video",
		.owner = THIS_MODULE,
		.of_match_table	= psee_video_of_match,
	},
	.probe		= psee_video_probe,
	.remove		= psee_video_remove,
};

static int __init psee_video_init(void)
{
	printk(KERN_INFO "Hello module world.\n");
	return platform_driver_register(&psee_video_driver);
}


static void __exit psee_video_exit(void)
{
	platform_driver_unregister(&psee_video_driver);
	printk(KERN_INFO "Goodbye module world.\n");
}

module_init(psee_video_init);
module_exit(psee_video_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Prophesee");
MODULE_DESCRIPTION("psee-video - media/v4l2 driver for Prophesee video IP");
