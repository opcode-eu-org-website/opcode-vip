
# skrypt używający biblioteki C
# bez API pythonowego

# skrypt powoduje włączenie NumLock
# przy pracy w trybie graficznym
# zgodnym z X11

from ctypes import *
X11 = cdll.LoadLibrary("libX11.so.6")

X11.XOpenDisplay.restype = c_void_p
display = X11.XOpenDisplay(None);
X11.XkbLockModifiers(
	c_void_p(display), c_uint(0x0100),
	c_uint(16), c_uint(16)
)
X11.XCloseDisplay(c_void_p(display))
