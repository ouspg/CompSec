# Arch Linux based Virtual Machine with Black Arch repositories

This Linux distribution might have different package manager than many have used to, but it has *one of the greatest wikis* for possible problem situations. See [Arch Linux Wiki.](https://wiki.archlinux.org/)

This virtual machine has only those tools included that are needed to do the most of the exercises in the course, in case you don't have enough space on hard drive.
Package ecosystem is also much better than in Kali Linux, if you are willing to install more by yourself.

## Image Info

Gnome Desktop Environment as default.

VirtualBox 6.1 guest additions included. Use same version for the best experience.

For VMware, open-vm-tools are included.

* Username: **arch**
* Password: **arch**

## Black Arch repository

You can directly install [Black Arch](https://blackarch.org/) tools if you need some special ones. Only few which are mandatory, are preinstalled to save the space.

See their [tools](https://blackarch.org/tools.html) section for available tools.


## Installing packages

Update package index

```console
sudo pacman -Sy
```
    
Install package (You can look from here https://archlinux.org/packages/ for official packages and https://blackarch.org/tools.html for pentesting tools.)

```console
sudo pacman -S <package-name>
```

Remove package 
```console
sudo pacman -R <package-name>
```

Upgrade all packages
```
sudo pacman -Syu
```

Clean package cache:
```console
sudo pacman -Sc
```

## Installing AUR packages (from https://aur.archlinux.org/packages/)

Arch Linux has huge user supplied package ecosystem, which is located in the different repository. See https://aur.archlinux.org/packages/. Usually you need some kind of helper for installing these packages. 

[`yay`](https://github.com/Jguer/yay) helper has been pre-installed for installing AUR packages.

Install AUR package (Note, that sudo not included)

```console
yay -S <aur-package-name>
```
Remove AUR package

```console
yay -R <aur-package-name>
```

Upgrade all packages
```console
yay
```

## Special cases on labs

### Lab 1

Afl test cases are in different location `/usr/share/afl/testcases/`

### Lab 2

Restart apache with
```console
sudo systemctl restart httpd.service
```