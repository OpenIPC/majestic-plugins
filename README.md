![OpenIPC logo][logo]

## Majestic plugins for OpenIPC
**_Experimental system for creating open source plugins for Majestic_**

---

Build usage:
```
git clone https://github.com/OpenIPC/firmware
cd firmware
git clone https://github.com/OpenIPC/majestic-plugins

export BOARD=ssc335_lite
make br-majestic-plugins-rebuild
```

Upload library:
```
scp -O majestic-plugins/sigmastar.so root@192.168.1.10:/usr/lib
```

---

Send command:
```
curl -u root:12345 -s "http://192.168.1.10/plugin?command=1&value=100"
```

Get result:
```
curl -u root:12345 -s "http://192.168.1.10/plugin?result"
```

[logo]: https://openipc.org/assets/openipc-logo-black.svg
