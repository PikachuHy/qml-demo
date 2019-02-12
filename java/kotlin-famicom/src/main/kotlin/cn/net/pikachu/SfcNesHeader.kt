package cn.net.pikachu

data class SfcNesHeader(
    val id: String,
    val countPrgrom16kb: Int,
    val countChrrom8kb: Int
//    val control1: RomControlEnum,
//    val control2: RomControlByte2
)