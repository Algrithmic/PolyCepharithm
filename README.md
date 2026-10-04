# PolyCepharithm
PolyCepharithm is a simulation that mimics the behavior of the Physarum Polycephalum slime mold

## Dependencies
### Linux

On Debian and derivatives like Ubuntu and Linux Mint you will need the libwayland-dev and libxkbcommon-dev packages to compile for Wayland and the xorg-dev meta-package to compile for X11. These will pull in all other dependencies.

```Bash
# On Debian and Derivatives
sudo apt install libwayland-dev libxkbcommon-dev xorg-dev

# On Fedora and Derivatives
sudo dnf install wayland-devel libxkbcommon-devel libXcursor-devel libXi-devel libXinerama-devel libXrandr-devel
```

### Windows

You'll need to Compile with MinGW-w64