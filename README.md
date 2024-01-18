![OpenIPC logo][logo]

## Majestic plugins for OpenIPC
**_Experimental system for creating open source plugins for Majestic_**

---

Prepare source:
```
git clone https://github.com/OpenIPC/firmware
cd firmware
git clone https://github.com/OpenIPC/majestic-plugins
```

Build usage:
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

Upload file:
```
scp -O majestic-plugins/*.so root@192.168.1.10:/usr/lib
```

---

Activate plugin support:
```
ssh root@192.168.1.10
cli -s .system.plugins true
killall -1 majestic
```

Send local command:
```
echo brightness 100 | nc localhost 4000
```

Send remote command:
```
curl -u root:12345 -s "http://192.168.1.10/plugin?command=brightness&value=100"
```

[logo]: https://openipc.org/assets/openipc-logo-black.svg
