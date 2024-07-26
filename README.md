# freelibc
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
freelibc is licensed under the GPL-v3.0 license see [LICENSE](https://github.com/KevinAlavik/freelibc/tree/main/LICENSE) online version of license available [here](https://www.gnu.org/licenses/gpl-3.0.html)
