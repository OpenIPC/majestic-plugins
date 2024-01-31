![OpenIPC logo][logo]

## Majestic plugins for OpenIPC
**_Experimental system for creating open source plugins for Majestic_**

### Important information:
- At the moment, examples of plugins have been implemented only for the most popular processors today.
- Nothing prevents everyone and enthusiasts from adding them to other processors and actively developing them.
- By default, the plugin system is disabled and does not contribute any actions to the main operation of the device.

---

### Example function:
- New functions can be added to `vendor/custom.c`
- RETURN is a macro to simplify the plugin response output.
```
static void get_example(const char *value) {
	RETURN("call to get_example: %s", value);
}

static table custom[] = {
	[...]
	{ "example", &get_example },
};
```

### Example result:

```
root@openipc-ssc337de:~# echo example test123 | nc localhost 3500
call to get_example: test123
```

---

### Prepare source:
```
git clone https://github.com/OpenIPC/firmware --depth 1
cd firmware
```

### Build usage:
```
- Hisilicon:
make br-majestic-plugins-rebuild BOARD=hi3516ev300_lite

- Goke:
make br-majestic-plugins-rebuild BOARD=gk7202v300_lite

- Ingenic:
make br-majestic-plugins-rebuild BOARD=t31_lite

- Sigmastar:
make br-majestic-plugins-rebuild BOARD=ssc335_lite
```

### Upload file:
```
scp -O output/build/majestic-plugins-master/*.so root@192.168.1.10:/usr/lib
```

---

### Activate plugin support:
```
ssh root@192.168.1.10
cli -s .system.plugins true
killall -1 majestic
```

### Send local command:
```
echo brightness 100 | nc localhost 3500
```

### Send remote command:
```
curl -u root:12345 -s "http://192.168.1.10/plugin?command=brightness&value=100"
```

[logo]: https://openipc.org/assets/openipc-logo-black.svg
