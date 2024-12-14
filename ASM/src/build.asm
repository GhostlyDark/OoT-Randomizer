.n64
.relativeinclude on

// version guard, prevent people from building with older armips versions
.if (version() < 110)
.notice version()
.error   "Detected armips build is too old. Please install https://github.com/Kingcom/armips version 0.11 or later."
.endif

.create "../roms/patched.z64", 0
.incbin "../roms/base.z64"
.include "macros.asm"

;==================================================================================================
; Constants
;==================================================================================================

.include "constants.asm"
.include "addresses.asm"

;==================================================================================================
; Base game editing region
;==================================================================================================

.include "boot.asm"
.include "hacks.asm"

;==================================================================================================
; New code region
;==================================================================================================

.headersize (0x80400000 - 0x3680000)

.org 0x80400000
.area 0x20000 //payload max memory
PAYLOAD_START:

.area 0x10, 0
REDUX_CONTEXT:
.word CONFIGURATION_CONTEXT
.endarea

.include "config.asm"
.include "init.asm"
.include "cutscenes.asm"
.include "every_frame.asm"
.include "menu.asm"
.include "empty_bomb.asm"
.include "fishing.asm"
.include "bgs_fix.asm"
.include "chus_in_logic.asm"
.include "dampe.asm"
.include "bunny_hood.asm"
.include "colors.asm"
.include "damage.asm"
.include "audio.asm"
.include "twinrova_wait.asm"
.include "boomerang.asm"
.include "agony.asm"
.include "items_as_adult.asm"
.include "misc_colors.asm"
.include "door_of_time_col_fix.asm"
.include "mask_deequip.asm"
.include "blue_fire_arrows.asm"
.include "armos.asm"
.include "volvagia.asm"

.align 0x10
.importobj "../build/bundle.o"
.align 8
FONT_TEXTURE:
.incbin("../resources/font.bin")
DPAD_TEXTURE:
.incbin("../resources/dpad32.bin")

LEATHER_CHEST_FRONT_TEXTURE:
.incbin("../resources/chests/Leather.front")
LEATHER_CHEST_BASE_TEXTURE:
.incbin("../resources/chests/Leather.back")
KEY_CHEST_FRONT_TEXTURE:
.incbin("../resources/chests/Key.front")
KEY_CHEST_BASE_TEXTURE:
.incbin("../resources/chests/Key.back")

.align 0x10
PAYLOAD_END:
.endarea //payload max memory

AUDIO_THREAD_MEM_START:
.skip AUDIO_THREAD_MEM_SIZE
.close
