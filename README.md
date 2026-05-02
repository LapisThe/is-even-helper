# Is-Even Helper Script

This C++ program will greatly assist in the creation of an unfathomably quick IsEven Luau module script. Say goodbye to several hours and grueling amounts of labor writing conditionals for all your program's needs. With a program like this, mere minimum and maximum parameters will suffice in producing days worth of (subjectively) invaluable work.

While this was designed with the primary intent to be used within GNU/Linux, it should work perfectly fine on other popular operating systems, such as Windows or MacOS. (Could somebody confirm this..?)

## Getting Started

Dependencies:
`boost`

Ubuntu/Debian:

```sh
sudo apt install libboost-all-dev
```

Fedora:

```sh
sudo dnf install boost-devel
```

Homebrew:

```sh
brew install boost
```

Arch:

```sh
sudo pacman -S boost
```

This program has been (not so) rigorously tested on [Arch Linux](https://archlinux.org/) (and only Arch, BTW).

## Building

This program takes advantage of Makefiles to facilitate the build process.

Run:

```sh
make
```

## Running

To get familiarized with the basic (optional) flags to run this program, run this from the project's root directory:

On Unix filesystems:

```sh
bin/isevenhelper --help
```

## Contributing

Contributions are always welcome! To get started, fork this repository, branch off `main`, and submit a pull request to merge. These are excellent opportunities to create further improvements and optimizations, or to suggest new potential ideas.

While there are currently no official `CONTRIBUTING.md` guidelines, it is highly appreciated to conform to the general naming and styling conventions found within the codebase!

## Other notes

If it wasn't obvious already, this entire project was entirely built upon the notion of satire. Happy coding!
