package cn.net.pikachu.enumeration

enum class RomControlEnum(val value: Int) {
    // 控制信息1
    SFC_NES_VMIRROR(0x01),
    SFC_NES_SAVERAM(0x02),
    SFC_NES_TRAINER(0x04),
    SFC_NES_4SCREEN(0x08),

    // 控制信息2
    SFC_NES_VS_UNISYSTEM(0X01),
    SFC_NES_PLAYCHOICE10(0X02);
}