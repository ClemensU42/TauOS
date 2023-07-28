git clone https://github.com/limine-bootloader/limine.git --branch=v5.x-branch-binary --depth=1
 
# Build limine utility.
make -C limine
 
# Create a directory which will be our ISO root.
mkdir -p iso_root