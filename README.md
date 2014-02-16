rtc
===

[![Build Status](https://travis-ci.org/cryptotronix/rtc.png)](https://travis-ci.org/cryptotronix/rtc)

rtc is an user-space CLI application for embedded Real-Time Clocks (RTCs).  Currently, only one rtc is support, however this program can be extended for other devices.

Driver for the Maxim Integrated DS3231M I2C RTC.  This utility can be used to set and read the time from the Maxim Integrated DS3231M I2C RTC, further known as the DS3231M.

The data sheet for DS3231M can be found on Maxim Integrated [Website](
http://datasheets.maximintegrated.com/en/ds/DS3231M.pdf).  The device is high-accuracy real-time clock with on board oscillator, that is accessible over I2C.  The device can also support a battery backup.

Commands
---

The current commands implemented are `date` and `set-date`.  See the following example:

```bash
debian@arm:~/repos/rtc$ rtc set-date
debian@arm:~/repos/rtc$ echo $?
0
debian@arm:~/repos/rtc$ rtc date
Thu Jan  2 01:35:37 2014
```

Options
---

The default i2c bus is `/dev/i2c-1`, however this can be changed with
the `-b, --bus` option.
