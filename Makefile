GCC_PARAMETERS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
AS_PARAMETERS = --32
LD_PARAMETERS = -melf_i386

BOOTLOADER_DIRECTORY = bootloader
BOOTLOADER = $(shell find $(BOOTLOADER_DIRECTORY) -name '*.s')

SOURCE_DIRECTORY = src
SOURCES = $(shell find $(SOURCE_DIRECTORY) -name '*.cpp')

BUILD_DIRECTORY = build
OBJECTS_DIRECTORY = $(BUILD_DIRECTORY)/objs
OBJECTS = $(BOOTLOADER:$(BOOTLOADER_DIRECTORY)/%.s=$(OBJECTS_DIRECTORY)/%.o) $(SOURCES:$(SOURCE_DIRECTORY)/%.cpp=$(OBJECTS_DIRECTORY)/%.o)

$(OBJECTS_DIRECTORY)/%.o: $(BOOTLOADER_DIRECTORY)/%.s
	mkdir -p $(dir $@)
	as $(AS_PARAMETERS) -o $@ $<

$(OBJECTS_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp
	mkdir -p $(dir $@)
	gcc $(GCC_PARAMETERS) -c -o $@ $<

operating-system.bin: linker.ld $(OBJECTS)
	ld $(LD_PARAMETERS) -T $< -o $(BUILD_DIRECTORY)/$@ $(OBJECTS)

operating-system.iso:
	mkdir $(BUILD_DIRECTORY)/iso
	mkdir $(BUILD_DIRECTORY)/iso/boot
	mkdir $(BUILD_DIRECTORY)/iso/boot/grub
	cp $(BUILD_DIRECTORY)/operating-system.bin $(BUILD_DIRECTORY)/iso/boot/operating-system.bin
	echo 'set timeout=0' >> $(BUILD_DIRECTORY)/iso/boot/grub/grub.cfg
	echo 'set default=0' >> $(BUILD_DIRECTORY)/iso/boot/grub/grub.cfg
	echo '' >> $(BUILD_DIRECTORY)/iso/boot/grub/grub.cfg
	echo 'menuentry "Operating System" {' >> $(BUILD_DIRECTORY)/iso/boot/grub/grub.cfg
	echo '	multiboot /boot/operating-system.bin' >> $(BUILD_DIRECTORY)/iso/boot/grub/grub.cfg
	echo '	boot' >> $(BUILD_DIRECTORY)/iso/boot/grub/grub.cfg
	echo '}' >> $(BUILD_DIRECTORY)/iso/boot/grub/grub.cfg
	grub-mkrescue --output=$(BUILD_DIRECTORY)/$@ $(BUILD_DIRECTORY)/iso
	rm -rf $(BUILD_DIRECTORY)/iso

install: operating-system.bin operating-system.iso

run:
	(killall VirtualBox && sleep 1) || true
	VirtualBoxVM --startvm "Operating System" &