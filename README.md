# Build Instructions
```zsh
git clone https://github.com/Xichil/zsh-multithread.git
cd zsh-multithread
cmake -B build
cd build
make -j $(nproc)
sudo make install
# Installs the command `zt`
```
