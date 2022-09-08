
# MCU name
MCU = SN32F248BF

# Build Options
#   comment out to disable the options.
#
F_CPU = 8000000 # super important as it will report malfunction without this
BOOTMAGIC_ENABLE  = yes  # Enable Bootmagic Lite
MOUSEKEY_ENABLE   = no   # Mouse keys
EXTRAKEY_ENABLE   = yes  # Audio control and System control
CONSOLE_ENABLE    = no   # Console for debug
COMMAND_ENABLE    = no   # Commands for debug and configuration
NKRO_ENABLE       = no   # Enable N-Key Rollover
BACKLIGHT_ENABLE  = no   # Enable keyboard backlight functionality
AUDIO_ENABLE      = no   # Audio output
WAIT_FOR_USB      = no
CUSTOM_MATRIX     = yes

# Custom RGB matrix handling
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = SN32F24xB

# project specific files
SRC = ../../../drivers/led/sn32/matrix_sn32f24xx.c
