## Origins ##
Fork of libimobiledevice-win32 (https://github.com/storoj/libimobiledevice-win32) which in turn is win32 port of libimobiledevice (http://libimobiledevice.org).

## Goal ##
Debug MobileSafari and UIWebViews of ios devices on windows machines.

### Plan A: ###
- port usbmuxd
 - port sockets and process communication stuff
 - use libusbX event handling to deal with usb polling  
- port ios_webkit_proxy (https://github.com/google/ios-webkit-debug-proxy)
 
### Plan B: ###
- escape to NY, USA
- tell jokes
- sell out
