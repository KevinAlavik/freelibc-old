# freelibc

> [!WARNING]
> Discontinued, current version doesnt really work.

A custom set of freestanding headers replacing the freestanding headers of libgcc

## Usage
To install freelibc you first need to build it, thats done by running this
```bash
make
```
to install it* simply run
```bash
sudo make install
``` 
*Note: By deafult `make install` installs freelibc to `/usr/local/lib` (and headers to `/usr/local/include/freelibc`). These paths can be changed like this: 
```bash
sudo make install LIB_DIR=/usr/local/lib INCLUDE_INSTALL_DIR=/usr/local/include/freelibc
``` 
(ofc changing the paths to what you need)

## License

`freelibc` is licensed under the GNU General Public License (GPL) version 3.0. You can view the full text of the GPL-3.0 license [here](https://www.gnu.org/licenses/gpl-3.0.html). In addition to the GPL-3.0 terms, there is an exception that allows you to link or combine `freelibc` with other software that is not licensed under the GPL-3.0. You may distribute the combined work under the terms of the license of the other software, provided that `freelibc` itself remains under the GPL-3.0. See [LICENSE](https://github.com/KevinAlavik/freelibc/tree/main/LICENSE) and [LICENSE.gpl](https://github.com/KevinAlavik/freelibc/tree/main/LICENSE.gpl)
