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

Activate plugin support:
```
ssh root@192.168.1.10
cli -s .system.plugins true
killall -1 majestic
```

Send command to plugin (local/remote):
```
echo brightness 100 | nc localhost 4000
curl -u root:12345 -s "http://192.168.1.10/plugin?command=brightness&value=100"
```

[logo]: https://openipc.org/assets/openipc-logo-black.svg
